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
#include <QDialog>
#include <QString>

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
    //  Cost type selection radiobutton slots
    //
    void on_rbPeriodic_toggled(bool checked);
    void on_rbElectricity_toggled(bool checked);
    void on_rbOther_toggled(bool checked);
    void on_rbAccessoires_toggled(bool checked);

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
    void clearElectricityInput();
    void resetDialog();
    void retrieveData();

    //-----------------------------------------------------------------------------------
    //
    //  Private class wide variables
    //
    int
        iCostType = 0;

    QString
        strDate = "",
        strDateFormat = "dd-MM-yyyy",
        strDescription = "",
        strStartTime = "",
        strStartTimeFormat = "HH:mm";

};

#endif // DATAINPUTDIALOG_H
