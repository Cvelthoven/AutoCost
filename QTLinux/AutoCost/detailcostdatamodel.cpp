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
    qDebug() << "Constructor DetailCostDataModel called";

    //-----------------------------------------------------------------------------------
    //
    //  Reuse open Application database connection
    //
    dbAutoCost = QSqlDatabase::database(strApplicationDatabaseConnectionName, false);
    if ((dbAutoCost.isValid()) && (dbAutoCost.isOpen())) {
        bAppDataOpen = true;
    } else {
        bAppDataOpen = false;
    }

    strHeaders = {
        "ID",
        "Type",
        "Date",
        "Description",
        "Periodic",
        "Electricity",
        "Other",
        "Accessories",
        "Frequency",
        "Elec ID",
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
        "Load Delta",
        "Start Time"
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
                break;
            case DataColAutoCostDate:
                break;
            case DataColAutoCostDescription:
                break;
            case DataColAutoCostRecType:
                break;
            case DataColAutoCostFrequency:
                break;
            case DataColAutoCostTotalCost:
                break;
            case DataColElectricityRecID:
                break;
            case DataColElectricityKmTotal:
                break;
            case DataColElectricityKWhLoaded:
                break;
            case DataColElectricityCapBattteryStart:
                break;
            case DataColElectricityCapBatteryEnd:
                break;
            case DataColElectricityStartTime:
                break;
            default:
                break;
            }

        }

        for (iViewColumn = 0; iViewColumn < strHeaders.size(); ++iViewColumn)
        {
            switch (iDataColumnNb)
            {
            case DataColAutoCostRecID:
                iViewColumn = CostOverViewRecID;
                break;
            case DataColAutoCostRecType:
                iViewColumn = CostOverViewRecType;
                break;
            case DataColAutoCostDate:
                iViewColumn = CostOverViewDate;
                break;
            case DataColAutoCostDescription:
                iViewColumn = CostOverViewDescription;
                break;
            }
            row.append(query.value(iDataColumnNb));
            iDataColumnNb++;
        }

        m_rows.append(row);
        iDataColumnNb = 0;
    }

    endResetModel();

    strLastError.clear();
    qDebug() << "Loaded" << m_rows.size() << "records";
    return true;
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
//  data
//
//---------------------------------------------------------------------------------------
QVariant DetailCostDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
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
