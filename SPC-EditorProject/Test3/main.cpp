#include "GL/glew.h"
#define QT_NO_OPENGL_ES_2
#include <QtCore/QCoreApplication>
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qdesktopwidget.h>
#include <QtGui\qsurfaceformat.h>
#include "mainwindow.h"
#include "Form1.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);	
	
	QSurfaceFormat fmt;
	fmt.setDepthBufferSize(24);

	if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
		fmt.setSamples(4);
	if (QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"))) 
	{
		fmt.setVersion(3, 2);
		fmt.setProfile(QSurfaceFormat::CoreProfile);
	}

	QSurfaceFormat::setDefaultFormat(fmt);

	/*MainWindow mainWindow;
	mainWindow.resize(mainWindow.sizeHint());	
	mainWindow.showMaximized();*/
	Form1 form;
	form.resize(form.sizeHint());
	form.showMaximized();
	

	return app.exec();
}
