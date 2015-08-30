#include "modalshader.h"
#include <string>
#include <qmessagebox.h>
#include <iostream>
#include <qdialog.h>
#include <qfiledialog.h>
#include "Utils.h"
using namespace std;

ModalShader::ModalShader(QWidget *parent) : QDialog(parent)//, ui(new Ui::ModalShader)
	//: QMainWindow(parent)
{
	ui.setupUi(this);

	QFont * font = new QFont("Courier New");

	ui.plainTextEdit->setFont(*font);

	QPalette p = ui.plainTextEdit->palette();
	p.setColor(QPalette::Base,QColor("#0f1419"));
	p.setColor(QPalette::Text, Qt::white);
	ui.plainTextEdit->setPalette(p);
}

ModalShader::~ModalShader()
{

}


void ModalShader::SetShaderString(string shader)
{
	this->shaderString = shader;
	ui.plainTextEdit->setPlainText(QString(shader.c_str()));
}

void ModalShader::on_saveButton_Clicked()
{
	QFileDialog * modal = new QFileDialog();
	modal->setAcceptMode(QFileDialog::AcceptSave);
	modal->setFileMode(QFileDialog::AnyFile);

	QString file = modal->getSaveFileName();

	if (file != "")
	{
		file = file += ".vs";
		SaveShaderToFile(shaderString, file.toStdString());

	}
}