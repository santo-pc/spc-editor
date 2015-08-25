#include "Form1.h"
#include "glwidget.h"
#include <qgraphicsscene.h>
#include "qneblock.h"
#include "qneport.h"
#include "QNEditorNodes.h"
#include <iostream>
#include "StringsAndDefines.h"
#include "ShaderComposer.h"
#include "qapplication.h"
#include "qmessagebox.h"

#include <qgridlayout.h>
#include "qneblock.h"

Form1::Form1(QWidget *parent) :   QMainWindow(parent), ui(new Ui::MainWindow)
{
	
	ui->setupUi(this);
	glwidget = new GLWidget();
	ui->verticalLayoutXX->addWidget(glwidget);
	
	scene = new SPGraphicsScene();
	scene->SetForm1(this);

	QFont * fontType = new QFont("Arial", 12, QFont::Light, true);

	scene->setFont(*fontType);
	//scene = new QGraphicsScene();

	//view = new QGraphicsView(ui->dockNodeEditor);
	view = new SPGraphicsView();
	//view->setParent(ui->dockWidget);
	//view->SetForm1(this);
	view->setScene(scene);
	view->setRenderHint(QPainter::Antialiasing, true);
	view->setBackgroundBrush(QBrush(QColor(27, 36, 46)));

	ui->dockNodeEditor->setWidget(view);
	nodesEditor = new QNodesEditor(this);
	nodesEditor->install(scene);
	
	QSize rec = this->size();
	float height = rec.height();
	float width = rec.width();


	string sizeString = ConvertIntToString(width) + " " + ConvertIntToString(height);
	
	
	/*QMessageBox msgBox;
	msgBox.setText(QString( sizeString.c_str() ));
	msgBox.exec();*/

	// Poner iconos a los buttons
	QPixmap pixmap("../../Resources/Icons/sphere64.png");
	QIcon ButtonIcon(pixmap);
	ui->pushButtonMallaSphere->setIcon(ButtonIcon);
	ui->pushButtonMallaSphere->setIconSize(QSize(28,28));
	QPixmap pixmap2("../../Resources/Icons/cube64.png");
	QIcon ButtonIcon2(pixmap2);
	ui->pushButtonMallaCube->setIcon(ButtonIcon2);
	ui->pushButtonMallaCube->setIconSize(QSize(28, 28));
	QPixmap pixmap3("../../Resources/Icons/cylinder64.png");
	QIcon ButtonIcon3(pixmap3);
	ui->pushButtonMallaCylinder->setIcon(ButtonIcon3);
	ui->pushButtonMallaCylinder->setIconSize(QSize(28, 28));
	QPixmap pixmap4("../../Resources/Icons/teapot64.png");
	QIcon ButtonIcon4(pixmap4);
	ui->pushButtonMallaTeaPot->setIcon(ButtonIcon4);
	ui->pushButtonMallaTeaPot->setIconSize(QSize(28, 28));

	// NODES
	
	mainNode = new QNMainNode(0);
	scene->addItem(mainNode);
	mainNode->Init();
	mainNode->setPos(0, 0);
	mainNode->SetForm1(this);


}


Form1::~Form1()
{
	delete ui;
}

void Form1::on_button_clicked()
{
	SHADER_COMPOSER->ClearAll();

	string mainString = mainNode->Resolve();

	string cadenaX = STRINGDEFINES->SampleFragmet();

	cout << "Pintando cadena\n\n" << cadenaX << endl;	

	std::string result = SHADER_COMPOSER->Compose(mainString);

	glwidget->RebuildShader(result);

	SaveShaderToFile(result, "shaderResult.fs");

	cout << "FIN BUTTON" << endl;
	
}


int Form1::ShowContextMenu(const QPoint& pos)
{
	// for most widgets
	//QPoint globalPos = ui->dockWidget->mapToGlobal(pos);
	//QPoint globalPos = ui->centralwidget->mapFromGlobal(pos);
	//QPoint globalPos = view->viewport()->mapToGlobal(pos);
	//QPoint globalPos = pos;
	QPoint globalPos = QCursor::pos();
	// for QAbstractScrollArea and derived classes you would use:
	// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);
	
	QAction * floatAction = new QAction("Float", this); floatAction->setData(QVariant(ID_TYPE_SPConstFloatNode));
	QAction * Vector2 = new QAction("Vector2", this);	Vector2->setData(QVariant(ID_TYPE_SPVector2DNode));
	QAction * Vector3 = new QAction("Vector3", this); 	Vector3->setData(QVariant(ID_TYPE_SPVector3DNode));
	QAction * Vector4 = new QAction("Vector4", this); 	Vector4->setData(QVariant(ID_TYPE_SPVector4DNode));
	QAction * Texture = new QAction("Texture", this); 	Texture->setData(QVariant(ID_TYPE_SPTextureNode));
	QAction * Add = new QAction("Add", this);			Add->setData(QVariant(ID_TYPE_SPAddNode));
	QAction * Subtract = new QAction("Subtract", this); Subtract->setData(QVariant(ID_TYPE_SPSubtractNode));
	QAction * Multiply = new QAction("Multiply", this); Multiply->setData(QVariant(ID_TYPE_SPMultiplyNode));
	QAction * Power = new QAction("Power", this);		Power->setData(QVariant(ID_TYPE_SPPowerNode));
	QAction * Sqrt = new QAction("Sqrt", this);			Sqrt->setData(QVariant(ID_TYPE_SPSqrtNode));
	QAction * Log = new QAction("Log", this);			Log->setData(QVariant(ID_TYPE_SPLogNode));
	QAction * Min = new QAction("Min", this);			Min->setData(QVariant(ID_TYPE_SPMinNode));
	QAction * Max = new QAction("Max", this);			Max->setData(QVariant(ID_TYPE_SPMaxNode));
	QAction * Abs = new QAction("Abs", this);			Abs->setData(QVariant(ID_TYPE_SPAbsNode));
	QAction * Sign = new QAction("Sign", this);			Sign->setData(QVariant(ID_TYPE_SPSignNode));
	QAction * Mod = new QAction("Mod", this);			Mod->setData(QVariant(ID_TYPE_SPModNode));
	QAction * Clamp = new QAction("Clamp", this);		Clamp->setData(QVariant(ID_TYPE_SPClampNode));
	QAction * Lerp = new QAction("Lerp", this);			Lerp->setData(QVariant(ID_TYPE_SPLerpNode));

	QMenu myMenu;	
	myMenu.addAction(floatAction);
	myMenu.addAction(Vector2);
	myMenu.addAction(Vector3);
	myMenu.addAction(Vector4);
	myMenu.addAction(Texture);
	myMenu.addAction(Add);
	myMenu.addAction(Subtract);
	myMenu.addAction(Multiply);
	myMenu.addAction(Power);
	myMenu.addAction(Sqrt);
	myMenu.addAction(Log);
	myMenu.addAction(Min);
	myMenu.addAction(Max);
	myMenu.addAction(Abs);
	myMenu.addAction(Sign);
	myMenu.addAction(Mod);
	myMenu.addAction(Clamp);
	myMenu.addAction(Lerp);		

	QAction* selectedItem = myMenu.exec(globalPos);
	

	if (selectedItem)
	{
		// something was chosen, do stuff
		cout << "Opcion" << endl;
		int type = (int)selectedItem->data().toInt();
		cout << "ID TYPE " << type << endl;
		CreateNodeByType(type, pos);
	}
	else
	{
		// nothing was chosen
		cout << "No opcion" << endl;
	}
	return 1;
}

void Form1::CreateNodeByType(int typeId, QPoint pos)
{
	QNEBlock * node;
	
	switch (typeId)
	{
		case ID_TYPE_SPConstFloatNode:
			node = new QNConstFloatNode(0);			
			break;
		case ID_TYPE_SPVector2DNode:
			node = new QNVector2DNode(0);
			break;

		case ID_TYPE_SPVector3DNode:
			node = new QNVector3DNode(0);
			break;

		case ID_TYPE_SPVector4DNode:
			node = new QNVector4DNode(0);
			break;

		case ID_TYPE_SPTextureNode:
			node = new QNTextureNode(0);
			break;

		case ID_TYPE_SPAddNode:
			node = new QNAddNode(0);
			break;

		case ID_TYPE_SPSubtractNode:
			node = new QNSubtractNode(0);
			break;

		case ID_TYPE_SPMultiplyNode:
			node = new QNMultiplyNode(0);
			break;

		case ID_TYPE_SPPowerNode:
			node = new QNPowerNode(0);
			break;

		case ID_TYPE_SPSqrtNode:
			node = new QNSqrtNode(0);
			break;

		case ID_TYPE_SPLogNode:
			node = new QNLogNode(0);
			break;

		case ID_TYPE_SPMinNode:
			node = new QNMinNode(0);
			break;

		case ID_TYPE_SPMaxNode:
			node = new QNMaxNode(0);
			break;

		case ID_TYPE_SPAbsNode:
			node = new QNAbsNode(0);
			break;

		case ID_TYPE_SPSignNode:
			node = new QNSignNode(0);
			break;

		case ID_TYPE_SPModNode:
			node = new QNModNode(0);
			break;

		case ID_TYPE_SPClampNode:
			node = new QNClampNode(0);
			break;

		case ID_TYPE_SPLerpNode:
			node = new QNLerpNode(0);
			break;

	}

	scene->addItem(node);
	node->Init();
	node->setPos(pos.x(), pos.y());
	node->SetForm1(this);


	
}


int Form1::ShowNodeMenu(QNEBlock *node)
{
	/*QMessageBox msgBox;
	msgBox.setText("Show Menu");
	msgBox.exec();*/
	
	// Limpiar si toca
	if (oldPropLayout)
	{
		ClearLayout(oldPropLayout, true);
		delete oldPropLayout;
		oldPropLayout = NULL;
	}
	
	// Obtener el formulario en forma de QGridLayOut que el nodo responde
	oldPropLayout = node->GetPropertiesForm();
		
	/*propForm->setParent(ui->dockProperties);
	ui->dockProperties->setLayout(propForm);*/
	ui->dockWidgetProperties_3->widget()->setLayout(oldPropLayout);
	//ui->dockProperties1->*/
	/*ui->d*/
	//ui->dock
	return true;
}

void Form1::ClearLayout(QLayout* layout, bool deleteWidgets = true)
{
	while (QLayoutItem* item = layout->takeAt(0))
	{
		if (deleteWidgets)
		{
			if (QWidget* widget = item->widget())
				delete widget;
		}
		
		if (QLayout* childLayout = item->layout())
			ClearLayout(childLayout, deleteWidgets);
		
		delete item;
	}
}

void Form1::on_buttonCubeMesh_clicked()
{
	this->glwidget->ActiveMeshCube();
	/*QMessageBox box;
	box.setText("Cube");
	box.exec();*/
}
void Form1::on_buttonSphereMesh_clicked()
{
	//QMessageBox box;
	//box.setText("Sphere");
	//box.exec();
	this->glwidget->ActiveMeshSphere();
}

void Form1::on_buttonCylinderMesh_clicked()
{
	this->glwidget->ActiveMeshCylinder();
	//QMessageBox box;
	//box.setText("Cylinder");
	//box.exec();
}
void Form1::on_buttonTeaPotMesh_clicked()
{	
	this->glwidget->ActiveMeshTeaPot();
	/*QMessageBox box;
	box.setText("TeaPot");
	box.exec();*/
}