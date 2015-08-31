/********************************************************************************
** Form generated from reading UI file 'modalshader.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODALSHADER_H
#define UI_MODALSHADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModalShader
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushGuardar;

    void setupUi(QWidget *ModalShader)
    {
        if (ModalShader->objectName().isEmpty())
            ModalShader->setObjectName(QStringLiteral("ModalShader"));
        ModalShader->resize(604, 679);
        verticalLayout_2 = new QVBoxLayout(ModalShader);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(ModalShader);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(10, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushGuardar = new QPushButton(ModalShader);
        pushGuardar->setObjectName(QStringLiteral("pushGuardar"));

        horizontalLayout->addWidget(pushGuardar);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ModalShader);
        QObject::connect(pushGuardar, SIGNAL(clicked()), ModalShader, SLOT(on_saveButton_Clicked()));

        QMetaObject::connectSlotsByName(ModalShader);
    } // setupUi

    void retranslateUi(QWidget *ModalShader)
    {
        ModalShader->setWindowTitle(QApplication::translate("ModalShader", "Shader Generado", 0));
        pushGuardar->setText(QApplication::translate("ModalShader", "Guardar", 0));
    } // retranslateUi

};

namespace Ui {
    class ModalShader: public Ui_ModalShader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODALSHADER_H
