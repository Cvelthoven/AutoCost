#include "tabledatamodel.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  Default TableDataModel constructor
TableDataModel::TableDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

//---------------------------------------------------------------------------------------
//
//  TableDataModel class methods
//
//---------------------------------------------------------------------------------------
//
//  columnCount
//
//---------------------------------------------------------------------------------------
int TableDataModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : strHeaders.size();
}

//---------------------------------------------------------------------------------------
//
//  rowCount
//
//---------------------------------------------------------------------------------------
int TableDataModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_rows.size();
}

//---------------------------------------------------------------------------------------
//
//  columnAlignment
//
//---------------------------------------------------------------------------------------
Qt::Alignment TableDataModel::columnAlignment(int) const
{
    return Qt::AlignRight;
}

//---------------------------------------------------------------------------------------
//
//  data
//
//---------------------------------------------------------------------------------------
QVariant TableDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (role == Qt::TextAlignmentRole) return QVariant(int(columnAlignment(index.column())));
    if (role != Qt::DisplayRole) return QVariant();

    const int row = index.row(), col = index.column();
    if (row < 0 || row >= m_rows.size()) return QVariant();
    if (col < 0 || col >= strHeaders.size()) return QVariant();
    return m_rows.at(row).at(col);
}

//---------------------------------------------------------------------------------------
//
//  headerData
//
//---------------------------------------------------------------------------------------
QVariant TableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < strHeaders.size()) return strHeaders.at(section);
        return QVariant();
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}
