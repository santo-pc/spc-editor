#include "QNEditorNodes.h"
#include "qneport.h"
#include <qmessagebox.h>
#include  <iostream>
#include <qneconnection.h>
#include "StringsAndDefines.h"
#include "ShaderComposer.h"

/************************** MAIN NODE **************************/
QNMainNode::QNMainNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "Main Node";
	m_type = ID_TYPE_SPMainNode;
	

}

void QNMainNode::Init()
{
	addPort("Main Node", false, QNEPort::NamePort);
	ColorBasePort = addInputPort("Color");
	SpecularPort = addInputPort("Specular");
	NormalPort = addInputPort("Normal");
	AlphaPort = addInputPort("Alpha");
	
}
std::string QNMainNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("Main Node Resolve");
	msgBox.exec();

	string colorValueString = "";
	string specularValueString = "";
	string normalValueString = "";
	string alphaValueString = "";
	
	// Para las conexiones
	QNEConnection	* auxCon = NULL;
	QNEBlock		* auxNode = NULL;

	// Para COLOR
	// Get the first edge conector
	auxCon = ColorBasePort->connections().at(0);		
	if (auxCon)
	{
		auxNode = auxCon->port1()->block();

		if (auxNode)
		{
			colorValueString = auxNode->Resolve();
		}
	}

	
	string result =
		"vec3 SPMainNode()\n"
		"{"
		"	vec4 colorBase = " + colorValueString + ";\n"
		"	vec4 specular = " + specularValueString + ";\n"
		"	vec4 normal = " + normalValueString + ";\n"
		"	vec4 alpha = " + alphaValueString + ";\n"
		"}"
		;


		
	return result;
	

}

QNMainNode ::~QNMainNode()
{
}


/************************** CONST FLOAT NODE **************************/
QNConstFloatNode::QNConstFloatNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "QNConstFloatNode";
	m_type = ID_TYPE_SPConstFloatNode;
}

void QNConstFloatNode::Init()
{
	addPort("Value", false, QNEPort::NamePort);
	addOutputPort("Value");
}

std::string QNConstFloatNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("ConstFloatNode Resolve");
	msgBox.exec();
	
	string result;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string valueString = ConvertIntToString(value);	
	
	// 2. Componer su condigo
	//	const float MAX_NUM_LIGHTS = 8; // max number of lights
	result = "const float " + nameMember + " = " + valueString + ";\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeConst(this, result); // en este caso a AppendCodeConst


	// 4. Devolver siempre el nombre le miembro
	return nameMember;
}

QNConstFloatNode ::~QNConstFloatNode()
{
}




/************************** VECTOR 2 NODE **************************/
QNVector2DNode::QNVector2DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "QNVector2DNode";
	m_type = ID_TYPE_SPVector2DNode;
}

void QNVector2DNode::Init()
{
	addPort("Color RG", false, QNEPort::NamePort);
	addOutputPort("R");
	addOutputPort("G");
}

std::string QNVector2DNode::Resolve()
{
	return "";
}
QNVector2DNode ::~QNVector2DNode()
{
}


/************************** VECTOR 3 NODE **************************/
QNVector3DNode::QNVector3DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "QNVector3DNode";
	m_type = ID_TYPE_SPVector3DNode;
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
	titulo = "QNVector4DNode";
	m_type = ID_TYPE_SPVector4DNode;
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
	titulo = "QNTextureNode";
	m_type = ID_TYPE_SPTextureNode;
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
	titulo = "QNAddNode";
	m_type = ID_TYPE_SPAddNode;
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
	titulo = "QNSubstract";
	m_type = ID_TYPE_SPSubtractNode;
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
	titulo = "Multiply";
	m_type = ID_TYPE_SPMultiplyNode;
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
	titulo = "QNPowerNode";
	m_type = ID_TYPE_SPPowerNode;
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
	titulo = "Sqrt";
	m_type = ID_TYPE_SPSqrtNode;
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
	titulo = "Log";
	m_type = ID_TYPE_SPLogNode;
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
	titulo = "Min";
	m_type = ID_TYPE_SPMinNode;
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
	titulo = "Max";
	m_type = ID_TYPE_SPMaxNode;
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
	titulo = "Abs";
	m_type = ID_TYPE_SPAbsNode;
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
	titulo = "Sign";
	m_type = ID_TYPE_SPSignNode;
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
	titulo = "Mod";
	m_type = ID_TYPE_SPModNode;
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
	titulo = "Clamp";
	m_type = ID_TYPE_SPClampNode;
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
	titulo = "Lerp";
	m_type = ID_TYPE_SPLerpNode;
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







