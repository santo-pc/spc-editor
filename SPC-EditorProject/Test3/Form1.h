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
#include <qmessagebox.h>
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
		void RefreshNodeEditor();
	
	private:
		
		Ui::MainWindow *ui;


		GLWidget * glwidget;
		QNMainNode * mainNode;
		QNodesEditor * nodesEditor;
		QMenu *fileMenu;
		//QGraphicsView *view;
		SPGraphicsView * view;
		SPGraphicsScene *scene;
		//QGraphicsScene * scene;
		void CreateNodeByType(int typeId, QPoint pos);
		QGridLayout  * oldPropLayout = NULL;
		void ClearLayout(QLayout* layout, bool deleteWidgets);

		bool fistTime = true;
		string	ultimoShader;

		private slots:
			void on_button_clicked();
			void on_buttonCubeMesh_clicked();
			void on_buttonSphereMesh_clicked();
			void on_buttonCylinderMesh_clicked();
			void on_buttonTeaPotMesh_clicked();
			void on_value_changed_lightColorR();
			void on_value_changed_lightColorG();
			void on_value_changed_lightColorB();
			void on_slider_ambient_changed(int value);
			void on_slider_diffuse_changed(int value);
			void on_refresh_nodeEditor();
			void on_showShaderButton();


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

		/*QMessageBox box;
		box.setText("In Scene");
		box.exec();*/

		
		if (e->button() == Qt::RightButton)
		{
			// Si no se esta pulsando control
			if (!e->modifiers())
				form1->ShowContextMenu(e->scenePos().toPoint());
		}
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

	void wheelEvent(QWheelEvent * event)
	{
		if (event->delta() < 0)
			this->scale(0.8, 0.8);
		else if (event->delta() > 0)
			this->scale(1.2, 1.2);
	}
};

