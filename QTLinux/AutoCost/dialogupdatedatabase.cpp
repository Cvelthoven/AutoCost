//---------------------------------------------------------------------------------------
//
//  Module: dialogupdatedatabase.cpp
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
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "dialogupdatedatabase.h"
#include "ui_dialogupdatedatabase.h"

//---------------------------------------------------------------------------------------
//
//  Not already defined in dialogupdatedatabase.h
//
#include <QFileDialog>

//---------------------------------------------------------------------------------------
//
//  Class DialogUpdateDatabase constructors and destructors
//
//---------------------------------------------------------------------------------------
DialogUpdateDatabase::DialogUpdateDatabase(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogUpdateDatabase)
{
    //-----------------------------------------------------------------------------------
    //
    //  Setup dialog
    //
    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //
    //  Execute dialog
    //
    DialogUpdateDatabase::exec();
}

DialogUpdateDatabase::~DialogUpdateDatabase()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
//
//  Class DialogUpdateDatabase methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  on_btDbLoadRecords_clicked
//
//---------------------------------------------------------------------------------------
void DialogUpdateDatabase::on_btDbLoadRecords_clicked()
{

}

//---------------------------------------------------------------------------------------
//
//  on_btFileNameBrowse_clicked
//
//  Allows the user to select a file from the filesystem
//
//---------------------------------------------------------------------------------------
void DialogUpdateDatabase::on_btFileNameBrowse_clicked()
{
    strCsvFileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open electricity data file"),
                                                    QString(),
                                                    tr("All files (*)"));
    if (strCsvFileName.length() != 0)
    {
        ui->lneFileName->setText(strCsvFileName);
    }
    else
    {
        ui->lneFileName->setText("");

    }

}

//---------------------------------------------------------------------------------------
//
//  on_btReadInputFile_clicked
//
//  Reads the selected file and shows fileinformation in the dialog
//  Uses ReadCsvElectricityFile
//
//---------------------------------------------------------------------------------------
void DialogUpdateDatabase::on_btReadInputFile_clicked()
{
    if (strCsvFileName.length() != 0)
    {
        reElectricityFileData = new ReadCsvElectricityFile();
        if (reElectricityFileData->ReadFile(&strCsvFileName) == 0)
        {
            ui->lneRecordNumber->setText(
                QString::number(reElectricityFileData->getILineTotal()));
            ui->lneRecordFirst->setText(
                reElectricityFileData->getQdFirstRecordDate().toString("dd-MMM-yyyy"));
            ui->lneRecordLast->setText(
                reElectricityFileData->getQdLastRecordDate().toString("dd-MMM-yyyy"));
        }
        else
        {
            qDebug() << "Reading " << strCsvFileName << " failed";
        }
    }
}

//---------------------------------------------------------------------------------------
//
//  on_buttonBox_accepted
//
//---------------------------------------------------------------------------------------
void DialogUpdateDatabase::on_buttonBox_accepted()
{

}

//---------------------------------------------------------------------------------------
//
//  on_buttonBox_rejected
//
//---------------------------------------------------------------------------------------
void DialogUpdateDatabase::on_buttonBox_rejected()
{

}

//---------------------------------------------------------------------------------------
//
//  on_lneFileName_editingFinished
//
//---------------------------------------------------------------------------------------
void DialogUpdateDatabase::on_lneFileName_editingFinished()
{

}
