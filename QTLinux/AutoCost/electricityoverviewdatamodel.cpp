//---------------------------------------------------------------------------------------
//
//  Module: electricityoverviewdatamodel.cpp
//
//  Class ElectricityOverviewDataModel manages the electricity overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "electricityoverviewdatamodel.h"

#include <QAbstractTableModel>
#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Class ElectricityOverviewDataModel constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  Default constructor and destructor
//
//---------------------------------------------------------------------------------------
ElectricityOverviewDataModel::ElectricityOverviewDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    //-----------------------------------------------------------------------------------
    //
    //  Set column headers
    //
    strHeaders = {
        "Year",
        "Start",
        "End/Last",
        "Limit",
        "Used",
        "Rest"
    };

}

//---------------------------------------------------------------------------------------
//
//  MillageOverview class methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  columnCount
//
//---------------------------------------------------------------------------------------
int ElectricityOverviewDataModel::columnCount(const QModelIndex &parent) const
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
QVariant ElectricityOverviewDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set the field alignment of the columns
    //
    // if (role == Qt::TextAlignmentRole)
    // {
    //     switch (index.column())
    //     {
    //     case MillageOverviewYear:
    //         return Qt::AlignCenter;
    //         break;
    //     default:
    //         return Qt::AlignRight;
    //     }
    // }

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
QVariant ElectricityOverviewDataModel::headerData(int section, Qt::Orientation orientation, int role) const
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
//  rowCount
//
//---------------------------------------------------------------------------------------
int ElectricityOverviewDataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_rows.size();
}