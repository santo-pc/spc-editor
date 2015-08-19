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
	APort = addInputPort("A");
	BPort = addInputPort("B");
	
	
	
}

QNAddNode ::~QNAddNode()
{
}

std::string QNAddNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNAddNode Resolve");
	msgBox.exec();

	string codeDefinition;
	
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	

	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);
	
	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = " + aValueString + ";\n"
		"	vec4 B = " + bValueString + ";\n"
		"	return A + B;\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	APort = addInputPort("A");
	BPort = addInputPort("B");


}

QNSubtractNode ::~QNSubtractNode()
{
}

std::string QNSubtractNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNSubtractNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = " + aValueString + ";\n"
		"	vec4 B = " + bValueString + ";\n"
		"	return A - B;\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	APort = addInputPort("A");
	BPort = addInputPort("B");

}

QNMultiplyNode ::~QNMultiplyNode()
{
}
std::string QNMultiplyNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNMultiplyNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = " + aValueString + ";\n"
		"	vec4 B = " + bValueString + ";\n"
		"	return A * B;\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	ValuePort =  addInputPort("Val");
	ExpPort = addInputPort("Exp");

}

QNPowerNode ::~QNPowerNode()
{
}

std::string QNPowerNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNMultiplyNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValuePort);
	string ExpValueString = GetMemberStringByPort(ExpPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = " + ValueString + ";\n"
		"	vec4 exp = " + ExpValueString + ";\n"
		"	return vec4(pow(val.r, exp), pow(val.g, exp), pow(val.b, exp),pow(val.a, exp)) ;\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	ValPort = addInputPort("Val");
}

QNSqrtNode ::~QNSqrtNode()
{
}

std::string QNSqrtNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNSqrtNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValPort);
	

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = " + ValueString + ";\n"		
		"	return vec4(sqrt(val));\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	ValPort = addInputPort("Val");
}

QNLogNode ::~QNLogNode()
{
}

std::string QNLogNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNLogNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValPort);


	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = " + ValueString + ";\n"
		"	return vec4(log(val));\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	APort = addInputPort("A");
	BPort = addInputPort("B");
}

QNMinNode ::~QNMinNode()
{
}

std::string QNMinNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNMinNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = " + aValueString + ";\n"
		"	vec4 B = " + bValueString + ";\n"
		"	return min(A, B) ;\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	APort = addInputPort("A");
	BPort = addInputPort("B");
}

QNMaxNode ::~QNMaxNode()
{
}

std::string QNMaxNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNMaxNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = " + aValueString + ";\n"
		"	vec4 B = " + bValueString + ";\n"
		"	return max(A, B);\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	ValPort = addInputPort("Val");
}

QNAbsNode ::~QNAbsNode()
{
}

std::string QNAbsNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNAbsNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValPort);


	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = " + ValueString + ";\n"
		"	return vec4(abs(val));\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	ValPort = addInputPort("Val");
}

QNSignNode ::~QNSignNode()
{
}

std::string QNSignNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNSignNode Resolve");
	msgBox.exec();
	cout << "sign resolve1" << endl;
	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);

	cout << "sign resolve2" << endl;
	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValPort);

	cout << "sign resolve3" << endl;
	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = " + ValueString + ";\n"
		"	return vec4(sign(val));\n"
		"}\n";


	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction
	cout << "sign resolve4" << endl;
	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	APort = addInputPort("A");
	BPort = addInputPort("B");
}

QNModNode ::~QNModNode()
{
}

std::string QNModNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNModNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = " + aValueString + ";\n"
		"	vec4 B = " + bValueString + ";\n"
		"	return mod(A, B);\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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


	ValPort = addInputPort("Val");
	MinPort = addInputPort("Min");
	MaxPort = addInputPort("Max");

}

QNClampNode ::~QNClampNode()
{
}

std::string QNClampNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNClampNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string valValueString = GetMemberStringByPort(ValPort);
	string minValueString = GetMemberStringByPort(MinPort);
	string maxValueString = GetMemberStringByPort(MaxPort);


	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 Val = " + valValueString + ";\n"
		"	vec4 Min = " + minValueString + ";\n"
		"	vec4 Max = " + maxValueString + ";\n"
		"	return clamp(Val, Min, Max);\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
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
	
	ValXPort = addInputPort("A");
	ValYPort = addInputPort("B");
	TPort = addInputPort("T");

}

QNLerpNode ::~QNLerpNode()
{
}

std::string QNLerpNode::Resolve()
{
	QMessageBox msgBox;
	msgBox.setText("QNLerpNode Resolve");
	msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string valXValueString = GetMemberStringByPort(ValXPort);
	string valYValueString = GetMemberStringByPort(ValYPort);
	string tValueString = GetMemberStringByPort(TPort);


	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 ValX = " + valXValueString + ";\n"
		"	vec4 Valy = " + valYValueString + ";\n"
		"	vec4 t = " + tValueString + ";\n"
		"	return mix(ValX, Valy, t);\n"
		"}\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeFunction(this, codeDefinition); // en este caso a AppendCodeFunction

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
}







