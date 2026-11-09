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
#include "appsettingdatamodel.h"

#include <QDialog>

//---------------------------------------------------------------------------------------
//
//  Class AppSettings definitions
//
//---------------------------------------------------------------------------------------
namespace Ui {
class AppSettingsDialog;
}

class AppSettingsDialog : public QDialog,
                          public AppSettingDataModel
{
    Q_OBJECT

public:
    AppSettingsDialog(QWidget *parent = nullptr,
                      AppSettingDataModel *AppConfig = nullptr);
    ~AppSettingsDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AppSettingsDialog *ui;

    AppSettingDataModel* ApplicationConfiguration = nullptr;

    double
        dKWhDef;

    int
        iLoadSessionEndPercentage,
        iMillageYear;

    QVector<QString>
        stvDBOptions;

 };

#endif // APPSETTINGSDIALOG_H
