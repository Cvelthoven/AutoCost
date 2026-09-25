//---------------------------------------------------------------------------------------
//
//  Module: detailcostdatamodel.cpp
//
//  This class manages the detail cost data
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "detailcostdatamodel.h"

#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostDataModel constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  Default constructor and destructor
//
//---------------------------------------------------------------------------------------
DetailCostDataModel::DetailCostDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    //-----------------------------------------------------------------------------------
    //
    //  Reuse open Application database connection
    //
    dbAutoCost = QSqlDatabase::database(strApplicationDatabaseConnectionName, false);
    if ((dbAutoCost.isValid()) && (dbAutoCost.isOpen()))
    {
        bAppDataOpen = true;
    }
    else
    {
        bAppDataOpen = false;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set column headers
    //
    strHeaders = {
        "Date",
        "Description",
        "Periodic",
        "Electricity",
        "Other",
        "Accessories",
        "Milage total",
        "Milage trip",
        "KWh trip",
        "KWh Loaded",
        "KWh/km",
        "Avg €/KWh",
        "KWh/%",
        "km/%",
        "Battery Start",
        "Battery End",
        "Battery Used",
        "Load Delta",
        "Start Time",
        "Auto ID",
        "Elec ID",
        "Type",
        "Frequency"
    };
}

DetailCostDataModel::~DetailCostDataModel()
{
}

//---------------------------------------------------------------------------------------
//
//  DetailCostDataModel class methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  buildDetailCostQuery
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::buildDetailCostQuery() const
{
    return QString(
        "SELECT "
        "    ac.\"AutoCostRecID\" AS \"ID\", "
        "    ac.\"RecordType\" AS \"Type\", "
        "    ac.\"Date\" AS \"Date\", "
        "    ac.\"Description\" AS \"Description\", "
        "    ac.\"TotalCost\" AS \"Total Cost\", "
        "    ac.\"Frequency\" AS \"Frequency\", "
        "    el.\"ElecRecId\" AS \"Elec ID\", "
        "    el.\"KmTotal\" AS \"Km Total\", "
        "    el.\"KWhLoaded\" AS \"KWh Loaded\", "
        "    el.\"CapBatteryStart\" AS \"Battery Start\", "
        "    el.\"CapBatteryEnd\" AS \"Battery End\", "
        "    el.\"StartTime\" AS \"Start Time\" "
        "FROM public.\"acAutoCost\" ac "
        "LEFT JOIN public.\"acElectricity\" el "
        "    ON el.\"AutoCostRecId\" = ac.\"AutoCostRecID\" "
        "ORDER BY ac.\"Date\" ASC, el.\"KmTotal\" ASC NULLS LAST"
        );
}

//---------------------------------------------------------------------------------------
//
//  getTotalAccessory
//
//  Returns the vector with the totals per year of the periodic cost
//
//---------------------------------------------------------------------------------------
QVector<double> DetailCostDataModel::getTotalAccessory() const
{
    return dTotalAccessory;
}

//---------------------------------------------------------------------------------------
//
//  getTotalCost
//
//  Returns the vector with the totals per year of the total cost
//
//---------------------------------------------------------------------------------------
QVector<double> DetailCostDataModel::getTotalCost() const
{
    return dTotalCost;
}

//---------------------------------------------------------------------------------------
//
//  getTotalElectricity
//
//  Returns the vector with the totals per year of the electricity cost
//
//---------------------------------------------------------------------------------------
QVector<double> DetailCostDataModel::getTotalElectricity() const
{
    return dTotalElectricity;
}

//---------------------------------------------------------------------------------------
//
//  getTotalOtherCost
//
//  Returns the vector with the totals per year of the other cost
//
//---------------------------------------------------------------------------------------
QVector<double> DetailCostDataModel::getTotalOtherCost() const
{
    return dTotalOtherCost;
}

//---------------------------------------------------------------------------------------
//
//  getTotalPeriodic
//
//  Returns the vector with the totals per year of the periodic cost
//
//---------------------------------------------------------------------------------------
QVector<double> DetailCostDataModel::getTotalPeriodic() const
{
    return dTotalPeriodic;
}

//---------------------------------------------------------------------------------------
//
//  getYears
//
//  Returns the vector with the year values
//
//---------------------------------------------------------------------------------------
QVector<int> DetailCostDataModel::getYears() const
{
    return iYears;
}

//---------------------------------------------------------------------------------------
//
//  loadDetailCostData
//
//---------------------------------------------------------------------------------------
bool DetailCostDataModel::loadDetailCostData()
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    //-----------------------------------------------------------------------------------
    int
        iDataColumnNb = 0,
        iDataColums = 0,
        iViewColumn = 0;

    QString
        strValue = "";

    //-----------------------------------------------------------------------------------
    //
    //  Verify database is open
    //
    //-----------------------------------------------------------------------------------
    if (!bAppDataOpen)
    {
        strLastError = "Database connection not open";
        qWarning() << strLastError;
        return false;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Execute SQL query
    //
    //-----------------------------------------------------------------------------------
    QSqlQuery query(dbAutoCost);
    if (!query.exec(buildDetailCostQuery())) {
        queryError = query.lastError();
        strLastError = queryError.text();
        qWarning() << "Query error:" << strLastError;
        return false;
    }
    iDataColums = query.record().count();

    //-----------------------------------------------------------------------------------
    //
    //  Reset table view datamodel
    //
    //-----------------------------------------------------------------------------------
    beginResetModel();
    m_rows.clear();

    //-----------------------------------------------------------------------------------
    //
    //  Build Table view datamodel
    //
    //-----------------------------------------------------------------------------------
    while (query.next())
    {
        QVector<QVariant> row;
        row.reserve(strHeaders.size());

        //-------------------------------------------------------------------------------
        //
        //  Load data from record into temp variables the column calculations
        //
        for (iDataColumnNb = 0; iDataColumnNb < iDataColums; iDataColumnNb++)
        {
            switch (iDataColumnNb)
            {
            case DataColAutoCostRecID:
                iAutoCostRecID = query.value(iDataColumnNb).toInt();
                break;
            case DataColAutoCostRecType:
                iAutoCostType = query.value(iDataColumnNb).toInt();
                break;
            case DataColAutoCostDate:
                dtAutoCoatDate = query.value(iDataColumnNb).toDate();
                break;
            case DataColAutoCostDescription:
                strAutoCostDescription = query.value(iDataColumnNb).toString();
                break;
            case DataColAutoCostFrequency:
                iAutoCostFrequency = query.value(iDataColumnNb).toInt();
                break;
            case DataColAutoCostTotalCost:
                dAutoCostTotalCost = query.value(iDataColumnNb).toDouble();
                break;
            case DataColElectricityRecID:
                iElectricityRecID = query.value(iDataColumnNb).toInt();
                break;
            case DataColElectricityKmTotal:
                dElectricityTotalKM = query.value(iDataColumnNb).toDouble();
                break;
            case DataColElectricityKWhLoaded:
                dElectricityKWhLoaded = query.value(iDataColumnNb).toDouble();
                break;
            case DataColElectricityCapBattteryStart:
                dElectricityAccuStart = query.value(iDataColumnNb).toDouble();
                break;
            case DataColElectricityCapBatteryEnd:
                dElectricityAccuEnd = query.value(iDataColumnNb).toDouble();
                break;
            case DataColElectricityStartTime:
                if (iAutoCostType == CostRecElectricity)
                {
                    tmElectricityStartTime = query.value(iDataColumnNb).toTime();
                }
                break;
            default:
                break;
            }
        }

        //-------------------------------------------------------------------------------
        //
        //  Calculate the totals
        //
        //-------------------------------------------------------------------------------
        CostTotals();

        //-------------------------------------------------------------------------------
        //
        //  Calculate values of electricity records
        //
        //-------------------------------------------------------------------------------
        if (iAutoCostType == CostRecElectricity)
        {
            CostElectricityFieldCalc();
        }

        //-------------------------------------------------------------------------------
        //
        //  Write values to detailcost table view
        //
        for (iViewColumn = 0; iViewColumn < strHeaders.size(); ++iViewColumn)
        {
            switch (iViewColumn)
            {
            case CostOverViewDate:
                strValue = dtAutoCoatDate.toString("dd-MM-yyyy");
                break;
            case CostOverViewDescription:
                strValue = strAutoCostDescription;
                break;
            case CostOverViewPeriodic:
                strValue = CostPeriodic();
                break;
            case CostOverViewElectricity:
                strValue = CostElectricity();
                break;
            case CostOverViewOther:
                strValue = CostOther();
                break;
            case CostOverViewAccessory:
                strValue = CostAccessory();
                break;
            case CostOverViewMillage:
                strValue = CostMillage();
                break;
            case CostOverViewMillageTrip:
                strValue = CostMillageTrip();
                break;
            case CostOverViewKWhTrip:
                strValue = CostTripKwhUsed();
                break;
            case CostOverViewKWhLoaded:
                strValue = CostKWhLoaded();
                break;
             case CostOverViewKWhperKM:
                strValue = CostKWhPerKM();
                break;
            case CostOverViewAvgEuroPerKWh:
                 strValue = CostEuroPerKWh();
                 break;
            case CostOverViewKWhPerPercentage:
                strValue = CostKWhPerPercentage();
                break;
            case CostOverViewKMPerPercentage:
                strValue = CostKMperPercentage();
                break;
             case CostOverViewAccuStartPercentage:
                strValue = CostAccuStart();
                break;
             case CostOverViewAccuEndPercentage:
                strValue = CostAccuEnd();
                break;
            case CostOverViewAccuUsagePercentage:
                 strValue = CostAccuUsedPercentage();
                break;
            case CostOverViewAccuLoadDeltaPercentage:
                strValue = CostAccuLoadDelta();
                break;
            case CostOverViewLoadStartTime:
                strValue = CostLoadStartTime();
                break;
            case CostOverViewRecID:
                strValue = QString::number(iAutoCostRecID);
                break;
            case CostOverViewElecRecId:
                strValue = CostElectricityRecId();
                break;
            case CostOverViewRecType:
                strValue = QString::number(iAutoCostType);
                break;
            case CostOverViewPeriod:
                strValue = QString::number(iAutoCostFrequency);
                break;
            default:
                strValue = "";
                break;
            }
            row.append(strValue);
            strValue = "";
        }

        m_rows.append(row);
    }

    endResetModel();

    strLastError.clear();
    return true;
}

//---------------------------------------------------------------------------------------
//
//  columnCount
//
//---------------------------------------------------------------------------------------
int DetailCostDataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return strHeaders.size();
}

//---------------------------------------------------------------------------------------
//
//  rowCount
//
//---------------------------------------------------------------------------------------
int DetailCostDataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_rows.size();
}

//---------------------------------------------------------------------------------------
//
//  data
//
//---------------------------------------------------------------------------------------
QVariant DetailCostDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set the field alignment of the columns
    //
    //-----------------------------------------------------------------------------------
    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column())
        {
            case CostOverViewDate: return Qt::AlignHCenter;
            case CostOverViewDescription: return Qt::AlignLeft;
            case CostOverViewLoadStartTime: return Qt::AlignHCenter;
            default:
                return Qt::AlignRight;
        }
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    const int row = index.row();
    const int col = index.column();

    if (row < 0 || row >= m_rows.size()) {
        return QVariant();
    }

    if (col < 0 || col >= strHeaders.size()) {
        return QVariant();
    }

    return m_rows.at(row).at(col);
}

//---------------------------------------------------------------------------------------
//
//  headerData
//
//---------------------------------------------------------------------------------------
QVariant DetailCostDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < strHeaders.size()) {
            return strHeaders.at(section);
        }
        return QVariant();
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

//---------------------------------------------------------------------------------------
//
//  getBAppDataOpen
//
//---------------------------------------------------------------------------------------
bool DetailCostDataModel::getBAppDataOpen() const
{
    return bAppDataOpen;
}

//---------------------------------------------------------------------------------------
//
//  getLastError
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::getLastError() const
{
    return strLastError;
}

//---------------------------------------------------------------------------------------
//
//  CostAccessory
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostAccessory()
{
QString
        strAccessoryCost = "";

    if (iAutoCostType == CostRecAccessory)
    {
        strAccessoryCost = QString::number(dAutoCostTotalCost, 'f', 2);
    }
    return strAccessoryCost;
}

//---------------------------------------------------------------------------------------
//
//  CostAccuEnd
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostAccuEnd()
{
    QString
        strElectricityAccuEnd = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strElectricityAccuEnd = QString::number(dElectricityAccuEnd, 'f', 0);
    }
    return strElectricityAccuEnd;
}
//---------------------------------------------------------------------------------------
//
//  CostAccuLoadDelta
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostAccuLoadDelta()
{
    QString
        strAccuLoadDelta = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strAccuLoadDelta = QString::number(dElectricitySessionLoadPercentage, 'f', 0);
    }
    return strAccuLoadDelta;
}

//---------------------------------------------------------------------------------------
//
//  CostAccuStart
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostAccuStart()
{
    QString
        strElectricityAccuStart = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strElectricityAccuStart = QString::number(dElectricityAccuStart, 'f', 0);
    }
    return strElectricityAccuStart;
}

//---------------------------------------------------------------------------------------
//
//  CostAccuUsedPercentage
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostAccuUsedPercentage()
{

    QString
        strElectricityAccuUsedPercentage = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strElectricityAccuUsedPercentage = QString::number(dElectrcityAccuUsedPercentage, 'f', 0);
    }
    return strElectricityAccuUsedPercentage;
}

//---------------------------------------------------------------------------------------
//
//  CostElectricity
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostElectricity()
{
    QString
        strElectricityCost = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strElectricityCost = QString::number(dAutoCostTotalCost, 'f', 2);
    }
    return strElectricityCost;
}

//---------------------------------------------------------------------------------------
//
//  CostElectricityFieldCalc
//
//  Method that calculates the fiels of the electricity field before the
//  detailcost table is filled
//
//---------------------------------------------------------------------------------------
void DetailCostDataModel::CostElectricityFieldCalc()
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    static double
        dElectricityAccuEndPrev = 90;

    //-----------------------------------------------------------------------------------
    //
    //  Store year
    //
    iYear = dtAutoCoatDate.year();

    //-----------------------------------------------------------------------------------
    //
    //  Calculate the totals
    //
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //
    //  Trip millage
    //
    dElectrictyTripKM = dElectricityTotalKM - dElectricityTotalKMPrev;

    //-----------------------------------------------------------------------------------
    //
    //  Percentage accu load session
    //
    dElectricitySessionLoadPercentage = dElectricityAccuEnd - dElectricityAccuStart;

    //-----------------------------------------------------------------------------------
    //
    //  Percentage accu usage of trip
    //
    dElectrcityAccuUsedPercentage = dElectricityAccuEndPrev - dElectricityAccuStart;

    //-----------------------------------------------------------------------------------
    //
    //  KWh used during trip
    //
    dElectirictyTripUsage = (dElectricityKWhLoaded *
                            ((dElectricityAccuEndPrev - dElectricityAccuStart)/
                            (dElectricityAccuEnd - dElectricityAccuStart)));

    //-----------------------------------------------------------------------------------
    //
    //  KWh/km
    //
    dElectricityKWhperKM = dElectirictyTripUsage / dElectrictyTripKM;

    //-----------------------------------------------------------------------------------
    //
    //  Euro/KWh
    //
    dElectricityEuroPerKWh = dAutoCostTotalCost / dElectricityKWhLoaded;

    //-----------------------------------------------------------------------------------
    //
    //  KWh per percentage loaded
    //
    dElectricityKWhperPercentage = dElectricityKWhLoaded /
                                   dElectricitySessionLoadPercentage;

    //-----------------------------------------------------------------------------------
    //
    //  KM per percentage loaded
    //
    dElectricityKMperPercentage = dElectrictyTripKM / dElectricitySessionLoadPercentage;

    //-----------------------------------------------------------------------------------
    //
    //  Save values that are basis for the next run
    //
    dElectricityTotalKMPrev = dElectricityTotalKM;
    dElectricityAccuEndPrev = dElectricityAccuEnd;

}

//---------------------------------------------------------------------------------------
//
//  CostElectricity
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostElectricityRecId()
{
    QString
        strElectricityCostRecID = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strElectricityCostRecID = QString::number(iElectricityRecID);
    }
    return strElectricityCostRecID;
}

//---------------------------------------------------------------------------------------
//
//  CostEuroPerKWh
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostEuroPerKWh()
{
    QString
        strEuroPerKWh = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strEuroPerKWh = QString::number(dElectricityEuroPerKWh, 'f', 3);
    }
    return strEuroPerKWh;
}

//---------------------------------------------------------------------------------------
//
//  CostKMperPercentage
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostKMperPercentage()
{
    QString
        strKMperPercentage = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strKMperPercentage = QString::number(dElectricityKMperPercentage, 'f', 4);
    }
    return strKMperPercentage;
}
//---------------------------------------------------------------------------------------
//
//  CostKWhLoaded
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostKWhLoaded()
{
    QString
        strKWhLoaded = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strKWhLoaded = QString::number(dElectricityKWhLoaded, 'f', 2);
    }
    return strKWhLoaded;
}

//---------------------------------------------------------------------------------------
//
//  CostKWhPerKM
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostKWhPerKM()
{
    QString
        strKWhPerKM = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strKWhPerKM = QString::number(dElectricityKWhperKM, 'f', 3);
    }
    return strKWhPerKM;
}

//---------------------------------------------------------------------------------------
//
//  CostKWhPerPercentage
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostKWhPerPercentage()
{
    QString
        strKWhperPercentage = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strKWhperPercentage = QString::number(dElectricityKWhperPercentage, 'f', 4);
    }
    return strKWhperPercentage;
}

//---------------------------------------------------------------------------------------
//
//  CostLoadStartTime
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostLoadStartTime()
{
    QString
        strLoadStartTime = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strLoadStartTime = tmElectricityStartTime.toString("HH:mm");
    }
    return strLoadStartTime;
}

//---------------------------------------------------------------------------------------
//
//  CostMillage
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostMillage()
{
    QString
        strMillage = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strMillage = QString::number(dElectricityTotalKM, 'f', 0);
    }
    return strMillage;
}

//---------------------------------------------------------------------------------------
//
//  CostMillageTrip
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostMillageTrip()
{
    QString
        strMillageTrip = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strMillageTrip = QString::number(dElectrictyTripKM, 'f', 0);
    }
    return strMillageTrip;
}

//---------------------------------------------------------------------------------------
//
//  CostOther
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostOther()
{
    QString
        strOtherCost = "";

    if (iAutoCostType == CostRecOther)
    {
        strOtherCost = QString::number(dAutoCostTotalCost, 'f', 2);
    }
    return strOtherCost;
}

//---------------------------------------------------------------------------------------
//
//  CostPeriodic
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostPeriodic()
{
    QString
        strPeriodicCost = "";

    if (iAutoCostType == CostRecPeriodic)
    {
        strPeriodicCost = QString::number(dAutoCostTotalCost, 'f', 2);
    }
    return strPeriodicCost;
}

//---------------------------------------------------------------------------------------
//
//  CostTotals
//
//---------------------------------------------------------------------------------------
void DetailCostDataModel::CostTotals()
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    int iYearOfRecord = 0;

    //-----------------------------------------------------------------------------------
    //
    //  Init vectors containing the totals
    //  Set of set of each vector:
    //      - the first (total of totals) to 0
    //
    if (dTotalCost.size()==0)
    {
        iYears.append(0);
        dTotalCost.append(0);
        dTotalPeriodic.append(0);
        dTotalElectricity.append(0);
        dTotalOtherCost.append(0);
        dTotalAccessory.append(0);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Get year of record
    //  Append a item to each total vector and set it to 0
    //
    iYearOfRecord = dtAutoCoatDate.year();
    if (iYear != iYearOfRecord)
    {
        iYear = iYearOfRecord;
        iYears.append(iYearOfRecord);
        iYearCurrentRow++;
        dTotalCost.append(0);
        dTotalPeriodic.append(0);
        dTotalElectricity.append(0);
        dTotalOtherCost.append(0);
        dTotalAccessory.append(0);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Calculate the totals overall
    //
    dTotalCost[0] += dAutoCostTotalCost;
    dTotalCost[iYearCurrentRow] += dAutoCostTotalCost;
    if (iAutoCostType == CostRecPeriodic)
    {
        dTotalPeriodic[0] += dAutoCostTotalCost;
        dTotalPeriodic[iYearCurrentRow] += dAutoCostTotalCost;
    }
    else if (iAutoCostType == CostRecElectricity)
    {
        dTotalElectricity[0] += dAutoCostTotalCost;
        dTotalElectricity[iYearCurrentRow] += dAutoCostTotalCost;
    }
    else if (iAutoCostType == CostRecOther)
    {
        dTotalOtherCost[0] += dAutoCostTotalCost;
        dTotalOtherCost[iYearCurrentRow] += dAutoCostTotalCost;
    }
    else if (iAutoCostType == CostRecAccessory)
    {
        dTotalAccessory[0] += dAutoCostTotalCost;
        dTotalAccessory[iYearCurrentRow] += dAutoCostTotalCost;
    }

}

//---------------------------------------------------------------------------------------
//
//  CostTripKwhUsed
//
//---------------------------------------------------------------------------------------
QString DetailCostDataModel::CostTripKwhUsed()
{
    QString
        strTripKWhUsed = "";

    if (iAutoCostType == CostRecElectricity)
    {
        strTripKWhUsed = QString::number(dElectirictyTripUsage, 'f', 3);
    }
    return strTripKWhUsed;
}
