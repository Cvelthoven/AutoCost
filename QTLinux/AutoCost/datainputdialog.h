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
#include "AutoCost.h"

#include <QDialog>
#include <QString>
#include <QTime>

//---------------------------------------------------------------------------------------
//
//  Extra class definitions for the buttonbox in the dialog
//
//---------------------------------------------------------------------------------------
class QDialogButtonBox;
class QAbstractButton;

//---------------------------------------------------------------------------------------
//
//  Class DataInputDialog definitions
//
//---------------------------------------------------------------------------------------
namespace Ui {
class DataInputDialog;
}

class DataInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataInputDialog(QWidget *parent = nullptr);
    ~DataInputDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    //-----------------------------------------------------------------------------------
    //
    //  Slots of dialog
    //
    void on_lnAccuPercentageStart_editingFinished();
    void on_lnAccuPercentageEnd_editingFinished();
    void on_lnMillage_editingFinished();

    void on_rbPeriodic_toggled(bool checked);
    void on_rbElectricity_toggled(bool checked);
    void on_rbOther_toggled(bool checked);
    void on_rbAccessoires_toggled(bool checked);

    void on_rbPublicLoadSession_toggled(bool checked);
    void on_teStartTime_userTimeChanged(const QTime &time);
    void on_lnKWhMax_editingFinished();     //  Default/Max KWh changed
    void on_lnTotalKWh_editingFinished();   // Total KWh changed

    void on_lnKWh1_editingFinished();
    void on_lnKWh2_editingFinished();
    void on_lnKWh3_editingFinished();
    void on_lnKWh4_editingFinished();
    void on_lnKWh5_editingFinished();
    void on_lnKWh6_editingFinished();
    void on_lnKWh7_editingFinished();
    void on_lnKWh8_editingFinished();
    void on_lnKWh9_editingFinished();
    void on_lnKWh10_editingFinished();

    void on_lnPriceKWh1_editingFinished();
    void on_lnPriceKWh2_editingFinished();
    void on_lnPriceKWh3_editingFinished();
    void on_lnPriceKWh4_editingFinished();
    void on_lnPriceKWh5_editingFinished();
    void on_lnPriceKWh6_editingFinished();
    void on_lnPriceKWh7_editingFinished();
    void on_lnPriceKWh8_editingFinished();
    void on_lnPriceKWh9_editingFinished();    
    void on_lnPriceKWh10_editingFinished();


private:
    Ui::DataInputDialog *ui;

    //-----------------------------------------------------------------------------------
    //
    //  Dialog input handle button methods
    //
    void onApplyPressed();
    void onCancelPressed();
    void onClosePressed();
    void onDiscardPressed();

    //-----------------------------------------------------------------------------------
    //
    //  Other methods
    //
    void calcCostNonPublicElectricity();
    void calcNonPublicLoadPerSession(int iColNbChanged);
    void clearElectricityInput();
    void getStartTime();
    void resetDialog();
    void retrieveData();
    void setElectricityDefaultNonPublic();
    void showNonPublicLoadSession();

    //-----------------------------------------------------------------------------------
    //
    //  Private class wide variables
    //
    bool
        bPublicLoadSession = false;

    double
        dAmount = 0.0,          // Amount of the record
        dDefaultKWh = 7.7000,   // default amount load during 1 hour
        dKWhPeriod[iMaxNbElectricityPeriods],   // KWh loaded during a given period
        dKWhPrice[iMaxNbElectricityPeriods],    // Price of KWh during given period
        dTotalKWh = 0.0;        // total amount of KWh loaded during load session

    int
        iAccuEndPercentage = 90,    // default value for a load session
        iAccuStartPercentage = 0,
        iCostType = 0,
        iMillage = 0,
        iStartHour = 0,
        iStartMinute = 0;

     QString
        strDate = "",
        strDateFormat = "dd-MM-yyyy",
        strDescription = "",
        strStartTime = "",
        strStartTimeFormat = "HH:mm";

    QTime
        tiStartTime;

};

#endif // DATAINPUTDIALOG_H
