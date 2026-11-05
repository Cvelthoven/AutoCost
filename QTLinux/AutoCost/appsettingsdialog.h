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
//  Class AppSettings definitions
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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AppSettingsDialog *ui;

    AppSettings *AppConfiguration;

    bool
        bEncrypted = false;

    //-----------------------------------------------------------------------------------
    //
    //  Configuraton Application Database section key names
    //
    const QString
        strSectionNameAppDB = "ApplicationDatabase",
        strAppDBServerIPKey = "ServerIP",
        strAppDBServerPortKey = "ServerPort",
        strAppDBNameKey = "AppDBName",
        strAppDBUserIDKey = "AppDBUserID",
        strAppDBUserPasswordKey = "AppDBUserPassword",
    //-----------------------------------------------------------------------------------
    //
    //  Configuraton Application Load Session section key names
    //
        strSectionNameLoadSession = "LoadSessionDefaults",
        strLoadSessionKWh = "DefaultKWh",
        strLoadSessionAcceEndPercentage = "DefaultAccuEnd",
    //-----------------------------------------------------------------------------------
    //
    //  Configuraton Application Miscellaneous section key names
    //
        strSectionNameMiscellaneous = "Miscellaneous",
        strMiscellaneousMillageYear = "MillageYear";

    QList<QString>
        lsGeneralOptions,
        lsAppDBOptions;

    enum AppLoadSessionDefault
    {
        AppLoadSessionWKhDef = 0,
        AppLoadSessionAccuEndPercentDef
    };

    enum AppMiscellaneous
    {
        AppMiscellaneousMillageYear = 0
    };

 };

#endif // APPSETTINGSDIALOG_H
