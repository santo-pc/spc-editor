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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dockNodeEditor;
    QWidget *dockWidgetContents;
    QDockWidget *dock3DViewer;
    QWidget *dockWidgetContents_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayoutXX;
    QPushButton *pushButton;
    QToolBar *toolBar;
    QDockWidget *dockWidgetProperties_3;
    QWidget *dockWidgetContents_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(842, 768);
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
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 842, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockNodeEditor = new QDockWidget(MainWindow);
        dockNodeEditor->setObjectName(QStringLiteral("dockNodeEditor"));
        dockNodeEditor->setMinimumSize(QSize(532, 38));
        dockNodeEditor->setAutoFillBackground(true);
        dockNodeEditor->setFloating(false);
        dockNodeEditor->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockNodeEditor->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockNodeEditor->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockNodeEditor);
        dock3DViewer = new QDockWidget(MainWindow);
        dock3DViewer->setObjectName(QStringLiteral("dock3DViewer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(dock3DViewer->sizePolicy().hasHeightForWidth());
        dock3DViewer->setSizePolicy(sizePolicy1);
        dock3DViewer->setMinimumSize(QSize(286, 250));
        dock3DViewer->setAutoFillBackground(true);
        dock3DViewer->setFloating(false);
        dock3DViewer->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        verticalLayoutWidget = new QWidget(dockWidgetContents_2);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 271, 271));
        verticalLayoutXX = new QVBoxLayout(verticalLayoutWidget);
        verticalLayoutXX->setObjectName(QStringLiteral("verticalLayoutXX"));
        verticalLayoutXX->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayoutXX->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(dockWidgetContents_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 290, 71, 23));
        dock3DViewer->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock3DViewer);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidgetProperties_3 = new QDockWidget(MainWindow);
        dockWidgetProperties_3->setObjectName(QStringLiteral("dockWidgetProperties_3"));
        dockWidgetProperties_3->setMinimumSize(QSize(80, 250));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        dockWidgetProperties_3->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidgetProperties_3);

        toolBar->addAction(actionNew);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(on_button_clicked()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SP Material Editor - Shader Composer", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Create New Material</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        dockNodeEditor->setWindowTitle(QApplication::translate("MainWindow", "Node Editor", 0));
        dock3DViewer->setWindowTitle(QApplication::translate("MainWindow", "3D Viewer", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Test", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM2_H
