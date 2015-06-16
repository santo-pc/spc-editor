
#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets\qwidget.h>

class QSlider;
class QPushButton;

class GLWidget;
class MainWindow;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(MainWindow *mw);

protected:
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

	private slots:
	void dockUndock();

private:
	QSlider *createSlider();

	GLWidget *glWidget;
	QSlider *xSlider;
	QSlider *ySlider;
	QSlider *zSlider;
	QPushButton *dockBtn;
	MainWindow *mainWindow;
};


#endif
