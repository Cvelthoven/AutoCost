//---------------------------------------------------------------------------------------
//
//  Module: DetailCostTableModel.cpp
//
//  This class prepares the data from detailcostsqlmodel to be displayed.
//  All reformating and filling the calculated columns are part of this class
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "detailcosttablemodel.h"
#include "postgresqldb.h"

#include <QAbstractTableModel>
#include <QDate>
#include <QTableView>
#include <QString>

#include <QDebug>
//---------------------------------------------------------------------------------------
//
//  DetailCostTableModel default constructor
//
//---------------------------------------------------------------------------------------
DetailCostTableModel::DetailCostTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    qDebug() << "DetailCostTableModel constructor called";

    //-----------------------------------------------------------------------------------
    //
    //  Retrieven the detail cost records
    //
    //-----------------------------------------------------------------------------------
    qDebug() << "DetailCostSqlModel constructor called in DetailCostTableModel constructor";
    DetailedCostSqlTable = new DetailCostSqlModel();

    //-----------------------------------------------------------------------------------
    //
    //  Open the database to be able to retrieve the electricity records
    //
    //-----------------------------------------------------------------------------------
    qDebug() << "db connection for Electricity opened in DetailCostTableModel constructor";
    dbElectricity = new PostGreSQLDB(this);

    //-----------------------------------------------------------------------------------
    //
    //  Fill tblDetailCostValues with the values out of the database and the calculated
    //  values
    //
    //-----------------------------------------------------------------------------------
    for (int iCnt1 = 0; iCnt1 < DetailedCostSqlTable->iNbRows; iCnt1++)
    {
        //-------------------------------------------------------------------------------
        //
        //  Reset variables to empty values
        //
        //-------------------------------------------------------------------------------
        dAccuUsagePercentage = -1;
        dKWhperKM = -1;
        dKWhLoaded = -1;
        dKMPerPercentage = -1;
        dKWhPerPercentage = -1;
        dKWhTrip = -1;
        dMillageTrip = -1;
        dTotalCost = -99999.99;
        dAccuLoadDeltaPercentage = -1;
        dAccuUsagePercentage = -1;
        iAccuStartPercentage = -1;
        iFrequency = -1;
        iMillage = -1;
        iRecId = -1;
        iRecordType = -1;
        strDate = "";
        strDescription = "";
        strStartTime = "";

        //-------------------------------------------------------------------------------
        //
        //  Convert values and load them to tblDetailCostValues
        //
        //-------------------------------------------------------------------------------
        ConvertSqlrecordToTableViewRow(iCnt1);
    }
}

//---------------------------------------------------------------------------------------
//
//  DetailCostTableModel destructor
//
//  Clean up first
//
//---------------------------------------------------------------------------------------
DetailCostTableModel::~DetailCostTableModel()
{
    qDebug() << "DetailCostSqlModel destructor called in DetailCostTableModel destructor";
    delete DetailedCostSqlTable;
    qDebug() << "db close electricity called in DetailCostTableModel destructor";
    delete dbElectricity;
}

//---------------------------------------------------------------------------------------
//
//  Class methodes
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  ConvertSqlrecordToTableViewRow
//
//  Input:
//  - iRowNumber
//
//  Fill the tblDetailCostValues the values
//
//---------------------------------------------------------------------------------------
void DetailCostTableModel::ConvertSqlrecordToTableViewRow(int iRowNumber)
{
    //-----------------------------------------------------------------------------------
    //
    //  Retrieve and convert record to detailtableview layout
    //
    //-----------------------------------------------------------------------------------
    DetailedCostSqlTable->GetRecordData(iRowNumber,
                                        &iRecId,
                                        &iRecordType,
                                        &strDate,
                                        &strDescription,
                                        &dTotalCost,
                                        &iFrequency);
    tblDetailCostValues[iRowNumber][CostOverViewRecID] = QString::number(iRecId);
    tblDetailCostValues[iRowNumber][CostOverViewRecType] = QString::number(iRecordType);

    QDate dtTemp = QDate::fromString(strDate, "yyyy-MM-dd");
    if (dtTemp.isValid())
    {
        tblDetailCostValues[iRowNumber][CostOverViewDate] = dtTemp.toString("dd-MMM-yyyy");
    }
    tblDetailCostValues[iRowNumber][CostOverViewDescription] = strDescription;

    switch (iRecordType) {
    case CostRecPeriodic:
        tblDetailCostValues[iRowNumber][CostOverViewPeriodic] = QString::number(dTotalCost, 'f', 2);
        break;

    case CostRecElectricity:
        tblDetailCostValues[iRowNumber][CostOverViewElectricity] = QString::number(dTotalCost, 'f', 2);
        if (GetElectricityRecord(iRecId) == 0)
        {
            tblDetailCostValues[iRowNumber][CostOverViewMillage] = QString::number(iMillage);
            tblDetailCostValues[iRowNumber][CostOverViewMillageTrip] = QString::number(dMillageTrip, 'f', 0);
            tblDetailCostValues[iRowNumber][CostOverViewKWhTrip] = QString::number(dKWhTrip, 'f', 3);
            tblDetailCostValues[iRowNumber][CostOverViewKWhLoaded] = QString::number(dKWhLoaded, 'f', 1);
            tblDetailCostValues[iRowNumber][CostOverViewKWhperKM] = QString::number(dKWhperKM, 'f', 3);
            tblDetailCostValues[iRowNumber][CostOverViewKWhPerPercentage] = QString::number(dKWhPerPercentage, 'f', 4);
            tblDetailCostValues[iRowNumber][CostOverViewKMPerPercentage] = QString::number(dKMPerPercentage, 'f', 4);
            tblDetailCostValues[iRowNumber][CostOverViewAvgEuroPerKWh] = QString::number(dAvgEuroPerKWh, 'f', 3);
            tblDetailCostValues[iRowNumber][CostOverViewAccuStartPercentage] = QString::number(iAccuStartPercentage);
            tblDetailCostValues[iRowNumber][CostOverViewAccuEndPercentage] = QString::number(iAccuEndPercentage);
            tblDetailCostValues[iRowNumber][CostOverViewAccuUsagePercentage] = QString::number(dAccuUsagePercentage, 'f', 0);
            tblDetailCostValues[iRowNumber][CostOverViewAccuLoadDeltaPercentage] = QString::number(dAccuLoadDeltaPercentage, 'f', 0);


        }

        break;

    case CostRecOther:
        tblDetailCostValues[iRowNumber][CostOverViewOther] = QString::number(dTotalCost, 'f', 2);
        break;

    case CostRecAccessory:
        tblDetailCostValues[iRowNumber][CostOverViewAccessory] = QString::number(dTotalCost, 'f', 2);
        break;

    default:
        break;
    }

    tblDetailCostValues[iRowNumber][CostOverViewPeriod] = QString::number(iFrequency);


}

//---------------------------------------------------------------------------------------
//
//  GetElectricityRecord
//
//  Retrieves the related electricity record when the recordtype is electricity
//
//---------------------------------------------------------------------------------------
int DetailCostTableModel:: GetElectricityRecord(int &iRecID)
{
    //-----------------------------------------------------------------------------------
    //
    //  Built query
    //
    //-----------------------------------------------------------------------------------
    QString strElectricityQuery = "SELECT * FROM public.\"acElectricity\" Where \"AutoCostRecId\" = \'"
        + QString::number(iRecID) + "\'";

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve corresponding electricity record and convert it
    //
    //-----------------------------------------------------------------------------------
    if (dbElectricity->SelectQuery(&strElectricityQuery) == 1)
    {
        for (int iCnt1 = ElecRecRecID; iCnt1 < ElecRecAutoCostRecID; iCnt1++)
        {
            switch (iCnt1) {
            case ElecRecRecID:
                // Not used
                break;
            case ElecRecDate:
                strDate = dbElectricity->stlRecordContent.at(iCnt1);
                break;
            case ElecRecKmTotal:
                iMillage = dbElectricity->stlRecordContent.at(iCnt1).toInt();
                dMillageTrip = iMillage - iMillagePrevious;
                iMillagePrevious = iMillage;
                break;
            case ElekRecKWhLoaded:
                dKWhLoaded = dbElectricity->stlRecordContent.at(iCnt1).toDouble();
                break;
            case ElecRecCapBatStart:
                iAccuStartPercentage = dbElectricity->stlRecordContent.at(iCnt1).toInt();
                break;
            case ElecRecCapBatEnd:
                iAccuEndPercentagePrevious = iAccuEndPercentage;
                iAccuEndPercentage = dbElectricity->stlRecordContent.at(iCnt1).toInt();
                break;
            case ElecRecStartTime:
                strDate = dbElectricity->stlRecordContent.at(iCnt1);
                break;
            case ElecRecAutoCostRecID:
                // Not used, already defined in query
            default:
                break;
            }

        }

        //---------------------------------------------------------------------------
        //
        //  Calculate the calculated values
        //  Order of the calculates is important
        //
        //---------------------------------------------------------------------------
        //
        //  Load Delta percentage
        //  delta = end current - start current load session
        //
        dAccuLoadDeltaPercentage = iAccuEndPercentage - iAccuStartPercentage;

        //
        //  Percentage Usaged
        //  usage = end previous load - start current load
        //
        dAccuUsagePercentage = iAccuEndPercentagePrevious - iAccuStartPercentage;

        //
        //  KWh/%
        //  KWh/% = KWhLoaded / (end current load - start current load)
        //
        dKWhPerPercentage = dKWhLoaded / dAccuLoadDeltaPercentage;

        //
        //  KM/%
        //  KM/% = (Millage current - Millage previous trip) /
        //          (end current load - start current load)
        //
        dKMPerPercentage = dMillageTrip / dAccuLoadDeltaPercentage;

        //
        // KWh used in trip = percentage used * KWh/%
        //
        //
        dKWhTrip = dAccuUsagePercentage * dKWhPerPercentage;

        //
        //  Average KWh price of current loading session
        //  Electricity cost / KWh loaded
        //
        dAvgEuroPerKWh = dTotalCost / dKWhLoaded;


        //
        //  Average KWh/km
        //  KWh loaded / Millage trip
        //
        dKWhperKM = dKWhLoaded / dMillageTrip;

        return 0;
    }
    else
    {
        return -1;
    }

}

//---------------------------------------------------------------------------------------
//
//  rowCount
//
//  Set the number of rows in the overview
//  Required methods for QAbstractTableModel
//
//---------------------------------------------------------------------------------------
int DetailCostTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    int iNBRows = DetailedCostSqlTable->iNbRows;
    return iNBRows;
}

//---------------------------------------------------------------------------------------
//
//  columnCount
//
//  Set the number of columns in overview
//  Required methods for QAbstractTableModel
//
//---------------------------------------------------------------------------------------
int DetailCostTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return CostOverViewPeriod + 1;
}

//---------------------------------------------------------------------------------------
//
//  data
//
//  Displays the data in tblDetailCostValues
//
//---------------------------------------------------------------------------------------
QVariant DetailCostTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && checkIndex(index))
        return tblDetailCostValues[index.row()][index.column()];

    //-----------------------------------------------------------------------------------
    //
    //  Set the column and row alignment
    //
    //-----------------------------------------------------------------------------------
    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column()) {
        case CostOverViewRecID:
        case CostOverViewRecType:
        case CostOverViewDate:
        case CostOverViewAccuStartPercentage:
        case CostOverViewAccuEndPercentage:
        case CostOverViewAccuUsagePercentage:
            return int(Qt::AlignHCenter | Qt::AlignVCenter);
            break;
        case CostOverViewPeriodic:
        case CostOverViewElectricity:
        case CostOverViewOther:
        case CostOverViewAccessory:
        case CostOverViewMillage:
        case CostOverViewMillageTrip:
        case CostOverViewKWhTrip:
        case CostOverViewKWhLoaded:
        case CostOverViewKWhperKM:
        case CostOverViewAvgEuroPerKWh:
        case CostOverViewKWhPerPercentage:
        case CostOverViewKMPerPercentage:
        case CostOverViewAccuLoadDeltaPercentage:
            return int(Qt::AlignRight | Qt::AlignVCenter);
        default:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
            break;
        }
    }

    return QVariant();
}

//---------------------------------------------------------------------------------------
//
//  setData
//
//  Fills tblDetailCostValues with the converted values from the sqlquery
//
//  Now reacts to update in window
//
//---------------------------------------------------------------------------------------
bool DetailCostTableModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        tblDetailCostValues[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emit a joined string
        QString result;
        for (int row = 0; row < 109; row++) {
            for (int col= 0; col < CostOverViewPeriod; col++)
                result += tblDetailCostValues[row][col] + ' ';
        }
        emit editCompleted(result);
        return true;
    }
    return false;}



//---------------------------------------------------------------------------------------
//
//  headerData
//
//  Set the headers of the columns
//
//---------------------------------------------------------------------------------------
QVariant DetailCostTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case CostOverViewRecID:
            return QString("RecID");
        case CostOverViewRecType:
            return QString("Type");
        case CostOverViewDate:
            return QString("Date");
        case CostOverViewDescription:
            return QString("Description");
        case CostOverViewPeriodic:
            return QString("Periodic");
        case CostOverViewElectricity:
            return QString("Electricity");
        case CostOverViewOther:
            return QString("Other");
        case CostOverViewAccessory:
            return QString("Accessory");
        case CostOverViewMillage:
            return QString("Millage");
        case CostOverViewMillageTrip:
            return QString("KM Trip");
        case CostOverViewKWhTrip:
            return QString("kWh Trip");
        case CostOverViewKWhLoaded:
            return QString("kWh Loaded");
        case CostOverViewKWhperKM:
            return QString("kWh/km");
        case CostOverViewAvgEuroPerKWh:
            return QString("Avg Euro/kWh");
        case CostOverViewKWhPerPercentage:
            return QString("kWh/%");
        case CostOverViewKMPerPercentage:
            return QString("km/%");
        case CostOverViewAccuStartPercentage:
            return QString("Accu Start");
        case CostOverViewAccuEndPercentage:
            return QString("Accu End");
        case CostOverViewAccuUsagePercentage:
            return QString("Accu Usage");
        case CostOverViewAccuLoadDeltaPercentage:
            return QString("Load Delta");
        case CostOverViewPeriod:
            return QString("Period");

        }
    }
    return QVariant();
}

Qt::ItemFlags DetailCostTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}