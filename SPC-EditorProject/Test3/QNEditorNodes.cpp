#include "QNEditorNodes.h"
#include "qneport.h"
#include <qmessagebox.h>
#include  <iostream>
#include <qneconnection.h>
#include "StringsAndDefines.h"
#include "ShaderComposer.h"
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qlabel.h>

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
		"void main() \n"
		"{"
		"	vec4 colorBase = vec4(" + colorValueString + ");\n"
		"	vec4 specularLvl = vec4(" + specularValueString + ");\n"
		"	vec4 normal = vec4(" + normalValueString + ");\n"
		"	vec4 alpha = vec4(" + alphaValueString + ");\n"
		"	vec4 lightIntensity = vec4(0.0);"
		"\n"
		"	vec4 colorAux = vec4(0.0);\n"
		"\n"
		"	lightIntensity += BlinnPhong(0, colorBase.rgb, normal.rgb, specularLvl.rgb);\n"
		"\n"
		"	FragColor = lightIntensity;\n"
		"\n"
		"	FragColor.a = alpha.a;\n"
		"\n"
		"}\n"
		;


		
	return result;
	

}

QNMainNode ::~QNMainNode()
{
}

QGridLayout *  QNMainNode::GetPropertiesForm()
{

	QSizePolicy * policy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSize minSizeField = QSize(150, 25); QSize maxSizeField = QSize(200, 25);
	QSize minSizeLabel = QSize(50, 25);	QSize maxSizeLabel = QSize(50, 25);
	

	QTextEdit * button1 = new QTextEdit("Button 1"); button1->setSizePolicy(*policy); button1->setMinimumSize(minSizeField); button1->setMaximumSize(maxSizeField);
	QTextEdit * button2 = new QTextEdit("Button 2"); button2->setSizePolicy(*policy); button2->setMinimumSize(minSizeField); button2->setMaximumSize(maxSizeField);
	QTextEdit * button3 = new QTextEdit("Button 3"); button3->setSizePolicy(*policy); button3->setMinimumSize(minSizeField); button3->setMaximumSize(maxSizeField);
	QTextEdit * button4 = new QTextEdit("Button 4"); button4->setSizePolicy(*policy); button4->setMinimumSize(minSizeField); button4->setMaximumSize(maxSizeField);

	QObject::connect(button1, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(button2, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(button3, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(button4, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Field1"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	QLabel * label2 = new QLabel("Field2");	label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	QLabel * label3 = new QLabel("Field3");	label3->setMinimumSize(minSizeLabel); label3->setMaximumSize(maxSizeLabel);
	QLabel * label4 = new QLabel("Field4");	label4->setMinimumSize(minSizeLabel); label4->setMaximumSize(maxSizeLabel);

	QGridLayout * propForm = new QGridLayout(); 

	propForm->addWidget(label1, 0, 0);	propForm->addWidget(label2, 1, 0);
	propForm->addWidget(label3, 2, 0);	propForm->addWidget(label4, 3, 0);

	propForm->addWidget(button1, 0, 1); propForm->addWidget(button2, 1, 1);
	propForm->addWidget(button3, 2, 1);	propForm->addWidget(button4, 3, 1);
	
	
	// Para que la 4 fila ocupe el resto del layout
	propForm->setRowStretch(4, 1);
	propForm->setMargin(10);	
	propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNMainNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNConstFloatNode::GetPropertiesForm()
{

	// 1. Create Controls
	descTextEdit = new QTextEdit("");	descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	valueTextEdit = new QTextEdit(""); valueTextEdit->setSizePolicy(*policy); valueTextEdit->setMinimumSize(minSizeField); valueTextEdit->setMaximumSize(maxSizeField);
	

	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(valueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	
	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	QLabel * label2 = new QLabel("Value:"); label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	
	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0); 	propForm->addWidget(label2, 1, 0);


	propForm->addWidget(descTextEdit, 0, 1);
	propForm->addWidget(valueTextEdit, 1, 1);
	
	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNConstFloatNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();
	
	description = descTextEdit->placeholderText().toStdString();
	value = valueTextEdit->toPlainText().toFloat();

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


QGridLayout *  QNVector2DNode::GetPropertiesForm()
{

	// 1. Create Controls
	descTextEdit = new QTextEdit("");	descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	rValueTextEdit = new QTextEdit(""); rValueTextEdit->setSizePolicy(*policy); rValueTextEdit->setMinimumSize(minSizeField); rValueTextEdit->setMaximumSize(maxSizeField);
	gValueTextEdit = new QTextEdit(""); gValueTextEdit->setSizePolicy(*policy); gValueTextEdit->setMinimumSize(minSizeField); gValueTextEdit->setMaximumSize(maxSizeField);
	

	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(rValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(gValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	
	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	QLabel * label2 = new QLabel("R:"); label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	QLabel * label3 = new QLabel("G:"); label2->setMinimumSize(minSizeLabel); label3->setMaximumSize(maxSizeLabel);
	
	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0); 	propForm->addWidget(label2, 1, 0);
	propForm->addWidget(label3, 2, 0);
	propForm->addWidget(descTextEdit, 0, 1);
	propForm->addWidget(rValueTextEdit, 1, 1);
	propForm->addWidget(gValueTextEdit, 2, 1);
	
	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;
	

}

void QNVector2DNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNVector3DNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit("");	descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	rValueTextEdit = new QTextEdit(""); rValueTextEdit->setSizePolicy(*policy); rValueTextEdit->setMinimumSize(minSizeField); rValueTextEdit->setMaximumSize(maxSizeField);
	gValueTextEdit = new QTextEdit(""); gValueTextEdit->setSizePolicy(*policy); gValueTextEdit->setMinimumSize(minSizeField); gValueTextEdit->setMaximumSize(maxSizeField);
	bValueTextEdit = new QTextEdit(""); bValueTextEdit->setSizePolicy(*policy); bValueTextEdit->setMinimumSize(minSizeField); bValueTextEdit->setMaximumSize(maxSizeField);
	

	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(rValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(gValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(bValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	QLabel * label2 = new QLabel("R:"); label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	QLabel * label3 = new QLabel("G:"); label2->setMinimumSize(minSizeLabel); label3->setMaximumSize(maxSizeLabel);
	QLabel * label4 = new QLabel("B:"); label2->setMinimumSize(minSizeLabel); label4->setMaximumSize(maxSizeLabel);
	

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0); 	propForm->addWidget(label2, 1, 0);
	propForm->addWidget(label3, 2, 0);	propForm->addWidget(label4, 3, 0);
	

	propForm->addWidget(descTextEdit, 0, 1);
	propForm->addWidget(rValueTextEdit, 1, 1);
	propForm->addWidget(gValueTextEdit, 2, 1);
	propForm->addWidget(bValueTextEdit, 3, 1);
	

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNVector3DNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNVector4DNode::GetPropertiesForm()
{
	
	// 1. Create Controls
	descTextEdit = new QTextEdit("");	descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	rValueTextEdit = new QTextEdit(""); rValueTextEdit->setSizePolicy(*policy); rValueTextEdit->setMinimumSize(minSizeField); rValueTextEdit->setMaximumSize(maxSizeField);
	gValueTextEdit = new QTextEdit(""); gValueTextEdit->setSizePolicy(*policy); gValueTextEdit->setMinimumSize(minSizeField); gValueTextEdit->setMaximumSize(maxSizeField);
	bValueTextEdit = new QTextEdit(""); bValueTextEdit->setSizePolicy(*policy); bValueTextEdit->setMinimumSize(minSizeField); bValueTextEdit->setMaximumSize(maxSizeField);
	aValueTextEdit = new QTextEdit(""); aValueTextEdit->setSizePolicy(*policy); aValueTextEdit->setMinimumSize(minSizeField); aValueTextEdit->setMaximumSize(maxSizeField);
	
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(rValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(gValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(bValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	QObject::connect(aValueTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	QLabel * label2 = new QLabel("R:"); label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	QLabel * label3 = new QLabel("G:"); label2->setMinimumSize(minSizeLabel); label3->setMaximumSize(maxSizeLabel);
	QLabel * label4 = new QLabel("B:"); label2->setMinimumSize(minSizeLabel); label4->setMaximumSize(maxSizeLabel);
	QLabel * label5 = new QLabel("A:"); label2->setMinimumSize(minSizeLabel); label5->setMaximumSize(maxSizeLabel);
	     
	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0); 	propForm->addWidget(label2, 1, 0);
	propForm->addWidget(label3, 2, 0);	propForm->addWidget(label4, 3, 0);
	propForm->addWidget(label5, 4, 0);

	propForm->addWidget(descTextEdit, 0, 1);
	propForm->addWidget(rValueTextEdit, 1, 1);
	propForm->addWidget(gValueTextEdit, 2, 1);
	propForm->addWidget(bValueTextEdit, 3, 1);
	propForm->addWidget(aValueTextEdit, 4, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNVector4DNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNTextureNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNTextureNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNAddNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNAddNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNSubtractNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNSubtractNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNMultiplyNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNMultiplyNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNPowerNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNPowerNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNSqrtNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNSqrtNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNLogNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNLogNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNMinNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNMinNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNMaxNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNMaxNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNAbsNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNAbsNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNSignNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNSignNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();

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

QGridLayout *  QNModNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNModNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();
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

QGridLayout *  QNClampNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNClampNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();
	
	description = descTextEdit->placeholderText().toStdString();
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

QGridLayout *  QNLerpNode::GetPropertiesForm()
{



	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(descTextEdit, 0, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNLerpNode::HandleLostFocusMembers()
{
	QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();

	description = descTextEdit->placeholderText().toStdString();
}








