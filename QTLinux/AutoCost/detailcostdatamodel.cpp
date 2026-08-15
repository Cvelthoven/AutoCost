//---------------------------------------------------------------------------------------
//
//  Module: detailcostdatamodel.cpp
//
//  This class manages the detail cost data
//  The class DetailCostDataView manages the presentation of the detailed cost data
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

    m_headers = {
        "ID",
        "Type",
        "Date",
        "Description",
        "Total Cost",
        "Frequency",
        "Elec ID",
        "Km Total",
        "KWh Loaded",
        "Battery Start",
        "Battery End",
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
    if (!bAppDataOpen) {
        strLastError = "Database connection not open";
        qWarning() << strLastError;
        return false;
    }

    QSqlQuery query(dbAutoCost);
    if (!query.exec(buildDetailCostQuery())) {
        queryError = query.lastError();
        strLastError = queryError.text();
        qWarning() << "Query error:" << strLastError;
        return false;
    }

    beginResetModel();
    m_rows.clear();

    while (query.next()) {
        QVector<QVariant> row;
        row.reserve(m_headers.size());

        for (int col = 0; col < m_headers.size(); ++col) {
            row.append(query.value(col));
        }

        m_rows.append(row);
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

    return m_headers.size();
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

    if (col < 0 || col >= m_headers.size()) {
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
        if (section >= 0 && section < m_headers.size()) {
            return m_headers.at(section);
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
