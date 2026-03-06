//---------------------------------------------------------------------------------------
//
//  Module: appsettings.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettingsdialog.h"
#include "ui_appsettingsdialog.h"


#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor and destructor
//
//---------------------------------------------------------------------------------------
AppSettingsDialog::AppSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppSettingsDialog)
{
    qDebug() << "appsettingdialog -> constructor triggered";
    ui->setupUi(this);
}

AppSettingsDialog::~AppSettingsDialog()
{
    delete ui;
}
