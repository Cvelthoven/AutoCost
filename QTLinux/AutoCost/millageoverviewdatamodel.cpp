//---------------------------------------------------------------------------------------
//
//  Module: millageoverviewdatamodel.cpp
//
//  Class MillageOverviewDataModel manages the millage overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "millageoverviewdatamodel.h"

#include <QAbstractTableModel>
#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Class MillageOverview constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  Default constructor and destructor
//
//---------------------------------------------------------------------------------------
MillageOverviewDataModel::MillageOverviewDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    //-----------------------------------------------------------------------------------
    //
    //  Set column headers
    //
    strHeaders = {
        "Year",
        "Start",
        "Current",
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
int MillageOverviewDataModel::columnCount(const QModelIndex &parent) const
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
QVariant MillageOverviewDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set the field alignment of the columns
    //
    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column())
        {
        case MillageOverviewYear:
            return Qt::AlignCenter;
            break;
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
QVariant MillageOverviewDataModel::headerData(int section, Qt::Orientation orientation, int role) const
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
//  loadMillageData
//
//---------------------------------------------------------------------------------------
bool MillageOverviewDataModel::loadMillageData(const DetailCostDataModel &detailModel)
{
    int iRowNb =0,
        iColNb = 0,
        iTotalRows = 0,
        iTotalCol = 0;

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve data from the detail cost data
    //
    dMillageYearStart = detailModel.getDMillageYearStart();
    dMillageCurrent = detailModel.getMillageCurrent();
    years = detailModel.getYears();

    //-----------------------------------------------------------------------------------
    //
    //  Calculate remaining values
    //

    //-----------------------------------------------------------------------------------
    //
    //  Reset table view datamodel
    //
    iTotalRows = years.size();
    iTotalCol = strHeaders.size();
    beginResetModel();
    m_rows.clear();

    //-----------------------------------------------------------------------------------
    //
    //  Build table view datamodel
    //
    for (iRowNb = 0; iRowNb < iTotalRows; iRowNb++)
    {
        QVector<QVariant> millageRow;
        millageRow.reserve(iTotalCol);
        for (iColNb = 0; iColNb < iTotalCol; iColNb++)
        {
            switch (iColNb)
            {
                case MillageOverviewYear:
                    if (iRowNb == 0)
                    {
                        millageRow.append("Total");
                    }
                    else
                    {
                        millageRow.append(QString::number(years.at(iRowNb)));
                    }
                    break;
                case MillageOverviewStart:
                    if (iRowNb == 0)
                    {
                        millageRow.append(QString::number(0));
                    }
                    else
                    {
                        millageRow.append(QString::number(dMillageYearStart.at(iRowNb), 'f', 0));
                    }
                    break;
                case MillageOverviewCurrent:
                    if (iRowNb == 0)
                    {
                        millageRow.append(QString::number(0));
                    }
                    else
                    {
                        millageRow.append(QString::number(dMillageCurrent, 'f', 0));
                    }
                    break;
                case MillageOverviewLimit:
                    if (iRowNb == 0)
                    {
                        millageRow.append(" ");
                    }
                    else
                    {
                        millageRow.append(QString::number(iMaxMillageYear));
                    }
                    break;
                case MillageOverviewUsed:
                    if (iRowNb == 0)
                    {
                        millageRow.append("test");
                    }
                    else
                    {
                        millageRow.append("test");
                    }
                    break;
                case MillageOverviewRemaining:
                    if (iRowNb == 0)
                    {
                        millageRow.append("test");
                    }
                    else
                    {
                        millageRow.append("test");
                    }
                    break;
                default:
                    millageRow.append("Test");
                    break;
            }
        }
        m_rows.append(millageRow);

    }
    endResetModel();

    return true;
}

//---------------------------------------------------------------------------------------
//
//  rowCount
//
//---------------------------------------------------------------------------------------
int MillageOverviewDataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_rows.size();
}