#include "MainWindow.h"
#include ".build/ui_MainWindow.h"

#include <QImage>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QImageWriter>
#include <QDesktopServices>
#include <QtOpenGL/QGLWidget>

#include <QThreadPool>

#include "ImageRecord.h"
#include "ImageRecordListModel.h"

#include "LoadDialog.h"

#include <QUuid>

#include <string>
#include <iostream>
#include <cassert>

#define DEBUG_PRELOAD 0 


namespace {

	QString removeLangPrefix(const QString & orig)
	{
		QString copy = orig;
		return copy.replace(QRegExp("^lang=\"[^\"]+\"\\s*"),"");
	}
		
}


MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, m_pixmap(0)
	, m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
        connect(m_ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(m_ui->loadBtn, SIGNAL(clicked()), this, SLOT(showLoadDialog()));
// 	connect(m_ui->importFolder, SIGNAL(returnPressed()), this, SLOT(loadFolder()));
	connect(m_ui->nextBtn, SIGNAL(clicked()), this, SLOT(nextImage()));
	connect(m_ui->prevBtn, SIGNAL(clicked()), this, SLOT(prevImage()));
	connect(m_ui->gotoBox, SIGNAL(editingFinished()), this, SLOT(loadGotoBoxValue()));
	
	connect(m_ui->graphicsView, SIGNAL(nextImage()), this, SLOT(nextImage()));
	connect(m_ui->graphicsView, SIGNAL(prevImage()), this, SLOT(prevImage()));
	

	m_scene = new QGraphicsScene();

	m_ui->graphicsView->setScene(m_scene);
	m_scene->setSceneRect(0,0,1024,768);
	
	m_pixmapItem = new QGraphicsPixmapItem();
	m_pixmapItem->setPos(0,0);
	m_scene->addItem(m_pixmapItem);
	
	m_cache.setMaxCost(1536); // 250 MB
	
	// Using similar formula as CPAN's config for the -j option: nbr cpus + 1
	QThreadPool::globalInstance()->setMaxThreadCount(QThread::idealThreadCount() + 1);
}

MainWindow::~MainWindow()
{
	writeMetaData();
	
	// Cleanup
	Exiv2::XmpParser::terminate();

	delete m_ui;
	if(m_pixmap)
		delete m_pixmap;
}


void MainWindow::showLoadDialog()
{
	LoadDialog d(this);
	if(d.exec())
	{
		QString folder = d.batchFolder();
		
		m_batchDir = QDir(folder);
		if(!m_batchDir.exists())
		{
			QMessageBox::critical(0,"Folder Not Found","Sorry, but the folder you entered in the 'Batch Folder' box does not exist.");
			return;
		}
	
		m_copyFiles = d.copyFiles();
		m_copyDest = QDir(d.copyFolder());
		if(!m_copyDest.exists())
		{
			QMessageBox::critical(0,"Destination Folder Not Found","Sorry, but the folder you entered in the 'Copy To Folder' box does not exist.");
			return;
		}
		
		m_cache.setMaxCost(d.cacheSize());
		m_lookBehind = d.lookBehind();
		m_lookAhead = d.lookAhead();
		
		loadFolder();
	}
}

#define ADD_DATUM(prefix,md) \
		QString key = QString("[" #prefix "] %1").arg(md->key().c_str()); \
		QString value = md->toString().c_str(); \
		textKeys << key; \
		textMap[key] = value; 

void MainWindow::loadFolder()
{
	
	
	QStringList filters;
// 	filters << "*.bmp";
// 	filters << "*.png";
	filters << "*.jpg";
	filters << "*.jpeg";
// 	filters << "*.xpm";
// 	filters << "*.svg";
	m_fileList = m_batchDir.entryList(filters);
	
	m_ui->progressBar->setMaximum(m_fileList.size());
	m_ui->gotoBox->setMaximum(m_fileList.size()-1);
	
	if(m_fileList.isEmpty())
	{
		QMessageBox::critical(this,tr("No JPEG Files Found"),QString(tr("I'm sorry, but no JPEG files were found in %1. Please check the folder and try again.")).arg(m_batchDir.absolutePath()));
		return;
	}
	
	
	setCurrentImage(0);
	
	m_ui->progressBar->setEnabled(true);
	m_ui->gotoBox->setEnabled(true);
	m_ui->groupBox->setEnabled(true);
	m_ui->nextBtn->setFocus();
}

void MainWindow::nextImage()
{
	if(m_fileList.isEmpty())
		return;
		
	m_currentFile ++;
	if(m_currentFile >= m_fileList.size())
		m_currentFile = 0;
	setCurrentImage(m_currentFile);
}

void MainWindow::prevImage()
{
	if(m_fileList.isEmpty())
		return;
		
	m_currentFile --;
	if(m_currentFile < 0)
		m_currentFile = m_fileList.size() - 1;
	setCurrentImage(m_currentFile);
}

QMutex mutex;
static int activeThreads = 0;
const int imageSize = 1024 * 4;

PreloadImageTask::PreloadImageTask(QString file)
	: QObject()
	, QRunnable()
	, m_file(file) {}

void PreloadImageTask::run()
{
	mutex.lock();
	activeThreads++;
	mutex.unlock();
	
	QImage image(m_file);
	
	if(DEBUG_PRELOAD)
		qDebug() << m_file<<":"<<(image.numBytes() / 1024 / 1024) << "MB ( active:"<<activeThreads<<")";
	
	emit imageLoaded(m_file,image); 
	
	mutex.lock();
	activeThreads--;
	mutex.unlock();
}

void MainWindow::loadGotoBoxValue()
{
	setCurrentImage(m_ui->gotoBox->value());
}

void MainWindow::setCurrentImage(int num)
{
	if(m_ui->gotoBox->value() != num)
		m_ui->gotoBox->setValue(num);
		
	writeMetaData();
		
	m_currentFile = num;
	m_ui->progressBar->setValue(num);
	
	QString file = m_fileList[num];
	QString path = QString("%1/%2").arg(m_batchDir.absolutePath()).arg(file);
	//QFileInfo fileInfo(path);
	
	setWindowTitle(QString(tr("Image Importer - %1")).arg(file));
	
	m_ui->filenameLabel->setText(file);
	
	initMetaData();
	
	if(m_pixmap)
		delete m_pixmap;
		
	QImage *img = 0;
	if((img = m_cache.object(path)) != 0)
	{
		if(DEBUG_PRELOAD)
			qDebug() << "MainWindow::setCurrentImage: Cache hit on "<<file;
		QPixmap px = QPixmap::fromImage(*img);
		m_pixmapItem->setPixmap(px);
		m_scene->setSceneRect(px.rect());
	}
	else
	{
		if(DEBUG_PRELOAD)
			qDebug() << "MainWindow::setCurrentImage: Cache MISS on "<<file;
		setCursor(Qt::BusyCursor);
		QPixmap origPixmap(path);
		//m_pixmap = new QPixmap();
		m_pixmapItem->setPixmap(origPixmap); //.scaledToWidth(1024));
		m_scene->setSceneRect(origPixmap.rect()); //0,0,1024,768);
		setCursor(Qt::ArrowCursor);
				
		imageLoaded(path, origPixmap.toImage());
	}
	
	m_ui->graphicsView->adjustViewScaling();
	
	int numQueued = 0;
	
	int it = num;
	while(it ++ < m_fileList.size() -1 && it - num <= m_lookAhead)
	{
		if(queuePreload(m_fileList[it]))
			numQueued ++;
	}
	
	it = num;
	while(it -- > 0 && num - it <= m_lookBehind)
	{
		if(queuePreload(m_fileList[it]))
			numQueued ++;
	}
	
	if(DEBUG_PRELOAD)
		qDebug() << "MainWindow::setCurrentImage: Queued"<<numQueued<<"for preload";
}

bool MainWindow::queuePreload(QString file)
{
	QString path = QString("%1/%2").arg(m_batchDir.absolutePath()).arg(file);
	if(!m_cache.contains(path) && 
	   !m_filesInProcess.contains(path))
	{
		m_filesInProcess.append(path);
		
		if(DEBUG_PRELOAD)
			qDebug() << "MainWindow::queuePreload: Queueing "<<file<<" for preload";
		PreloadImageTask *preload = new PreloadImageTask(path);
		connect(preload, SIGNAL(imageLoaded(QString,QImage)), this, SLOT(imageLoaded(QString,QImage)));
		
		// QThreadPool takes ownership and deletes 'preload' automatically
		QThreadPool::globalInstance()->start(preload);
		
		return true;
	}
	
	return false;
}

void MainWindow::imageLoaded(const QString& file, const QImage& img)
{
	int mb = img.numBytes() / 1024 / 1024;
	
	QImage * cacheable = new QImage(img);
	m_cache.insert(file, cacheable, mb);
	m_filesInProcess.remove(file);
	
	if(DEBUG_PRELOAD)
		qDebug() << "MainWindow::imageLoaded: Loaded"<<file<<" ("<<mb<<"MB )"; //<< ( m_filesInProcess.isEmpty() ? "" : QString(", still waiting on %1 images.").arg(m_filesInProcess.size()));
	
}

void MainWindow::initMetaData()
{
	if(m_fileList.isEmpty())
		return;
		
// 	m_ui->title->setText(file);
	QString file = m_fileList[m_currentFile];
	QString path = QString("%1/%2").arg(m_batchDir.absolutePath()).arg(file);
	
	/*
		Image ID	- 	Exif.Image.UniqueID, tag # 0xa420 - 128bit length, generate with QUuid
		Batch Name	- 	Xmp. ??
		Tags		- 	Xmp.dc.subject
		Description	-	Xmp.dc.description
		Title		-	Xmp.dc.title
		Location	-	Xmp. ??
		Rating		-	Xmp.xmp.Rating (1-5), Xmp.MicrosoftPhoto.Rating (%)
	*/

	m_exivImage = Exiv2::ImageFactory::open(path.toStdString()); 
	assert(m_exivImage.get() != 0);
	m_exivImage->readMetadata();
	
// 	QFile outputFile("output.txt");
// 	if(!outputFile.open(QFile::WriteOnly | QFile::Truncate))
// 	{
// 		qDebug() << "Unable to open output.txt for writing.";
// 	}
// 	
// 	QTextStream outputStream(&outputFile);
	
// 	Exiv2::ExifData& exifData = m_exivImage->exifData();
// 	QString imageId = exifData["Exif.Image.UniqueID"].toString().c_str();
// 	if(imageId.isEmpty())
// 	{
// 		imageId = QUuid::createUuid().toString();
// 		exifData["Exif.Image.UniqueID"] = (char *)imageId.constData();
// 		m_exivImage->setExifData(exifData);
// 	}
	
	
	
	Exiv2::XmpData& xmpData = m_exivImage->xmpData();
	
	QString imageId = xmpData["Xmp.dc.uniqueid"].toString().c_str();
	if(imageId.isEmpty())
	{
		imageId = QUuid::createUuid().toString();
		xmpData["Xmp.dc.uniqueid"] = imageId.toStdString();
		m_exivImage->setXmpData(xmpData);
	}
	
	ImageRecord * ref = ImageRecord::retrieveImageId(imageId);
	if(!ref)
	{
		ref = new ImageRecord(file);
		ImageRecord::addRecord(ref);
		
		Exiv2::ExifData& exifData = m_exivImage->exifData();
		QDateTime dt = QDateTime::fromString(exifData["Exif.Photo.DateTimeOriginal"].toString().c_str(), "yyyy:MM:dd HH:mm:ss");
		qDebug() << "MainWindow::initMetaData: "<<file<<": Date/Time taken: "<<dt.toString();
		
		ref->setDatestamp(dt);
		ref->setImageId(imageId);
		
		ImageRecord * ref2 = ImageRecord::retrieveImageId(imageId);
		if(!ref2)
		{
			qDebug() << "can't re-retrieve imageId"<<imageId;
			abort();
		}
	}
	else
	{
		qDebug() << "MainWindow::initMetaData: "<<file<<": Loaded record#"<<ref->recordId()<<" from database";
	}
	
	QString batch		= xmpData["Xmp.dc.batch"]	.toString().c_str();
	QString location	= xmpData["Xmp.dc.coverage"]	.toString().c_str();
	QString tags 		= xmpData["Xmp.dc.subject"]	.toString().c_str();
	QString description 	= xmpData["Xmp.dc.description"]	.toString().c_str();
	QString title 		= xmpData["Xmp.dc.title"]	.toString().c_str();
	QString rating	 	= xmpData["Xmp.xmp.rating"]	.toString().c_str();
	
	
	
	if(!batch.isEmpty())
		m_ui->batchname->setText(batch);
	
	if(!location.isEmpty())
		m_ui->location->setText(location);
	
	if(!tags.isEmpty())
		m_ui->tags->setText(tags);
	
	if(!description.isEmpty())
		m_ui->description->setText(removeLangPrefix(description));
	else
		m_ui->description->setText("");
		
	if(!title.isEmpty())
		m_ui->title->setText(removeLangPrefix(title));
	else
		m_ui->title->setText("");
		
	if(!rating.isEmpty())
		m_ui->rating->setValue(rating.toInt());
	else
		m_ui->rating->setValue(0);
		
	/*
	
	for (Exiv2::XmpData::const_iterator md = xmpData.begin();
		md != xmpData.end(); ++md) 
	{
		ADD_DATUM("XMP",md);
	}
	
	if (xmpData.empty()) 
	{
		qDebug() << "XmpData: No XMP Data found in "<<file;
	}*/
	
	
	
}

void MainWindow::writeMetaData()
{
	if(!m_exivImage.get())
		return;
	
	
	Exiv2::XmpData& xmpData = m_exivImage->xmpData();
	QString imageId = xmpData["Xmp.dc.uniqueid"].toString().c_str();
	
	QString file = m_fileList[m_currentFile];
	qDebug() << "MainWindow::writeMetaData: "<<file<<": Writing meta data for imageId: "<<imageId;
	
	ImageRecord * ref = ImageRecord::retrieveImageId(imageId);
	if(!ref)
	{
		ref = new ImageRecord(file);
		ImageRecord::addRecord(ref);
		
		Exiv2::ExifData& exifData = m_exivImage->exifData();
		QDateTime dt = QDateTime::fromString(exifData["Exif.Photo.DateTimeOriginal"].toString().c_str(), "yyyy:MM:dd HH:mm:ss");
		qDebug() << "MainWindow::writeMetaData: "<<file<<": Date/Time taken: "<<dt.toString();
		ref->setDatestamp(dt);
	}
	else
	{
		qDebug() << "MainWindow::writeMetaData: "<<file<<": Loaded record#"<<ref->recordId()<<" from database";
	}
	
	
	QString batch = m_ui->batchname->text();
	ref->setBatchName(batch);
	xmpData["Xmp.dc.batch"]		= batch.toStdString();
	
	QString location = m_ui->location->text();
	ref->setLocation(location);
	xmpData["Xmp.dc.coverage"]	= location.toStdString();
	
	QString tags = m_ui->tags->text();
	ref->setTags(tags);
	
	
	
	for (Exiv2::XmpData::iterator md = xmpData.begin();
		md != xmpData.end(); ++md) 
		if(strcmp(md->key().c_str(),"Xmp.dc.subject") == 0)
			md = xmpData.erase(md);
		
	xmpData["Xmp.dc.subject"]	= tags.toStdString();
	
	QString description = m_ui->description->text();
	ref->setDescription(description);
	xmpData["Xmp.dc.description"]	= description.toStdString();
	
	QString title = m_ui->title->text();
	ref->setTitle(title);
	xmpData["Xmp.dc.title"]		= title.toStdString();
	
	int rating = m_ui->rating->value();
	ref->setRating(rating);
	QString ratingStr = QString("%1").arg(rating);
	xmpData["Xmp.xmp.rating"]	= ratingStr.toStdString();
	
// 	// Serialize the XMP data and output the XMP packet
// 	std::string xmpPacket;
// 	if (0 != Exiv2::XmpParser::encode(xmpPacket, xmpData)) {
// 		throw Exiv2::Error(1, "Failed to serialize XMP data");
// 	}
// 	//std::cout << xmpPacket << "\n";
// 	qDebug() << "xmpPacket: "<<xmpPacket.c_str();

	m_exivImage->setXmpData(xmpData);
	m_exivImage->writeMetadata();
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) 
	{
		case QEvent::LanguageChange:
			m_ui->retranslateUi(this);
			break;
		default:
			break;
	}
}


 bool MainWindow::event(QEvent *event)
 {
	if (event->type() == QEvent::KeyPress) 
	{
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		//qDebug() << "MainWindow::event: key:"<<ke->key();
		if(ke->key() >= 0x30 && ke->key() <= 0x35)
		{
			int rating = ke->key() - 0x30;
			m_ui->rating->setValue(rating);
			qDebug() << "MainWindow::event: key:"<<ke->key()<<", rating:"<<rating;
		}
		else
		if(ke->key() >= 0x01000030 && ke->key() <= 0x01000034)
		{
			int rating = ke->key() - 0x01000030 + 1;
			m_ui->rating->setValue(rating);
			qDebug() << "MainWindow::event: key:"<<ke->key()<<", rating:"<<rating;
		}
		else
// 		if(ke->key() == Qt::Key_F2)
// 		{
// 			showRenameDialog();
// 		}
// 		else
		{
			qDebug() << "MainWindow::event: unused key:"<<ke->key();
		}
	}
	
	return QWidget::event(event);
}