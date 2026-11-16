//---------------------------------------------------------------------------------------
//
//  Module: dialogupdatedatabase.h
//
//  Class DialogUpdateDatabase controls the dialog to update the database
//  The dialog let the user select the *.csv file with electricity data that must be
//  loaded. Returns information about the data in the *.csv file and gives the
//  user the option to actual store the data into the database.
//
//  Reading the *.csv file is done with the claas ReadCsvElectricityFile.
//  Storing the data found is done with the class ReadCsvElectricityFile
//
//---------------------------------------------------------------------------------------
#ifndef DIALOGUPDATEDATABASE_H
#define DIALOGUPDATEDATABASE_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QDialog>

//---------------------------------------------------------------------------------------
//
//  Class DialogUpdateDatabase definitions
//
//---------------------------------------------------------------------------------------
namespace Ui {
class DialogUpdateDatabase;
}

class DialogUpdateDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUpdateDatabase(QWidget *parent = nullptr);
    ~DialogUpdateDatabase();

private slots:
    void on_btDbLoadRecords_clicked();
    void on_btReadInputFile_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_lneFileName_editingFinished();

private:
    Ui::DialogUpdateDatabase *ui;
};

#endif // DIALOGUPDATEDATABASE_H
