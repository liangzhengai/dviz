#include "MdiPreviewWidget.h"

#include <QMessageBox>
#include <QDesktopWidget>

//#include "VideoOutputWidget.h"
//#include "../qq06-glthread/GLWidget.h"

#include <QApplication>
#include <QSettings>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCDEStyle>

#include "VideoWidget.h"

void MdiPreviewWidget::setFadeTimef(double secs)
{
	int ms = (int)(secs * 1000.0);
	if(m_fadeSlider->value() != ms)
		m_fadeSlider->setValue(ms);
	// this will trigger setFadeTime(int) if value is different
}

void MdiPreviewWidget::setFadeTime(int ms)
{
	double sec = ((double)ms) / 1000;
	if(m_timeBox->value() != ms)
		m_timeBox->setValue(sec);
	
	m_outputWidget->setFadeLength(ms);
}

MdiPreviewWidget::MdiPreviewWidget(QWidget *parent)
	: MdiVideoChild(parent)
	, m_textInput(new QLineEdit(this))
{
	m_outputWidget = new VideoWidget();
	m_outputWidget->setFadeLength(1000);
		
	m_layout->addWidget(m_textInput);
	connect(m_textInput, SIGNAL(returnPressed()), this, SLOT(textReturnPressed()));
	
	QHBoxLayout *hbox1 = new QHBoxLayout();
	m_layout->addLayout(hbox1);
	
	QLabel *label = new QLabel("X Speed:");
	hbox1->addWidget(label);
	m_fadeSlider = new QSlider(Qt::Horizontal);
	m_fadeSlider->setMinimum(1);
	m_fadeSlider->setMaximum(10000);
	m_fadeSlider->setTickInterval(500);
	m_fadeSlider->setSingleStep(500);
	m_fadeSlider->setPageStep(500);
	m_fadeSlider->setValue(1500);
	m_fadeSlider->setTickPosition(QSlider::TicksBelow);
	hbox1->addWidget(m_fadeSlider,1);
	
	m_timeBox = new QDoubleSpinBox();
	m_timeBox->setSuffix("s");
	m_timeBox->setMinimum(1/1000);
	m_timeBox->setMaximum(10.0);
	//m_timeBox->setPageStep(0.5);
	m_timeBox->setSingleStep(0.5);
	m_timeBox->setValue(1.0);
	m_timeBox->setDecimals(1);
	m_timeBox->setStyleSheet("font-size:.85em");
	//m_timeBox->setStyle(new QCDEStyle());
	hbox1->addWidget(m_timeBox);
	
	QPushButton *blackBtn = new QPushButton(this);
	blackBtn->setIcon(QIcon("../data/stock-media-stop.png")/*,"&Black"*/);
	blackBtn->setCheckable(true);
	blackBtn->setStyle(new QCDEStyle());
	hbox1->addWidget(blackBtn);
	
	connect(blackBtn, SIGNAL(toggled(bool)), m_outputWidget, SLOT(fadeToBlack(bool)));
	
	
	connect(m_timeBox, SIGNAL(valueChanged(double)), this, SLOT(setFadeTimef(double)));
	connect(m_fadeSlider, SIGNAL(valueChanged(int)), this, SLOT(setFadeTime(int)));

	
/*	m_outputWidget = new GLWidget(0);
	m_outputWidget->show();
	m_outputWidget->startRendering();*/
	
// 	GLWidget *widget = new GLWidget(0);
// 	widget->setWindowTitle("Thread0");
// 	widget->show();
//  	widget->startRendering();
	
	
// 	m_outputWidget->setVisible(true);
// 	m_outputWidget->applyGeometry(QRect(0,0,320,240));


	QDesktopWidget *desktopWidget = QApplication::desktop();
	
	QSettings settings;
	int idx = settings.value("mdipreviewwidget/last-screen-index",0).toInt();
		
	m_configMenu = new QMenu(this);
	m_configMenu->addSeparator()->setText(tr("Output"));
	
	QActionGroup *screenGroup = new QActionGroup(this);
	connect(screenGroup, SIGNAL(triggered(QAction*)), this, SLOT(outputActionTriggered(QAction*)));
	QAction *action;
	
	m_screenList << QRect(0,0,1,1);
	
	action = m_configMenu->addAction("No Output");
	action->setCheckable(true);
	action->setChecked(idx == 0);
	action->setData(0);
	screenGroup->addAction(action);
	
	if(action->isChecked())
		outputActionTriggered(action);
	
	
	int numScreens = desktopWidget->numScreens();
	for(int screenNum = 0; screenNum < numScreens; screenNum ++)
	{
		QRect geom = desktopWidget->screenGeometry(screenNum);
		
		QString text = QString("Screen %1 at (%2 x %3)")
			.arg(screenNum + 1)
			.arg(geom.left())
			.arg(geom.top());
		
		action = m_configMenu->addAction(text);
		action->setCheckable(true);
		action->setChecked(idx == m_screenList.size());
		action->setData(m_screenList.size());
		screenGroup->addAction(action);
		
		m_screenList << geom;
		
		if(action->isChecked())
			outputActionTriggered(action);
	}
	
	setWindowTitle("Output Preview");
	
	videoWidget()->setFps(15);
}

	
void MdiPreviewWidget::textReturnPressed()
{
	m_videoWidget->setOverlayText(m_textInput->text());
	m_outputWidget->setOverlayText(m_textInput->text());
	m_textInput->selectAll();
}


void MdiPreviewWidget::outputActionTriggered(QAction *action)
{
	if(!action)
		return;
		
	int idx = action->data().toInt();
	
	if(idx < 0 || idx >= m_screenList.size())
		return;
		
	QSettings settings;
	settings.setValue("mdipreviewwidget/last-screen-index",idx);
		
	QRect geom = m_screenList[idx];
	
	//m_outputWidget->applyGeometry(geom);
	//m_outputWidget->setVisible(true);
	
	//qDebug() << "VideoOutputWidget::applyGeometry(): rect: "<<rect;
 	//if(isFullScreen)
 		m_outputWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
//  	else
//  		m_outputWidget->setWindowFlags(Qt::FramelessWindowHint);
				
				
	m_outputWidget->resize(geom.width(),geom.height());
	m_outputWidget->move(geom.left(),geom.top());
		
	m_outputWidget->show();
	
	m_outputWidget->setWindowTitle(QString("Video Output - LiveMix")/*.arg(m_output->name())*/);
	m_outputWidget->setWindowIcon(QIcon(":/data/icon-d.png"));
}

void MdiPreviewWidget::takeSource(MdiVideoChild *child)
{
	//m_outputWidget->setOverlayText(child->videoWidget()->overlayText());
	m_outputWidget->setVideoSource(child->videoSource());
	setVideoSource(child->videoSource());
}

void MdiPreviewWidget::takeSource(VideoSource *source)
{
	m_outputWidget->setVideoSource(source);
	setVideoSource(source);
}
