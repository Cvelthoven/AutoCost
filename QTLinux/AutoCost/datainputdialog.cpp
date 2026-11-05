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
#include <QTime>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  DataInputDialog default constructor
//
//---------------------------------------------------------------------------------------
DataInputDialog::DataInputDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::DataInputDialog)
{

    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //
    //  Setup signal slot configuration
    //
    connect(this, &DataInputDialog::signLoadElectricityDefaults,
            this, &DataInputDialog::loadElectricityDefaults);

    //-----------------------------------------------------------------------------------
    //
    //  Preload fields
    //
    //-----------------------------------------------------------------------------------
    //
    //  Date and time field and label
    //
    ui->deRecordDate->setDisplayFormat(strDateFormat);
    ui->teStartTime->setDisplayFormat(strStartTimeFormat);

    //-----------------------------------------------------------------------------------
    //
    //  Set the radiobutton id's
    //
    ui->CostButtonGroup->setId(ui->rbPeriodic, 1);
    ui->CostButtonGroup->setId(ui->rbElectricity, 2);
    ui->CostButtonGroup->setId(ui->rbOther, 3);
    ui->CostButtonGroup->setId(ui->rbAccessoires, 4);

    //-----------------------------------------------------------------------------------
    //
    //  Fill the dialog with the default values
    //
    resetDialog();

    //-----------------------------------------------------------------------------------
    //
    //  Create tablemodel
    //  Move to the signal slot loadElectricityDefaults
    //
    // ElectricityCostModel = new ElectricityCostInputModel(this);
    // ElectricityCostModel->loadDataDefault();
    // ui->tblElectricityCostInput->setModel(ElectricityCostModel);

    //-----------------------------------------------------------------------------------
    //
    //  Format table
    //
    ui->tblElectricityCostInput->setAlternatingRowColors(true);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputHour, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputHour00, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputKWh00, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputHour15, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputKWh15, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputHour30, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputKWh30, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputHour45, 55);
    ui->tblElectricityCostInput->setColumnWidth(ElectricityCostInputKWh45, 55);
}

//---------------------------------------------------------------------------------------
//
//  DataInputDialog default destructor
//
//---------------------------------------------------------------------------------------
DataInputDialog::~DataInputDialog()
{
    delete ui;
    qDebug() << "DataInputDialog destructor called";
}

//---------------------------------------------------------------------------------------
//
//  Class methods
//
//---------------------------------------------------------------------------------------
//
//  calcCostNonPublicElectricity
//
//  Calculate non-pulbic electricity load session cost and show it in dialog
//
//---------------------------------------------------------------------------------------
void DataInputDialog::calcCostNonPublicElectricity()
{
    dAmount = 0.0;
    for (int iCnt1 = 0; iCnt1 < iMaxNbElectricityPeriods; iCnt1++)
    {
        dAmount = dAmount + (dKWhPeriod[iCnt1] * dKWhPrice[iCnt1]);
    }
    ui->lnAmount->setText(QString::number(dAmount,'f', 2));
}

//---------------------------------------------------------------------------------------
//
//  calcNonPublicLoadPerSession
//
//  (Re)colculate non-public electricity load session load per period
//
//  Input:
//      - iColNbChanged: number of the period that is changed, next periods will
//        be recalculated
//
//---------------------------------------------------------------------------------------
void DataInputDialog::calcNonPublicLoadPerSession(int iColNbChanged)
{
    //-----------------------------------------------------------------------------------
    //
    //  local variables
    //
    double dSubTotalKWh = 0.0,
        dRestKWh = 0.0;

    int iCnt1 = 0;

    //-----------------------------------------------------------------------------------
    //
    //  (Re)calc amount from start untill and including period that is changed
    //
    iCnt1 = 0;
    while (iCnt1 <= iColNbChanged)
    {
        dSubTotalKWh += dKWhPeriod[iCnt1];
        iCnt1++;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Calc the amount of the first period
    //  If the first period is set manually then no action
    //
    if (iColNbChanged == 0)
    {
        if ((bFirstLoadPeriodChanged)||(bStartLoadTimeChanged))
        {
            dKWhPeriod[0] = dDefaultKWh * (static_cast<double>(60 - iStartMinute)/60);
            dKWhPeriod[0] = std::round(dKWhPeriod[0] * 1000) / 1000;
            bFirstLoadPeriodChanged = false;
            bStartLoadTimeChanged = false;
        }
        dSubTotalKWh = dKWhPeriod[0];
        iCnt1 = 1;
    }
    dRestKWh = dTotalKWh - dSubTotalKWh;

    //-----------------------------------------------------------------------------------
    //
    //  (Re)calc the remaining periods, overwrite value with default
    //
    while ((dRestKWh >= dDefaultKWh) && (iCnt1 < (iMaxNbElectricityPeriods -1)))
    {
        dKWhPeriod[iCnt1] = dDefaultKWh;
        dRestKWh -= dKWhPeriod[iCnt1];
        iCnt1++;
    }

    //-----------------------------------------------------------------------------------
    //
    //  (Re)calc the last period, and if needed add an extra period
    //
    dKWhPeriod[iCnt1] = dRestKWh;
}

//---------------------------------------------------------------------------------------
//
//  getBClosePressed
//
//---------------------------------------------------------------------------------------
bool DataInputDialog::getBClosePressed() const
{
    return bClosePressed;
}

//---------------------------------------------------------------------------------------
//
//  getStartTime
//
//  Load start time from the dialog box and set the first hour label
//
//---------------------------------------------------------------------------------------
void DataInputDialog::getStartTime()
{
    tiStartTime = ui->teStartTime->time();
    iStartHour = tiStartTime.hour();
    iStartMinute = tiStartTime.minute();
    strStartTime = tiStartTime.toString("hh:mm");

}

//---------------------------------------------------------------------------------------
//
//  loadElectricityDefaults
//
//  Slot: show the default default values of the electricity input:
//      - default start time of load session
//      - default max KWh
//      - default end load session accu percentage
//
//---------------------------------------------------------------------------------------
void DataInputDialog::loadElectricityDefaults()
{
    ui->lnDescription->setText("Laden");
    ui->teStartTime->setDisplayFormat(strStartTimeFormat);
    ui->teStartTime->setTime(QTime::fromString("00:00"));
    ui->lnKWhMax->setText(QString::number(dKWhMaxDefault,'f', 1));
    ui->lnAccuPercentageEnd->setText(QString::number(iAccuEndPercentageDefault));

    //-----------------------------------------------------------------------------------
    //
    //  Create tablemodel
    //
    ElectricityCostModel = new ElectricityCostInputModel(this);
    ElectricityCostModel->loadDataDefault();
    ui->tblElectricityCostInput->setModel(ElectricityCostModel);

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
    QDialogButtonBox::StandardButton which = ui->buttonBox->standardButton(button);
    switch (which)
    {
    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the input data and store it in the database
    //  And reset the dialog to the default again
    //
    case QDialogButtonBox::Apply:
        retrieveData();
        storeData();
        accept();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Close the dialog without saving possible input
    //
    case QDialogButtonBox::Cancel:
        reject();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the input data and store it in the database
    //  And close the dialog
    //
    case QDialogButtonBox::Close:
        bClosePressed = true;
        retrieveData();
        storeData();
        accept();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Discard possible input data
    //  And reset the dialog to the default again
    //
    case QDialogButtonBox::Discard:
        resetDialog();
        break;

    default:
        break;
    }
}

//---------------------------------------------------------------------------------------
//
//  Reset the in-memory electricity input
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_deRecordDate_dateChanged(const QDate &date)
{
    if (ElectricityCostModel)
        ElectricityCostModel->loadDataDefault();
}

//---------------------------------------------------------------------------------------
//
//  on_lnAccuPercentageEnd_editingFinished
//  Slot to handle the end percentage af the accu of the loading session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnAccuPercentageEnd_editingFinished()
{
    iAccuEndPercentage = ui->lnAccuPercentageEnd->text().toInt();
}

//---------------------------------------------------------------------------------------
//
//  on_lnAccuPercentageStart_editingFinished
//  Slot to handle the start percentage af the accu of the loading session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnAccuPercentageStart_editingFinished()
{
    iAccuStartPercentage = ui->lnAccuPercentageStart->text().toInt();
}

//---------------------------------------------------------------------------------------
//
//  Default/Max KWh load session changed
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnKWhMax_editingFinished()
{
    dDefaultKWh = ui->lnKWhMax->text().toDouble();
    calcNonPublicLoadPerSession(0);
    calcCostNonPublicElectricity();
}

//---------------------------------------------------------------------------------------
//
//  on_lnMillage_editingFinished
//  Slot to handle the millage at the start of a load session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnMillage_editingFinished()
{
    iMillage = ui->lnMillage->text().toInt();
}

//---------------------------------------------------------------------------------------
//
//  Loads total amount loaded and the start time set at that moment to ensure that also
//  the default time is loaded in case this is the correct time.
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnTotalKWh_editingFinished()
{
    getStartTime();
    dTotalKWh = ui->lnTotalKWh->text().toDouble();
    //-----------------------------------------------------------------------------------
    //
    //  Load the defaults for a non-public load session
    //
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(-1);    // no values set yet
        calcCostNonPublicElectricity();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Load the defaults for a public load session
    //
    else
    {

    }
}

//---------------------------------------------------------------------------------------
//
//  Handle electricity radio button
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_rbElectricity_toggled(bool checked)
{
    if (checked)
    {
        iCostType = CostRecElectricity;
        emit signLoadElectricityDefaults();

//        setElectricityDefaultNonPublic();
    }
    else
    {
        iCostType = 0;
    }
}

//---------------------------------------------------------------------------------------
//
//  Handle the switch between a non-public and public load session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_rbPublicLoadSession_toggled(bool checked)
{
    if (checked)
    {
        bPublicLoadSession = true;
        emit signLoadElectricityDefaults();

//        setElectricityDefaultNonPublic();
    }
    else
    {
        bPublicLoadSession = false;
    }
}

//---------------------------------------------------------------------------------------
//
//  Retrieve time set by user
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_teStartTime_userTimeChanged(const QTime &time)
{
    //-----------------------------------------------------------------------------------
    //
    //  Only retrieve time when cost type is electricity otherwise ignore or discard
    //
    if (iCostType == 2)
    {
        bFirstLoadPeriodChanged = true;
        getStartTime();
        calcNonPublicLoadPerSession(0);
        calcCostNonPublicElectricity();
    }
}

//---------------------------------------------------------------------------------------
//
//  resetDialog
//  Reset the dialog to the default again
//
//---------------------------------------------------------------------------------------
void DataInputDialog::resetDialog()
{

    ui->deRecordDate->setDate(QDate::currentDate());

    ui->lnDescription->clear();
    strDescription = "";

    ui->lnAmount->clear();
    dAmount = 0.0;          // Amount of the record

    ui->teStartTime->clear();
    iStartHour = 0;
    iStartMinute = 0;

    dDefaultKWh = dKWhMaxDefault;// default amount load during 1 hour
    dTotalKWh = 0.0;        // total amount of KWh loaded during load session
    iAccuEndPercentage = iAccuEndPercentageDefault;// default value for a load session
    iAccuStartPercentage = 0;
    iCostType = 0;
    iMillage = 0;
    strDate = "";
    strStartTime = "";
    bFirstLoadPeriodChanged = false;
    bPublicLoadSession = false;
    bStartLoadTimeChanged = false;

    bClosePressed = false;
    ui->lnDescription->setFocus();
}

//---------------------------------------------------------------------------------------
//
//  Retrieve input data from dialog
//  Except the electricity data
//
//---------------------------------------------------------------------------------------
void DataInputDialog::retrieveData()
{

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve data
    //
    daRecordDate = ui->deRecordDate->date();
    strDescription = ui->lnDescription->text();
    dAmount = ui->lnAmount->text().toFloat();
}

//---------------------------------------------------------------------------------------
//
//  Store the data to the database
//
//---------------------------------------------------------------------------------------
void DataInputDialog::storeData()
{
    dbData = new DataInput();
    dbData->setIRecordType(iCostType);
    dbData->setDaDate(daRecordDate);
    dbData->setStrDescription(strDescription);
    dbData->setDTotalCost(dAmount);
    if (dbData->addAcAutoCostRecord() == 0)
    {
        if (iCostType == CostRecElectricity)
        {
            dbData->setBPublicLoadSession(bPublicLoadSession);
            dbData->setIKmTotal(iMillage);
            dbData->setDKWhLoaded(dTotalKWh);
            dbData->setICapBatteryStart(iAccuStartPercentage);
            dbData->setICapBatteryEnd(iAccuEndPercentage);
            dbData->setTiStartTime(tiStartTime);
            if (dbData->addAcElectricityRecord() != 0)
            {
                // If insert of acElectricity record fails, a rollback or delete of the
                // corresponding insert of acAutoCost is required
            }
        }
    }
}
