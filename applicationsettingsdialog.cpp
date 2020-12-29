//---------------------------------------------------------------------------------------
//
//  AutoCost: applicationsettingsdialog
//
//---------------------------------------------------------------------------------------
//
//  General QT header files

//---------------------------------------------------------------------------------------
//
// AutoCost specific header files
#include "AutoCost.h"
#include "applicationsettingsdialog.h"
#include "ui_applicationsettingsdialog.h"

//---------------------------------------------------------------------------------------
// Debugging include
#include <QDebug>

ApplicationSettingsDialog::ApplicationSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationSettingsDialog)
{
    ui->setupUi(this);
}

ApplicationSettingsDialog::~ApplicationSettingsDialog()
{
    delete ui;
}

void ApplicationSettingsDialog::on_buttonBox_rejected()
{
    qDebug() << "Settings dialog -> Cancel triggered";

}
