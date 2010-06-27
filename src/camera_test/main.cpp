#include <QtGui/QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtOpenGL/QGLWidget>
#include <QDebug>
#include <QAbstractTextDocumentLayout>
#include <QTextDocument>
#include <QTextCursor>

//#include "CameraTest.h"
#include "CameraViewerWidget.h"

int main(int argc, char **argv)
{
	//QGL::setPreferredPaintEngine(QPaintEngine::OpenGL);
	QApplication app(argc, argv);

// 	CameraTest t;
	CameraViewerWidget t;
	t.show();
	t.resize(100,100);

	return app.exec();
}
