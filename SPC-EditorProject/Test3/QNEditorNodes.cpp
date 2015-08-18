#include "QNEditorNodes.h"
#include "qneport.h"
#include <qmessagebox.h>
#include  <iostream>
#include <qneconnection.h>
#include "StringsAndDefines.h"
#include "ShaderComposer.h"

static std::string GetSuffixByNodeType(int type)
{
	string suffix = "";
	switch (type)
	{
		// const values case
		case ID_TYPE_SPConstFloatNode:
		case ID_TYPE_SPVector2DNode:
		case ID_TYPE_SPVector3DNode:
		case ID_TYPE_SPVector4DNode:
			suffix = "";
			break;

		default: // Default Case for Functions
			suffix = "()";
			break;
	}

	return suffix;
}

// Util Function, used for get the name of the conected member by a certain port of a node
static std::string GetMemberStringByPort(QNEPort * port)
{
	std::string memberNameResult = "ERROR GETTIG CONECTION MEMBER'S NAME";
	
	if (!port) 
		return memberNameResult;

	QNEConnection	* auxCon = NULL;	// Edge connection
	QNEBlock		* auxNode = NULL;	// Node connected 

	// Get the first edge conector
	auxCon = port->connections().at(0);
	if (auxCon)
	{
		auxNode = auxCon->port1()->block();

		if (auxNode)
		{
			memberNameResult = auxNode->Resolve();
			std::string suffix = GetSuffixByNodeType(auxNode->GetType());
			memberNameResult += suffix;

			return memberNameResult;
		}
	}

	return "NO CONNECTION MADE";

}

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

	string colorValueString = GetMemberStringByPort(ColorBasePort);
	string specularValueString = GetMemberStringByPort(SpecularPort);
	string normalValueString = GetMemberStringByPort(NormalPort);
	string alphaValueString = GetMemberStringByPort(AlphaPort);
	
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
	
	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string valueString = ConvertIntToString(value);	
	
	// 2. Componer el codigo de este nodo
	//	const float MAX_NUM_LIGHTS = 8; // max number of lights
	codeDefinition = "const float " + nameMember + " = " + valueString + ";\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeConst(this, codeDefinition); // en este caso a AppendCodeConst

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
	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string rValueString = ConvertIntToString(value.r);
	string gValueString = ConvertIntToString(value.g);

	// 2. Componer el codigo de este nodo
	//	const float MAX_NUM_LIGHTS = 8; // max number of lights
	codeDefinition = "const vec2 " + nameMember + " = vec2(" + rValueString + ", " + gValueString + ");\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeConst(this, codeDefinition); // en este caso a AppendCodeConst

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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

std::string QNVector3DNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNVector3DNode Resolve");
	msgBox.exec();

	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string rValueString = ConvertIntToString(value.r);
	string gValueString = ConvertIntToString(value.g);
	string bValueString = ConvertIntToString(value.b);

	// 2. Componer el codigo de este nodo
	//	const float MAX_NUM_LIGHTS = 8; // max number of lights
	codeDefinition = "const vec3 " + nameMember + " = vec3(" + rValueString + ", " + gValueString + ", " + bValueString + ");\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeConst(this, codeDefinition); // en este caso a AppendCodeConst

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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

std::string QNVector4DNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNVector4DNode Resolve");
	msgBox.exec();

	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string rValueString = ConvertIntToString(value.r);
	string gValueString = ConvertIntToString(value.g);
	string bValueString = ConvertIntToString(value.b);
	string aValueString = ConvertIntToString(value.a);

	// 2. Componer el codigo de este nodo
	//	const float MAX_NUM_LIGHTS = 8; // max number of lights
	codeDefinition = "const vec4 " + nameMember + " = vec4(" + rValueString + ", " + gValueString + ", " + bValueString + ", " + aValueString + ");\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeConst(this, codeDefinition); // en este caso a AppendCodeConst

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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







