/********************************************************************************
** Form generated from reading UI file 'Form2.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM2_H
#define UI_FORM2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3Test;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dock3DViewer;
    QWidget *dockWidgetContents_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayoutXX;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayoutButtons;
    QPushButton *pushButtonMallaSphere;
    QPushButton *pushButtonMallaCube;
    QPushButton *pushButtonMallaCylinder;
    QPushButton *pushButtonMallaTeaPot;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayoutLighColor;
    QLabel *label_2;
    QLineEdit *lineEditR;
    QLabel *label_3;
    QLineEdit *lineEditG;
    QLabel *label_4;
    QLineEdit *lineEditB;
    QLabel *label_5;
    QSlider *horizontalSliderDiffuse;
    QLabel *label_6;
    QSlider *horizontalSliderAmbient;
    QPushButton *pushButton;
    QDockWidget *dockWidgetProperties_3;
    QWidget *dockWidgetContents_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1142, 891);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/SPTFG/document_new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3Test = new QVBoxLayout();
        verticalLayout_3Test->setObjectName(QStringLiteral("verticalLayout_3Test"));

        horizontalLayout_2->addLayout(verticalLayout_3Test);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1142, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dock3DViewer = new QDockWidget(MainWindow);
        dock3DViewer->setObjectName(QStringLiteral("dock3DViewer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(dock3DViewer->sizePolicy().hasHeightForWidth());
        dock3DViewer->setSizePolicy(sizePolicy1);
        dock3DViewer->setMinimumSize(QSize(310, 250));
        dock3DViewer->setAutoFillBackground(true);
        dock3DViewer->setFloating(false);
        dock3DViewer->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        scrollArea = new QScrollArea(dockWidgetContents_2);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(10, 10, 291, 411));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 289, 409));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        verticalLayoutWidget = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 251, 231));
        verticalLayoutXX = new QVBoxLayout(verticalLayoutWidget);
        verticalLayoutXX->setObjectName(QStringLiteral("verticalLayoutXX"));
        verticalLayoutXX->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayoutXX->setContentsMargins(0, 0, 0, 0);
        layoutWidget = new QWidget(scrollAreaWidgetContents);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(250, 0, 34, 132));
        verticalLayoutButtons = new QVBoxLayout(layoutWidget);
        verticalLayoutButtons->setObjectName(QStringLiteral("verticalLayoutButtons"));
        verticalLayoutButtons->setContentsMargins(0, 0, 0, 0);
        pushButtonMallaSphere = new QPushButton(layoutWidget);
        pushButtonMallaSphere->setObjectName(QStringLiteral("pushButtonMallaSphere"));
        pushButtonMallaSphere->setMinimumSize(QSize(28, 28));
        pushButtonMallaSphere->setIconSize(QSize(64, 64));

        verticalLayoutButtons->addWidget(pushButtonMallaSphere);

        pushButtonMallaCube = new QPushButton(layoutWidget);
        pushButtonMallaCube->setObjectName(QStringLiteral("pushButtonMallaCube"));
        pushButtonMallaCube->setMinimumSize(QSize(28, 28));
        pushButtonMallaCube->setIconSize(QSize(64, 64));

        verticalLayoutButtons->addWidget(pushButtonMallaCube);

        pushButtonMallaCylinder = new QPushButton(layoutWidget);
        pushButtonMallaCylinder->setObjectName(QStringLiteral("pushButtonMallaCylinder"));
        pushButtonMallaCylinder->setMinimumSize(QSize(28, 28));
        pushButtonMallaCylinder->setIconSize(QSize(64, 64));

        verticalLayoutButtons->addWidget(pushButtonMallaCylinder);

        pushButtonMallaTeaPot = new QPushButton(layoutWidget);
        pushButtonMallaTeaPot->setObjectName(QStringLiteral("pushButtonMallaTeaPot"));
        pushButtonMallaTeaPot->setMinimumSize(QSize(28, 28));
        pushButtonMallaTeaPot->setIconSize(QSize(64, 64));

        verticalLayoutButtons->addWidget(pushButtonMallaTeaPot);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 240, 271, 161));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 251, 137));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayoutLighColor = new QHBoxLayout();
        horizontalLayoutLighColor->setObjectName(QStringLiteral("horizontalLayoutLighColor"));
        horizontalLayoutLighColor->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(25);
        sizePolicy3.setVerticalStretch(25);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setMaximumSize(QSize(25, 16777215));

        horizontalLayoutLighColor->addWidget(label_2);

        lineEditR = new QLineEdit(layoutWidget1);
        lineEditR->setObjectName(QStringLiteral("lineEditR"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEditR->sizePolicy().hasHeightForWidth());
        lineEditR->setSizePolicy(sizePolicy4);
        lineEditR->setMaximumSize(QSize(30, 16777215));
        lineEditR->setBaseSize(QSize(0, 0));

        horizontalLayoutLighColor->addWidget(lineEditR);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setMaximumSize(QSize(25, 16777215));

        horizontalLayoutLighColor->addWidget(label_3);

        lineEditG = new QLineEdit(layoutWidget1);
        lineEditG->setObjectName(QStringLiteral("lineEditG"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(25);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lineEditG->sizePolicy().hasHeightForWidth());
        lineEditG->setSizePolicy(sizePolicy5);
        lineEditG->setMaximumSize(QSize(30, 16777215));

        horizontalLayoutLighColor->addWidget(lineEditG);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);
        label_4->setMaximumSize(QSize(25, 16777215));

        horizontalLayoutLighColor->addWidget(label_4);

        lineEditB = new QLineEdit(layoutWidget1);
        lineEditB->setObjectName(QStringLiteral("lineEditB"));
        lineEditB->setMaximumSize(QSize(30, 16777215));

        horizontalLayoutLighColor->addWidget(lineEditB);

        horizontalLayoutLighColor->setStretch(0, 25);
        horizontalLayoutLighColor->setStretch(1, 25);
        horizontalLayoutLighColor->setStretch(2, 25);
        horizontalLayoutLighColor->setStretch(3, 25);
        horizontalLayoutLighColor->setStretch(4, 25);
        horizontalLayoutLighColor->setStretch(5, 25);

        verticalLayout_2->addLayout(horizontalLayoutLighColor);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_2->addWidget(label_5);

        horizontalSliderDiffuse = new QSlider(layoutWidget1);
        horizontalSliderDiffuse->setObjectName(QStringLiteral("horizontalSliderDiffuse"));
        horizontalSliderDiffuse->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSliderDiffuse);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        horizontalSliderAmbient = new QSlider(layoutWidget1);
        horizontalSliderAmbient->setObjectName(QStringLiteral("horizontalSliderAmbient"));
        horizontalSliderAmbient->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSliderAmbient);

        pushButton = new QPushButton(scrollAreaWidgetContents);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 140, 41, 41));
        scrollArea->setWidget(scrollAreaWidgetContents);
        dock3DViewer->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock3DViewer);
        dockWidgetProperties_3 = new QDockWidget(MainWindow);
        dockWidgetProperties_3->setObjectName(QStringLiteral("dockWidgetProperties_3"));
        dockWidgetProperties_3->setMinimumSize(QSize(80, 250));
        dockWidgetProperties_3->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        dockWidgetProperties_3->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidgetProperties_3);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(on_button_clicked()));
        QObject::connect(pushButtonMallaSphere, SIGNAL(clicked()), MainWindow, SLOT(on_buttonSphereMesh_clicked()));
        QObject::connect(pushButtonMallaCube, SIGNAL(clicked()), MainWindow, SLOT(on_buttonCubeMesh_clicked()));
        QObject::connect(pushButtonMallaCylinder, SIGNAL(clicked()), MainWindow, SLOT(on_buttonCylinderMesh_clicked()));
        QObject::connect(pushButtonMallaTeaPot, SIGNAL(clicked()), MainWindow, SLOT(on_buttonTeaPotMesh_clicked()));
        QObject::connect(lineEditR, SIGNAL(textChanged(QString)), MainWindow, SLOT(on_value_changed_lightColorR()));
        QObject::connect(lineEditG, SIGNAL(textChanged(QString)), MainWindow, SLOT(on_value_changed_lightColoG()));
        QObject::connect(lineEditB, SIGNAL(textChanged(QString)), MainWindow, SLOT(on_value_changed_lightColorB()));
        QObject::connect(horizontalSliderDiffuse, SIGNAL(valueChanged(int)), MainWindow, SLOT(on_slider_diffuse_changed(int)));
        QObject::connect(horizontalSliderAmbient, SIGNAL(valueChanged(int)), MainWindow, SLOT(on_slider_ambient_changed(int)));
        QObject::connect(lineEditG, SIGNAL(textChanged(QString)), MainWindow, SLOT(on_value_changed_lightColorG()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SP Material Editor - Shader Composer", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Create New Material</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        dock3DViewer->setWindowTitle(QApplication::translate("MainWindow", "3D Viewer", 0));
        pushButtonMallaSphere->setText(QString());
        pushButtonMallaCube->setText(QString());
        pushButtonMallaCylinder->setText(QString());
        pushButtonMallaTeaPot->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Light Settings", 0));
        label->setText(QApplication::translate("MainWindow", "Color", 0));
        label_2->setText(QApplication::translate("MainWindow", "R:", 0));
        label_3->setText(QApplication::translate("MainWindow", "G:", 0));
        label_4->setText(QApplication::translate("MainWindow", "B:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Diffuse Intensity", 0));
        label_6->setText(QApplication::translate("MainWindow", "Ambient Intensity", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Apply", 0));
        dockWidgetProperties_3->setWindowTitle(QApplication::translate("MainWindow", "Properties", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM2_H
