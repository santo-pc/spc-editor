#ifndef MODALSHADER_H
#define MODALSHADER_H

#include <QWidget>
#include <QtWidgets\qmainwindow.h>
#include <qgraphicsscene.h>
#include <qpoint.h>
#include <qgraphicssceneevent.h>
#include <qgraphicsview.h>
#include <qdialog.h>
//#include "ui_modalshader.h"
#include "../ui_modalshader.h"
#include <string>

class ModalShader : public QDialog
{
	Q_OBJECT

public:
	ModalShader(QWidget *parent = 0);
	~ModalShader();

	void SetShaderString(std::string shader);

private:
	std::string shaderString;
	Ui::ModalShader ui;

private slots:
	void on_saveButton_Clicked();
};

#endif // MODALSHADER_H
