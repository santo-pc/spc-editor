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
#include <qvalidator.h>
#include <qfiledialog.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include "Form1.h"

static QLineEdit * CreateMyNumericLineEdit(float value, QNEBlock * nodeOwner)
{
	QLineEdit * lineEdit = new QLineEdit(ConvertFloatToString(value).c_str()); 
	lineEdit->setSizePolicy(*nodeOwner->policy);
	lineEdit->setMinimumSize(nodeOwner->minSizeField);
	lineEdit->setMaximumSize(nodeOwner->maxSizeField);
	lineEdit->setValidator(nodeOwner->floatValidator);

	QObject::connect(lineEdit, &QLineEdit::textChanged, nodeOwner, &QNEBlock::HandleLostFocusMembers);	
	

	return lineEdit;
	
}
static void GetPreffixAndSuffixByNodeType(int type, QNEPort * outPut, std::string &preffix, std::string &suffix)
{
	suffix = "";
	preffix = "";

	switch (type)
	{
		// const values case
		case ID_TYPE_SPConstFloatNode:
		case ID_TYPE_SPVector2DNode:
		case ID_TYPE_SPVector3DNode:
		case ID_TYPE_SPVector4DNode:
			suffix = "";
			preffix = "";
			break;
		case ID_TYPE_SPTextureNode:
			suffix = ", TexCoord)";
			preffix = "texture(";
			break;
		default: // Default Case for Functions
			suffix = "()";
			preffix = "";
			break;
	}
	
	//if (type == ID_TYPE_SPTextureNode)
	//{
	//	QMessageBox box;
	//	box.setText(outPut->portName());
	//	box.exec();
	//}
	// determinar el componente conectado usando el miembro de vector4d que le corresponde
	if (outPut->portName() == "R" || outPut->portName() == "G" || outPut->portName() == "B" || outPut->portName() == "A")
	{
		
		if (outPut->portName() == "R") suffix += ".r";
		if (outPut->portName() == "G") suffix += ".g";
		if (outPut->portName() == "B") suffix += ".b";
		if (outPut->portName() == "A") suffix += ".a";
		
	}
}

// Util Function, used for get the name of the conected member by a certain port of a node
static std::string GetMemberStringByPort(QNEPort * port)
{
	std::string memberNameResult = "ERROR GETTIG CONECTION MEMBER'S NAME";
	
	
	if (!port) 
		return memberNameResult;
	if (port->connections().count() <= 0)
	{
		/*QMessageBox box; 
		box.setText("No conections for this port");
		box.exec();*/
		return ERROR_NO_CONNECTION;
	}

	QNEConnection	* auxCon = NULL;	// Edge connection
	QNEBlock		* auxNode = NULL;	// Node connected 

	// Get the first edge conector
	auxCon = port->connections().at(0);
	
	if (auxCon)
	{
		if (auxCon->port1() == port)
			auxNode = auxCon->port2()->block();
		else
			auxNode = auxCon->port1()->block();

		

		if (auxNode)
		{
			memberNameResult = auxNode->Resolve();
			std::string suffix;
			std::string preffix;

			GetPreffixAndSuffixByNodeType(auxNode->GetType(), auxCon->port1(), preffix, suffix);
			
			std::string result = preffix + memberNameResult + suffix;
			return result;
		}
	}


	// Si eso pasa gestionar el error
	return ERROR_NO_CONNECTION;

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
	ShininessPort = addInputPort("Shininess");
	NormalPort = addInputPort("Normal");
	AlphaPort = addInputPort("Alpha");


	// Alpha and Shineness only accept floats values (nodes)
	ShininessPort->acceptVector4Node = false;
	//AlphaPort->acceptVector4Node = false;

	
}
std::string QNMainNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("Main Node Resolve");
	msgBox.exec();*/

	cout << "Main Node Resolver 1 " << endl;
	string colorValueString = GetMemberStringByPort(ColorBasePort);
	colorValueString = (colorValueString == ERROR_NO_CONNECTION) ? DEFAULT_VALUE_COLOR : colorValueString;
	cout << "Main Node Resolver 2 " << endl;
	string specularValueString = GetMemberStringByPort(SpecularPort);
	specularValueString = (specularValueString == ERROR_NO_CONNECTION) ? DEFAULT_VALUE_SPECULAR : specularValueString;
	cout << "Main Node Resolver 3 " << endl;
	string normalValueString = GetMemberStringByPort(NormalPort);
	normalValueString = (normalValueString == ERROR_NO_CONNECTION) ? DEFAULT_VALUE_NORMAL : normalValueString;
	cout << "Main Node Resolver 4 " << endl;
	string alphaValueString = GetMemberStringByPort(AlphaPort);
	alphaValueString = (alphaValueString == ERROR_NO_CONNECTION) ? DEFAULT_VALUE_ALPHA : alphaValueString;
	cout << "Main Node Resolver 5 " << endl;
	string shininessValueString = GetMemberStringByPort(ShininessPort);
	shininessValueString = (shininessValueString == ERROR_NO_CONNECTION) ? DEFAULT_VALUE_SHININESS : shininessValueString;
	


	string result =
		"void main() \n"
		"{\n\n"
		"	vec4 colorBase = vec4(" + colorValueString + ");\n"
		"	vec4 specularLvl = vec4(" + specularValueString + ");\n"
		"	vec4 normal = 2 * vec4( " + normalValueString + ")-1;\n"
		"	vec4 alpha = vec4(" + alphaValueString + ");\n"
		"	vec4 lightIntensity = vec4(0.0);\n"
		"	float shininess = " + shininessValueString + ";\n"
		"\n"
		"	lightIntensity += BlinnPhong(colorBase.rgb, normal.rgb, specularLvl.rgb, shininess);\n"
		"	FragColor = lightIntensity;\n"
		"	FragColor.a = alpha.r;"
		"\n"
		"}"
		;


		
	return result;
	

}

QNMainNode ::~QNMainNode()
{
}

QGridLayout *  QNMainNode::GetPropertiesForm()
{

	//QSizePolicy * policy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	//QSize minSizeField = QSize(150, 25); QSize maxSizeField = QSize(200, 25);
	//QSize minSizeLabel = QSize(50, 25);	QSize maxSizeLabel = QSize(50, 25);
	//

	//QTextEdit * button1 = new QTextEdit("Button 1"); button1->setSizePolicy(*policy); button1->setMinimumSize(minSizeField); button1->setMaximumSize(maxSizeField);
	//QTextEdit * button2 = new QTextEdit("Button 2"); button2->setSizePolicy(*policy); button2->setMinimumSize(minSizeField); button2->setMaximumSize(maxSizeField);
	//QTextEdit * button3 = new QTextEdit("Button 3"); button3->setSizePolicy(*policy); button3->setMinimumSize(minSizeField); button3->setMaximumSize(maxSizeField);
	//QTextEdit * button4 = new QTextEdit("Button 4"); button4->setSizePolicy(*policy); button4->setMinimumSize(minSizeField); button4->setMaximumSize(maxSizeField);

	//QObject::connect(button1, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	//QObject::connect(button2, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	//QObject::connect(button3, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	//QObject::connect(button4, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	//QLabel * label1 = new QLabel("Field1"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	//QLabel * label2 = new QLabel("Field2");	label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	//QLabel * label3 = new QLabel("Field3");	label3->setMinimumSize(minSizeLabel); label3->setMaximumSize(maxSizeLabel);
	//QLabel * label4 = new QLabel("Field4");	label4->setMinimumSize(minSizeLabel); label4->setMaximumSize(maxSizeLabel);

	//QGridLayout * propForm = new QGridLayout(); 

	//propForm->addWidget(label1, 0, 0);	propForm->addWidget(label2, 1, 0);
	//propForm->addWidget(label3, 2, 0);	propForm->addWidget(label4, 3, 0);

	//propForm->addWidget(button1, 0, 1); propForm->addWidget(button2, 1, 1);
	//propForm->addWidget(button3, 2, 1);	propForm->addWidget(button4, 3, 1);
	//
	//
	//// Para que la 4 fila ocupe el resto del layout
	//propForm->setRowStretch(4, 1);
	//propForm->setMargin(10);	
	//propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return NULL;

}

void QNMainNode::HandleLostFocusMembers()
{
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}


/************************** CONST FLOAT NODE **************************/
QNConstFloatNode::QNConstFloatNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_ConstFloatNode";
	m_type = ID_TYPE_SPConstFloatNode;
}

void QNConstFloatNode::Init()
{
	addPort("Value", false, QNEPort::NamePort);
	addOutputPort("Value");
}

std::string QNConstFloatNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("ConstFloatNode Resolve");
	msgBox.exec();*/
	
	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string valueString = ConvertFloatToString(value);	
	
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
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	valueTextEdit = CreateMyNumericLineEdit(value, this);
	
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
	
	
	description = descTextEdit->placeholderText().toStdString();
	value = valueTextEdit->text().replace(',', '.').toFloat();
	this->form1->RefreshNodeEditor();

}





/************************** VECTOR 2 NODE **************************/
QNVector2DNode::QNVector2DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_Vector2DNode";
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
	string rValueString = ConvertFloatToString(value.r);
	string gValueString = ConvertFloatToString(value.g);

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
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);
	
	rValueLineEdit = CreateMyNumericLineEdit(value.r, this);
	gValueLineEdit = CreateMyNumericLineEdit(value.g, this);

	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	QLabel * label2 = new QLabel("R:"); label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	QLabel * label3 = new QLabel("G:"); label2->setMinimumSize(minSizeLabel); label3->setMaximumSize(maxSizeLabel);



	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0); 	propForm->addWidget(label2, 1, 0);
	propForm->addWidget(label3, 2, 0);
	
	propForm->addWidget(descTextEdit, 0, 1);
	propForm->addWidget(rValueLineEdit, 1, 1);
	propForm->addWidget(gValueLineEdit, 2, 1);
	
	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;
	

}

void QNVector2DNode::HandleLostFocusMembers()
{
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	value.r = rValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	value.g = gValueLineEdit->text().replace(QString(","), QString(".")).toFloat();	
	this->form1->RefreshNodeEditor();



}



/************************** VECTOR 3 NODE **************************/
QNVector3DNode::QNVector3DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_Vector3DNode";
	m_type = ID_TYPE_SPVector3DNode;
}

void QNVector3DNode::Init()
{
	addPort("Color RGB",false, QNEPort::NamePort);
	addOutputPort("");
	ROutPut =	addOutputPort("R");
	GOutPut =	addOutputPort("G");
	BOutPut =	addOutputPort("B");
}

QNVector3DNode ::~QNVector3DNode()
{
}

std::string QNVector3DNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNVector3DNode Resolve");
	msgBox.exec();*/

	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string rValueString = ConvertFloatToString(value.r);
	string gValueString = ConvertFloatToString(value.g);
	string bValueString = ConvertFloatToString(value.b);

	// 2. Componer el codigo de este nodo
	//	const float MAX_NUM_LIGHTS = 8; // max number of lights
	codeDefinition = "const vec4 " + nameMember + " = vec4(" + rValueString + ", " + gValueString + ", " + bValueString + ", 0);\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeConst(this, codeDefinition); // en este caso a AppendCodeConst

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
}

QGridLayout *  QNVector3DNode::GetPropertiesForm()
{

	// 1. Create Controls
	descTextEdit = new QTextEdit("");	descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	rValueLineEdit = CreateMyNumericLineEdit(value.r, this);
	gValueLineEdit = CreateMyNumericLineEdit(value.g, this);
	bValueLineEdit = CreateMyNumericLineEdit(value.b, this);
	
	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	QLabel * label2 = new QLabel("R:"); label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);
	QLabel * label3 = new QLabel("G:"); label2->setMinimumSize(minSizeLabel); label3->setMaximumSize(maxSizeLabel);
	QLabel * label4 = new QLabel("B:"); label2->setMinimumSize(minSizeLabel); label4->setMaximumSize(maxSizeLabel);
	

	// 2. Create LayOut
	QGridLayout * propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0); 	propForm->addWidget(label2, 1, 0);
	propForm->addWidget(label3, 2, 0);	propForm->addWidget(label4, 3, 0);
	

	propForm->addWidget(descTextEdit, 0, 1);
	propForm->addWidget(rValueLineEdit, 1, 1);
	propForm->addWidget(gValueLineEdit, 2, 1);
	propForm->addWidget(bValueLineEdit, 3, 1);
	

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNVector3DNode::HandleLostFocusMembers()
{
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();
*/

	description = descTextEdit->placeholderText().toStdString();
	value.r = rValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	value.g = gValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	value.b = bValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	this->form1->RefreshNodeEditor();
	
}



/************************** VECTOR 4 NODE **************************/
QNVector4DNode::QNVector4DNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_Vector4DNode";
	m_type = ID_TYPE_SPVector4DNode;
}

void QNVector4DNode::Init()
{
	addPort("Color RGBA", false, QNEPort::NamePort);
	addOutputPort("");
	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNVector4DNode ::~QNVector4DNode()
{
}

std::string QNVector4DNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNVector4DNode Resolve");
	msgBox.exec();*/

	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	string rValueString = ConvertFloatToString(value.r);
	string gValueString = ConvertFloatToString(value.g);
	string bValueString = ConvertFloatToString(value.b);
	string aValueString = ConvertFloatToString(value.a);

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
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	rValueLineEdit = CreateMyNumericLineEdit(value.r, this);
	gValueLineEdit = CreateMyNumericLineEdit(value.g, this);
	bValueLineEdit = CreateMyNumericLineEdit(value.b, this);
	aValueLineEdit = CreateMyNumericLineEdit(value.a, this);
	
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
	propForm->addWidget(rValueLineEdit, 1, 1);
	propForm->addWidget(gValueLineEdit, 2, 1);
	propForm->addWidget(bValueLineEdit, 3, 1);
	propForm->addWidget(aValueLineEdit, 4, 1);

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	return propForm;

}

void QNVector4DNode::HandleLostFocusMembers()
{
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	value.r = rValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	value.g = gValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	value.b = bValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	value.a = aValueLineEdit->text().replace(QString(","), QString(".")).toFloat();
	this->form1->RefreshNodeEditor();
}


/************************** TEXTURE NODE **************************/
QNTextureNode::QNTextureNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_TextureNode";
	m_type = ID_TYPE_SPTextureNode;
}

void QNTextureNode::Init()
{
	addPort("Texture 2D", false, QNEPort::NamePort);
	addOutputPort("");
	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNTextureNode ::~QNTextureNode()
{
}

std::string QNTextureNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QTexture Resolve");
	msgBox.exec();*/

	string codeDefinition;
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	
	// 2. Componer el codigo de este nodo	
	codeDefinition = "uniform sampler2D " + nameMember + ";\n";

	// 3.Registrar el codigo a la lista que le corresponde
	SHADER_COMPOSER->AppendCodeTexture(this, codeDefinition); // en este caso a AppendCodeConst

	// 4. Devolver siempre el nombre le miembro
	return nameMember;
}
void QNTextureNode::ShowImage(std::string path)
{
	/*if (scene)
	{
		delete scene;
		scene = NULL;
	}
	this->grid*/

	
	QString qpath(path.c_str());
	QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap(qpath));
	
	
	scene = new QGraphicsScene();
	view = new QGraphicsView(scene);
	
	view->setMaximumSize(QSize(300, 300));
	/*view->setMinimumSize(QSize(100, 100));*/
	propForm->setAlignment(view, Qt::AlignCenter | Qt::AlignTop);
	propForm->addWidget(view, 2, 0, 3, 0);

	scene->addItem(item);

	view->resize(view->sizeHint());

	view->show();
}
QGridLayout *  QNTextureNode::GetPropertiesForm()
{

	// 1. Create Controls
	descTextEdit = new QTextEdit(""); descTextEdit->setSizePolicy(*policy); descTextEdit->setMinimumSize(minSizeField); descTextEdit->setMaximumSize(maxSizeField);
	QObject::connect(descTextEdit, &QTextEdit::textChanged, this, &QNEBlock::HandleLostFocusMembers);

	pathTextEdit = new QTextEdit(path.c_str()); pathTextEdit->setSizePolicy(*policy); pathTextEdit->setMinimumSize(minSizeField); pathTextEdit->setMaximumSize(maxSizeField);
	pathTextEdit->setReadOnly(true);


	QLabel * label1 = new QLabel("Description:"); label1->setMinimumSize(minSizeLabel); label1->setMaximumSize(maxSizeLabel);
	
	QLabel * label2 = new QLabel("Path:"); label2->setMinimumSize(minSizeLabel); label2->setMaximumSize(maxSizeLabel);

	buttonExaminar = new QPushButton("Browse");
	QObject::connect(buttonExaminar, &QPushButton::clicked, this, &QNTextureNode::OpenSelectWindow);

	
	
	// 2. Create LayOut
	propForm = new QGridLayout();

	propForm->addWidget(label1, 0, 0);
	propForm->addWidget(label2, 1, 0);
	
	propForm->addWidget(descTextEdit, 0, 1);

	propForm->addWidget(pathTextEdit, 1, 1);
	propForm->addWidget(buttonExaminar, 1, 2);

	

	// Para que la ultima fila ocupe el resto del layout
	propForm->setRowStretch(propForm->rowCount(), 1);
	ShowImage(path);
	

	propForm->setMargin(10);  propForm->setHorizontalSpacing(3); propForm->setHorizontalSpacing(5);

	

	return propForm;

}

void QNTextureNode::OpenSelectWindow()
{
	QFileDialog * modal = new QFileDialog();
	modal->setFileMode(QFileDialog::ExistingFile);
	modal->setNameFilter("*.png *.bmp *.gif");
	QString file =  modal->getOpenFileName();
	
	if (file != "")
	{
		path = file.toStdString();
		pathTextEdit->setText(file);
		
		form1->RefreshNodeEditor();
		/*QMessageBox box;
		box.setText(path.c_str());
		box.exec();*/

	}
	else
	{
		path = STANDAR_TEXTURE_PATH;
	}

	ShowImage(path);
	
}

void QNTextureNode::HandleLostFocusMembers()
{
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();

}

/************************** ADD NODE **************************/
QNAddNode::QNAddNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_AddNode";
	m_type = ID_TYPE_SPAddNode;
}

void QNAddNode::Init()
{
	addPort("Add", false, QNEPort::NamePort);
	addOutputPort("");
	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
	APort = addInputPort("X");
	BPort = addInputPort("Y");
	
	
	
}

QNAddNode ::~QNAddNode()
{
}

std::string QNAddNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNAddNode Resolve");
	msgBox.exec();*/

	string codeDefinition;
	
	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);
	

	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);
	
	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = vec4(" + aValueString + ");\n"
		"	vec4 B = vec4(" + bValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();
*/
	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
	
}



/************************** SUBTRACT NODE **************************/
QNSubtractNode::QNSubtractNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_Substract";
	m_type = ID_TYPE_SPSubtractNode;
}

void QNSubtractNode::Init()
{
	addPort("Subs", false, QNEPort::NamePort);
	addOutputPort("");
	APort = addInputPort("X");
	BPort = addInputPort("Y");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");


}

QNSubtractNode ::~QNSubtractNode()
{
}

std::string QNSubtractNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNSubtractNode Resolve");
	msgBox.exec();
*/
	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = vec4(" + aValueString + ");\n"
		"	vec4 B = vec4(" + bValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}



/************************** MULTIPLY NODE **************************/
QNMultiplyNode::QNMultiplyNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_MultiplyNode";
	m_type = ID_TYPE_SPMultiplyNode;
}

void QNMultiplyNode::Init()
{
	addPort("Multiply", false, QNEPort::NamePort);
	
	APort = addInputPort("X");
	BPort = addInputPort("Y");
	addOutputPort("");
	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");

}

QNMultiplyNode ::~QNMultiplyNode()
{
}
std::string QNMultiplyNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNMultiplyNode Resolve");
	msgBox.exec()*/;

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = vec4(" + aValueString + ");\n"
		"	vec4 B = vec4(" + bValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}


/************************** POWER NODE **************************/
QNPowerNode::QNPowerNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_PowerNode";
	m_type = ID_TYPE_SPPowerNode;
}

void QNPowerNode::Init()
{
	addPort("Power", false, QNEPort::NamePort);
	addOutputPort("");
	ValuePort =  addInputPort("Val");
	ExpPort = addInputPort("Exp");



	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");

}

QNPowerNode ::~QNPowerNode()
{
}

std::string QNPowerNode::Resolve()
{
	//QMessageBox msgBox;
	//msgBox.setText("QNMultiplyNode Resolve");
	//msgBox.exec();

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValuePort);
	string ExpValueString = GetMemberStringByPort(ExpPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = vec4(" + ValueString + ");\n"
		"	vec4 exp = vec4(" + ExpValueString + ");\n"
		"	return pow(val, exp);\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}




/************************** SQRT NODE **************************/
QNSqrtNode::QNSqrtNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_SqrtNode";
	m_type = ID_TYPE_SPSqrtNode;
}

void QNSqrtNode::Init()
{
	addPort("Sqrt", false, QNEPort::NamePort);
	addOutputPort("");
	ValPort = addInputPort("Val");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNSqrtNode ::~QNSqrtNode()
{
}

std::string QNSqrtNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNSqrtNode Resolve");
	msgBox.exec();*/

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValPort);
	

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = vec4(" + ValueString + ");\n"		
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();
*/
	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}


/************************** LOG NODE **************************/
QNLogNode::QNLogNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_LogNode";
	m_type = ID_TYPE_SPLogNode;
}

void QNLogNode::Init()
{
	addPort("Log", false, QNEPort::NamePort);
	addOutputPort("");
	ValPort = addInputPort("Val");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNLogNode ::~QNLogNode()
{
}

std::string QNLogNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNLogNode Resolve");
	msgBox.exec();*/

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValPort);


	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = vec4(" + ValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
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
	APort = addInputPort("X");
	BPort = addInputPort("Y");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNMinNode ::~QNMinNode()
{
}

std::string QNMinNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNMinNode Resolve");
	msgBox.exec();*/

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = vec4(" + aValueString + ");\n"
		"	vec4 B = vec4(" + bValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}



/************************** MAX NODE **************************/
QNMaxNode::QNMaxNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_MaxNode";
	m_type = ID_TYPE_SPMaxNode;
}

void QNMaxNode::Init()
{
	addPort("Max", false, QNEPort::NamePort);
	addOutputPort("");
	APort = addInputPort("X");
	BPort = addInputPort("Y");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNMaxNode ::~QNMaxNode()
{
}

std::string QNMaxNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNMaxNode Resolve");
	msgBox.exec();
*/
	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = vec4(" + aValueString + ");\n"
		"	vec4 B = vec4(" + bValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}

/************************** ABS NODE **************************/
QNAbsNode::QNAbsNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_AbsNode";
	m_type = ID_TYPE_SPAbsNode;
}

void QNAbsNode::Init()
{
	addPort("Abs", false, QNEPort::NamePort);
	addOutputPort("");
	ValPort = addInputPort("Val");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNAbsNode ::~QNAbsNode()
{
}

std::string QNAbsNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNAbsNode Resolve");
	msgBox.exec();*/

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string ValueString = GetMemberStringByPort(ValPort);


	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 val = vec4(" + ValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}



/************************** SIGN NODE **************************/
QNSignNode::QNSignNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_SignNode";
	m_type = ID_TYPE_SPSignNode;
}

void QNSignNode::Init()
{
	addPort("Sign", false, QNEPort::NamePort);
	addOutputPort("");
	ValPort = addInputPort("Val");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNSignNode ::~QNSignNode()
{
}

std::string QNSignNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNSignNode Resolve");
	msgBox.exec();*/
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
		"	vec4 val = vec4(" + ValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();

}

/************************** MOD NODE **************************/
QNModNode::QNModNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_ModNode";
	m_type = ID_TYPE_SPModNode;
}

void QNModNode::Init()
{
	addPort("Mod", false, QNEPort::NamePort);
	addOutputPort("");
	APort = addInputPort("X");
	BPort = addInputPort("Y");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");
}

QNModNode ::~QNModNode()
{
}

std::string QNModNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNModNode Resolve");
	msgBox.exec();*/

	string codeDefinition;

	// 1. Obtener un nombre para el miembro
	string nameMember = SHADER_COMPOSER->RegistrarMiembro(this);


	// 2. Componer el codigo de este nodo
	// Para cada puerto obtengo el nombre de los conectados
	string aValueString = GetMemberStringByPort(APort);
	string bValueString = GetMemberStringByPort(BPort);

	codeDefinition = "vec4 " + nameMember + "()\n"
		"{\n"
		"	vec4 A = vec4(" + aValueString + ");\n"
		"	vec4 B = vec4(" + bValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/
	this->form1->RefreshNodeEditor();
}



/************************** CLAMP NODE **************************/
QNClampNode::QNClampNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_ClampNode";
	m_type = ID_TYPE_SPClampNode;
}

void QNClampNode::Init()
{
	addPort("Clamp", false, QNEPort::NamePort);
	addOutputPort("");


	ValPort = addInputPort("Val");
	MinPort = addInputPort("Min");
	MaxPort = addInputPort("Max");

	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");

}

QNClampNode ::~QNClampNode()
{
}

std::string QNClampNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNClampNode Resolve");
	msgBox.exec();*/

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
		"	vec4 Val = vec4(" + valValueString + ");\n"
		"	vec4 Min = vec4(" + minValueString + ");\n"
		"	vec4 Max = vec4(" + maxValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/
	
	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}



/************************** LERP NODE **************************/
QNLerpNode::QNLerpNode(QGraphicsItem *parent) : QNEBlock(parent)
{
	titulo = "SPC_LerpNode";
	m_type = ID_TYPE_SPLerpNode;
}

void QNLerpNode::Init()
{
	addPort("Lerp", false, QNEPort::NamePort);
	addOutputPort("");
	
	ValXPort = addInputPort("X");
	ValYPort = addInputPort("Y");
	TPort = addInputPort("T");

	// T only accepts floats values (nodes)
	TPort->acceptVector4Node = false;
	



	ROutPut = addOutputPort("R");
	GOutPut = addOutputPort("G");
	BOutPut = addOutputPort("B");
	AOutPut = addOutputPort("A");

}

QNLerpNode ::~QNLerpNode()
{
}

std::string QNLerpNode::Resolve()
{
	/*QMessageBox msgBox;
	msgBox.setText("QNLerpNode Resolve");
	msgBox.exec();*/

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
		"	vec4 ValX = vec4(" + valXValueString + ");\n"
		"	vec4 Valy = vec4(" + valYValueString + ");\n"
		"	vec4 t = vec4(" + tValueString + ");\n"
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
	/*QMessageBox msgBox;
	msgBox.setText("Se ha modificado el valor");
	msgBox.exec();*/

	description = descTextEdit->placeholderText().toStdString();
	this->form1->RefreshNodeEditor();
}








