//---------------------------------------------------------------------------------------
//
//  Module: datainputdialog.h
//
//---------------------------------------------------------------------------------------
#ifndef DATAINPUTDIALOG_H
#define DATAINPUTDIALOG_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
//#include "appsettings.h"
#include "AutoCost.h"
#include "appsettingdatamodel.h"
#include "datainput.h"
#include "electricitycostinputmodel.h"

#include <QDialog>
#include <QString>
#include <QTime>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  Extra class definitions for the buttonbox in the dialog
//
//---------------------------------------------------------------------------------------
class QDialogButtonBox;
class QAbstractButton;
class QLineEdit;
class QLabel;

//---------------------------------------------------------------------------------------
//
//  Class DataInputDialog definitions
//
//---------------------------------------------------------------------------------------
namespace Ui {
class DataInputDialog;
}

class DataInputDialog : public QDialog,
                        public AppSettingDataModel
{
    Q_OBJECT

public:
    explicit DataInputDialog(QWidget *parent = nullptr,
                      AppSettingDataModel *AppConfig = nullptr);
    ~DataInputDialog();

    //---------------------------------------------------------------------------------------
    //
    //  Getter and Setter Methods
    //
    //---------------------------------------------------------------------------------------
    bool getBClosePressed() const;

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    //-----------------------------------------------------------------------------------
    void resetDialog();

signals:
    void signLoadElectricityDefaults();//  Signal show default electricity input


private slots:
    void loadElectricityDefaults(); //  Show defaults electricity input
    void on_buttonBox_clicked(QAbstractButton *button);

    //-----------------------------------------------------------------------------------
    //
    //  Slots of dialog
    //
    void on_lnAccuPercentageStart_editingFinished();
    void on_lnAccuPercentageEnd_editingFinished();
    void on_lnMillage_editingFinished();

    void on_rbElectricity_toggled(bool checked);
    void on_deRecordDate_dateChanged(const QDate &date);

    void on_rbPublicLoadSession_toggled(bool checked);
    void on_teStartTime_userTimeChanged(const QTime &time);
    void on_lnKWhMax_editingFinished();     //  Default/Max KWh changed
    void on_lnTotalKWh_editingFinished();   // Total KWh changed


private:
    Ui::DataInputDialog *ui;

    //-----------------------------------------------------------------------------------
    //
    //  Other methods
    //
    void calcCostNonPublicElectricity();
    void calcNonPublicLoadPerSession(int iColNbChanged);
    void getStartTime();
    void retrieveData();
    void storeData();

    //-----------------------------------------------------------------------------------
    //
    //  Private class wide variables
    //
    bool
        bClosePressed = false,
        bFirstLoadPeriodChanged = false,
        bPublicLoadSession = false,
        bStartLoadTimeChanged = false;

    const int
        iMaxNbElectricityPeriods = 10;

    double
        dAmount = 0.0,          // Amount of the record
        dDefaultKWh = -1.0,   // default amount load during 1 hour
        dKWhPeriod[10],   // KWh loaded during a given period, must be dynamic !!!!!!
        dKWhPrice[10],    // Price of KWh during given period, must be dynamic !!!!!
        dTotalKWh = 0.0;        // total amount of KWh loaded during load session

    int
        iAccuEndPercentage = -1,    // default value for a load session
        iAccuStartPercentage = 0,
        iCostType = 0,
        iMillage = 0,
        iStartHour = 0,
        iStartMinute = 0;


    QDate
        daRecordDate;

    QString
        strDate = "",
        strDateFormat = "dd-MM-yyyy",
        strDescription = "",
        strStartTime = "",
        strStartTimeFormat = "HH:mm";

    QTime
        tiStartTime;

    DataInput *dbData;

    AppSettingDataModel* ApplicationConfiguration = nullptr;
    ElectricityCostInputModel *ElectricityCostModel = nullptr;

};

#endif // DATAINPUTDIALOG_H
