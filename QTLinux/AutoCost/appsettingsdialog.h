//---------------------------------------------------------------------------------------
//
//  Module: appsettingsdialog.h
//
//---------------------------------------------------------------------------------------
#ifndef APPSETTINGSDIALOG_H
#define APPSETTINGSDIALOG_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettings.h"

#include <QDialog>

//---------------------------------------------------------------------------------------
//
//  Clsass AppSettings definitions
//
//---------------------------------------------------------------------------------------
namespace Ui {
class AppSettingsDialog;
}

class AppSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppSettingsDialog(QWidget *parent = nullptr);
    ~AppSettingsDialog();

private:
    Ui::AppSettingsDialog *ui;

    AppSettings *AppConfiguration;

 };

#endif // APPSETTINGSDIALOG_H
