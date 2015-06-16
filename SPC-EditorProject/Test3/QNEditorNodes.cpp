#include "QNEditorNodes.h"
#include "qneport.h"
#include  <iostream>

/************************** CONST FLOAT NODE **************************/
QNConstFloatNode::QNConstFloatNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNConstFloatNode::Init()
{
	addPort("Value", false, QNEPort::NamePort);
	addOutputPort("Value");
}

QNConstFloatNode ::~QNConstFloatNode()
{
}


/************************** VECTOR 2 NODE **************************/
QNVector2DNode::QNVector2DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNVector2DNode::Init()
{
	addPort("Color RG", false, QNEPort::NamePort);
	addOutputPort("R");
	addOutputPort("G");
}

QNVector2DNode ::~QNVector2DNode()
{
}


/************************** VECTOR 3 NODE **************************/
QNVector3DNode::QNVector3DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNVector3DNode::Init()
{
	addPort("Color RGB",false, QNEPort::NamePort);
	addOutputPort("R");
	addOutputPort("G");
	addOutputPort("B");
}

QNVector3DNode ::~QNVector3DNode()
{
}


/************************** VECTOR 4 NODE **************************/
QNVector4DNode::QNVector4DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNVector4DNode::Init()
{
	addPort("Color RGB", false, QNEPort::NamePort);
	addOutputPort("R");
	addOutputPort("G");
	addOutputPort("B");
	addOutputPort("A");
}

QNVector4DNode ::~QNVector4DNode()
{
}


/************************** TEXTURE NODE **************************/
QNTextureNode::QNTextureNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNTextureNode::Init()
{
	addPort("Texture 2D", false, QNEPort::NamePort);
	addOutputPort("R");
	addOutputPort("G");
	addOutputPort("B");
	addOutputPort("A");
}

QNTextureNode ::~QNTextureNode()
{
}


/************************** ADD NODE **************************/
QNAddNode::QNAddNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNAddNode::Init()
{
	addPort("Add", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("A");
	addInputPort("B");
	
	
}

QNAddNode ::~QNAddNode()
{
}


/************************** SUBTRACT NODE **************************/
QNSubtractNode::QNSubtractNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNSubtractNode::Init()
{
	addPort("Subs", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("A");
	addInputPort("B");


}

QNSubtractNode ::~QNSubtractNode()
{
}


/************************** MULTIPLY NODE **************************/
QNMultiplyNode::QNMultiplyNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNMultiplyNode::Init()
{
	addPort("Multiply", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("A");
	addInputPort("B");

}

QNMultiplyNode ::~QNMultiplyNode()
{
}

/************************** POWER NODE **************************/
QNPowerNode::QNPowerNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNPowerNode::Init()
{
	addPort("Power", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("Val");
	addInputPort("Exp");

}

QNPowerNode ::~QNPowerNode()
{
}


/************************** SQRT NODE **************************/
QNSqrtNode::QNSqrtNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNSqrtNode::Init()
{
	addPort("Sqrt", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("Val");
}

QNSqrtNode ::~QNSqrtNode()
{
}

/************************** LOG NODE **************************/
QNLogNode::QNLogNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNLogNode::Init()
{
	addPort("Log", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("Val");
}

QNLogNode ::~QNLogNode()
{
}


/************************** MIN NODE **************************/
QNMinNode::QNMinNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNMinNode::Init()
{
	addPort("Min", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("A");
	addInputPort("B");
}

QNMinNode ::~QNMinNode()
{
}

/************************** MAX NODE **************************/
QNMaxNode::QNMaxNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNMaxNode::Init()
{
	addPort("Max", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("A");
	addInputPort("B");
}

QNMaxNode ::~QNMaxNode()
{
}

/************************** ABS NODE **************************/
QNAbsNode::QNAbsNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNAbsNode::Init()
{
	addPort("Abs", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("Val");
}

QNAbsNode ::~QNAbsNode()
{
}

/************************** SIGN NODE **************************/
QNSignNode::QNSignNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNSignNode::Init()
{
	addPort("Sign", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("Val");
}

QNSignNode ::~QNSignNode()
{
}


/************************** MOD NODE **************************/
QNModNode::QNModNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNModNode::Init()
{
	addPort("Mod", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("A");
	addInputPort("B");
}

QNModNode ::~QNModNode()
{
}


/************************** CLAMP NODE **************************/
QNClampNode::QNClampNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNClampNode::Init()
{
	addPort("Clamp", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("Val");
	addInputPort("Min");
	addInputPort("Max");

}

QNClampNode ::~QNClampNode()
{
}


/************************** LERP NODE **************************/
QNLerpNode::QNLerpNode(QGraphicsItem *parent) : QNEBlock(parent)
{
}

void QNLerpNode::Init()
{
	addPort("Lerp", false, QNEPort::NamePort);
	addOutputPort("");
	addInputPort("A");
	addInputPort("B");
	addInputPort("T");

}

QNLerpNode ::~QNLerpNode()
{
}







