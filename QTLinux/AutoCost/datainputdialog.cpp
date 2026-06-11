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
    case QDialogButtonBox::Ok:
        // action for OK
        onOKPressed();
        accept();
        break;

    case QDialogButtonBox::Cancel:
        // action for Cancel
        reject();
        break;

    case QDialogButtonBox::Apply:
        // action for Apply
        // do something without closing the dialog
        break;

    case QDialogButtonBox::Reset:
        // action for Reset
        // clear or reset fields
        break;

    default:
        break;
    }

}

void DataInputDialog::onOKPressed()
{

}

void DataInputDialog::onCancelPressed()
{

}

void DataInputDialog::onApplyPressed()
{

}

void DataInputDialog::onResetPressed()
{

}