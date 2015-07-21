#include "Form1.h"
#include "glwidget.h"
#include <qgraphicsscene.h>
#include "qneblock.h"
#include "qneport.h"
#include "QNEditorNodes.h"
#include <iostream>



Form1::Form1(QWidget *parent) :   QMainWindow(parent), ui(new Ui::MainWindow)
{
	
	ui->setupUi(this);
	GLWidget * widget = new GLWidget();
	ui->verticalLayoutXX->addWidget(widget);
	
	scene = new QGraphicsScene();
	
	view = new QGraphicsView(ui->dockWidget);
	view->setScene(scene);
	view->setRenderHint(QPainter::Antialiasing, true);

	ui->dockWidget->setWidget(view);
	nodesEditor = new QNodesEditor(this);
	nodesEditor->install(scene);
	

	/*connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));*/
	


	// NODES
	
	mainNode = new QNMainNode(0);
	scene->addItem(mainNode);
	mainNode->Init();




	QNEBlock * nodeVector3 = new QNVector3DNode(0);
	scene->addItem(nodeVector3);
	nodeVector3->Init();

	QNEBlock * nodeFloat = new QNConstFloatNode(0);
	scene->addItem(nodeFloat);
	nodeFloat->Init();

	QNEBlock * nodeVector2 = new QNVector2DNode(0);
	scene->addItem(nodeVector2);
	nodeVector2->Init();
	
	QNEBlock * nodeAdd = new QNAddNode(0);
	scene->addItem(nodeAdd);
	nodeAdd->Init();


	QNEBlock * subNode = new QNSubtractNode(0);
	scene->addItem(subNode);
	subNode->Init();
	
	QNEBlock * multiNode = new QNMultiplyNode(0);
	scene->addItem(multiNode);
	multiNode->Init();

	QNEBlock * powerNode = new QNPowerNode(0);
	scene->addItem(powerNode);
	powerNode->Init();

	QNEBlock * sqrtNode = new QNSqrtNode(0);
	scene->addItem(sqrtNode);
	sqrtNode->Init();

	QNEBlock * logNode = new QNLogNode(0);
	scene->addItem(logNode);
	logNode->Init();


	QNEBlock * minNode = new QNMinNode(0);
	scene->addItem(minNode);
	minNode->Init();

	QNEBlock * maxNode = new QNMaxNode(0);
	scene->addItem(maxNode);
	maxNode->Init();

	QNEBlock * absNode = new QNAbsNode(0);
	scene->addItem(absNode);
	absNode->Init();

	QNEBlock * signNode = new QNSignNode(0);
	scene->addItem(signNode);
	signNode->Init();

	QNEBlock * modNode = new QNModNode(0);
	scene->addItem(modNode);
	modNode->Init();

	QNEBlock * clampNode = new QNClampNode(0);
	scene->addItem(clampNode);
	clampNode->Init();


	QNEBlock * lerpNode = new QNLerpNode(0);
	scene->addItem(lerpNode);
	lerpNode->Init();


	
	mainNode->setPos(0, 0);
	nodeVector3->setPos(0, 50);
	nodeFloat->setPos(150, 100);
	nodeVector2->setPos(0, 150);
	nodeAdd->setPos(150, 200);
	subNode->setPos(0, 250);
	multiNode->setPos(150, 300);
	powerNode->setPos(0, 350);
	sqrtNode->setPos(150, 400);
	minNode->setPos(0, 450);
	maxNode->setPos(150, 500);
	absNode->setPos(0, 550);
	signNode->setPos(150, 600);
	modNode->setPos(0, 650);
	clampNode->setPos(150, 700);
	lerpNode->setPos(0, 750);
	logNode->setPos(150, 750);
}


Form1::~Form1()
{
	delete ui;
}

void Form1::on_button_clicked()
{
	mainNode->Resolve();
}