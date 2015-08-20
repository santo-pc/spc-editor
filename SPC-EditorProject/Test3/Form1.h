#pragma once

#include <GL\glew.h>
#include <QtWidgets\qmainwindow.h>
#include <qgraphicsscene.h>
#include <qpoint.h>
#include <qgraphicssceneevent.h>
#include <qgraphicsview.h>
#include "GeneratedFiles\ui_Form2.h"

#include "qnodeseditor.h"
#include "QNEditorNodes.h"
#include "SPGraphicsScene.h"
#include "glwidget.h"

class QNEBlock;
class SPGraphicsScene;
class SPGraphicsView;
class Form1 : public QMainWindow
{
	Q_OBJECT

	public:		
		explicit Form1(QWidget *parent = 0);
		~Form1();
		
		int ShowContextMenu(const QPoint& pos);
		int ShowNodeMenu(QNEBlock *node);
	
	private:
		
		Ui::MainWindow *ui;


		GLWidget * glwidget;
		QNMainNode * mainNode;
		QNodesEditor * nodesEditor;
		QMenu *fileMenu;
		QGraphicsView *view;
		//SPGraphicsView * view;
		SPGraphicsScene *scene;
		//QGraphicsScene * scene;
		void CreateNodeByType(int typeId, QPoint pos);

		private slots:
			void on_button_clicked();
};

class SPGraphicsScene : public QGraphicsScene
{
private:
	Form1 * form1; // para invocar el menu contextual
public:

	void SetForm1(Form1 * form) { this->form1 = form; };

	void mousePressEvent(QGraphicsSceneMouseEvent * e)
	{
		QGraphicsScene::mousePressEvent(e);
		e->setAccepted(true);
		cout << "SPGraphicsScene  Mouse Pressed Event " << e->scenePos().x() << ", " << e->scenePos().y() << endl;

		if (e->button() == Qt::RightButton)
			form1->ShowContextMenu(e->scenePos().toPoint());
		else
		{
			
		}
	};
};


class SPGraphicsView : public QGraphicsView
{
private:
	Form1 * form1; // para invocar el menu contextual
public:

	void SetForm1(Form1 * form) { this->form1 = form; };

	//void mousePressEvent(QMouseEvent * e)
	//{
	//	
	///*	cout << "SPGraphicsView Mouse Pressed Event " << e->pos().x() << ", " << e->pos().y() << endl;

	//	if (e->button() == Qt::RightButton)
	//		form1->ShowContextMenu(e->pos());
	//	else
	//	{

	//	}*/
	//};
};