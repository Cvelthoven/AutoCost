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

private:
    Ui::DataInputDialog *ui;

    void onApplyPressed();
    void onCancelPressed();
    void onClosePressed();
    void onDiscardPressed();
    void resetDialog();
    void retrieveData();

    QString
        strDate = "",
        strDateFormat = "dd-MM-yyyy",
        strDescription = "",
        strStartTime = "",
        strStartTimeFormat = "HH:mm";

};

#endif // DATAINPUTDIALOG_H
