//---------------------------------------------------------------------------------------
//
//  Module: datainputdialog.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "datainputdialog.h"
#include "ui_datainputdialog.h"

#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QDate>

//---------------------------------------------------------------------------------------
//
//  DataInputDialog default constructor
//
//---------------------------------------------------------------------------------------
DataInputDialog::DataInputDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataInputDialog)
{

    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    //-----------------------------------------------------------------------------------

    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //
    //  Preload fields
    //
    //-----------------------------------------------------------------------------------
    //
    //  Date and time field
    //
    //-----------------------------------------------------------------------------------
    ui->deRecordDate->setDisplayFormat("dd-MM-yyyy");
    ui->deRecordDate->setDate(QDate::currentDate());
    ui->teStartTime->setDisplayFormat("HH:mm");
    ui->teStartTime->setTime(QTime::fromString("00:00"));

}

//---------------------------------------------------------------------------------------
//
//  DataInputDialog default destructor
//
//---------------------------------------------------------------------------------------
DataInputDialog::~DataInputDialog()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
//
//  Handle different responses on DataInputDialog
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    //-----------------------------------------------------------------------------------
    //
    //  Select action based on which button is clicked
    //
    //-----------------------------------------------------------------------------------
    QDialogButtonBox::StandardButton which = ui->buttonBox->standardButton(button);
    switch (which)
    {
    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the input data and store it in the database
    //  And reset the dialog to the default again
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Apply:
        onApplyPressed();
        accept();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Close the dialog without saving possible input
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Cancel:
        onCancelPressed();
        reject();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the input data and store it in the database
    //  And close the dialog
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Close:
        onClosePressed();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Discard possible input data
    //  And reset the dialog to the default again
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Discard:
        onDiscardPressed();
        break;

    default:
        break;
    }

}

//---------------------------------------------------------------------------------------
//
//  Retrieve the input data and store it in the database
//  And reset the dialog to the default again
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onApplyPressed()
{

}

//---------------------------------------------------------------------------------------
//
//  Close the dialog without saving possible input
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onCancelPressed()
{

}

//---------------------------------------------------------------------------------------
//
//  Retrieve the input data and store it in the database
//  And close the dialog
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onClosePressed()
{

}

//---------------------------------------------------------------------------------------
//
//  Discard possible input data
//  And reset the dialog to the default again
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onDiscardPressed()
{
    ui->deRecordDate->setDate(QDate::currentDate());
    ui->lnDescription->clear();
    ui->lnAmount->clear();
    ui->lnKWh1->clear();
    ui->lnKWh2->clear();
    ui->lnKWh3->clear();
    ui->lnKWh4->clear();
    ui->lnKWh5->clear();
    ui->lnKWh6->clear();
    ui->lnKWh7->clear();
    ui->lnKWh8->clear();
    ui->lnKWh9->clear();
    ui->lnKWhMax->clear();
    ui->lnPriceKWh1->clear();
    ui->lnPriceKWh2->clear();
    ui->lnPriceKWh3->clear();
    ui->lnPriceKWh4->clear();
    ui->lnPriceKWh5->clear();
    ui->lnPriceKWh6->clear();
    ui->lnPriceKWh7->clear();
    ui->lnPriceKWh8->clear();
    ui->lnPriceKWh9->clear();
    ui->lnTotalKWh->clear();
    ui->teStartTime->setTime(QTime::fromString("00:00"));

}