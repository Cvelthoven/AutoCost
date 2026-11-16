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


//---------------------------------------------------------------------------------------
//
//  Class DialogUpdateDatabase constructors and destructors
//
//---------------------------------------------------------------------------------------
DialogUpdateDatabase::DialogUpdateDatabase(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogUpdateDatabase)
{
    ui->setupUi(this);
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
