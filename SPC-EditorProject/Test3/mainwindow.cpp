#include "mainwindow.h"
#include "window.h"
#include <QtWidgets\qmenubar.h>
#include <QtWidgets\qmenu.h>
#include <QtWidgets\qmessagebox.h>
#include <GL\glew.h>
#include <iostream>

MainWindow::MainWindow()
{
    QMenuBar * menuBar = new QMenuBar;
    QMenu * menuWindow = menuBar->addMenu(tr("&Window"));
    QAction * addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    connect(addNew, SIGNAL(triggered()), this, SLOT(onAddNew()));
    setMenuBar(menuBar);

    onAddNew();

}

void MainWindow::onAddNew()
{
   setCentralWidget(new Window(this));
    
}
