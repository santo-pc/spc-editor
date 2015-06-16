#pragma once

#include <GL\glew.h>
#include <QtWidgets\qmainwindow.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include "GeneratedFiles\ui_Form2.h"
#include "qnodeseditor.h"


class Form1 : public QMainWindow
{
	Q_OBJECT

	public:		
		explicit Form1(QWidget *parent = 0);
		~Form1();
	
	private:
		Ui::MainWindow *ui;

		QNodesEditor *nodesEditor;
		QMenu *fileMenu;
		QGraphicsView *view;
		QGraphicsScene *scene;
};

