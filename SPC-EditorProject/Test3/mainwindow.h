#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets\qmainwindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void onAddNew();
};

#endif
