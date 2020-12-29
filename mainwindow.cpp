//---------------------------------------------------------------------------------------
//
//  AutoCost: mainwindow
//
//---------------------------------------------------------------------------------------
//
//  General QT header files

//---------------------------------------------------------------------------------------
//
// AutoCost specific header files
#include "AutoCost.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------------------------------------
// Debugging include
#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  MainWindow constructor
//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
//
//  MainWindow Menu functions
//
//---------------------------------------------------------------------------------------
//
//  File -> Exit
//
void MainWindow::on_action_FileExit_triggered()
{
    qDebug() << "File -> Exit triggered";

}

//---------------------------------------------------------------------------------------
//
//  Tools -> Options
//
void MainWindow::on_action_ToolsOptions_triggered()
{
    qDebug() << "Tools -> Options triggered";

}
