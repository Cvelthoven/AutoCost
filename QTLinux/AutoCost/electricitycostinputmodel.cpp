//---------------------------------------------------------------------------------------
//
//  Module: electricitycostinputmodel.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "electricitycostinputmodel.h"
#include "tabledatamodel.h"

#include <QObject>
#include <QTime>

//---------------------------------------------------------------------------------------
//
//  Class ElectricityCostInputModel constructors and destructors
//
//---------------------------------------------------------------------------------------
ElectricityCostInputModel::ElectricityCostInputModel(QObject *parent)
    : TableDataModel(parent),
    vPrice(iSlotsPerDay),
    vKWh(iSlotsPerDay)
{
    strHeaders =
    {
        "Hour",
        "00:00",
        "KWh",
        "00.15",
        "KWh",
        "00:30",
        "KWh",
        "00:45",
        "KWh"
    };
}

//---------------------------------------------------------------------------------------
//
//  Class ElectricityCostInputModel methods
//
//---------------------------------------------------------------------------------------
//
//  columnAlignment
//
//---------------------------------------------------------------------------------------
Qt::Alignment ElectricityCostInputModel::columnAlignment(int c) const
{
    return c == ElectricityCostInputHour00 ? Qt::AlignHCenter : Qt::AlignRight;
}

//---------------------------------------------------------------------------------------
//
//  flags
//
//---------------------------------------------------------------------------------------
Qt::ItemFlags ElectricityCostInputModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    Qt::ItemFlags f = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.column() != ElectricityCostInputHour00 && dDay.isValid())
        f |= Qt::ItemIsEditable;
    return f;
}

//---------------------------------------------------------------------------------------
//
//  loadDataDefault
//
//  Fill the electricity cost table with the default values:
//  - default KWh per 15 minutes, sufficient fields to accomodated the complete session
//  - set euro/Kwh to 0.00
//  - create enough rows for each expected hour of the load session
//  - set the hour at the beginning of each row
//
//---------------------------------------------------------------------------------------
bool ElectricityCostInputModel::loadDataDefault()
{
    beginResetModel();
    vPrice = QVector<QVariant>(iSlotsPerDay);
    vKWh = QVector<QVariant>(iSlotsPerDay);

    endResetModel();
    return true;
}

//-------------- Old code remove -----------------
// int ElectricityCostInputModel::rowCount(const QModelIndex &parent) const
// {
//     return parent.isValid() ? 0 : iSlotsPerDay;
// }

// int ElectricityCostInputModel::columnCount(const QModelIndex &parent) const
// {
//     return parent.isValid() ? 0 : ElectricityCostInputNbColumns;
// }

// QVariant ElectricityCostInputModel::data(const QModelIndex &index, int role) const
// {
//     if (!index.isValid() || index.row() >= iSlotsPerDay)
//         return QVariant();

//     if (role == Qt::TextAlignmentRole)
//         return int(index.column() == ElectricityCostInputTime ? Qt::AlignCenter
//                                                               : Qt::AlignRight | Qt::AlignVCenter);

//     if (role != Qt::DisplayRole && role != Qt::EditRole)
//         return QVariant();

//     const int r = index.row();
//     switch (index.column())
//     {
//     case ElectricityCostInputTime:
//     {
//         const QTime start = QTime(0, 0).addSecs(r * iSlotMinutes * 60);
//         return start.toString("hh:mm") + " - " +
//                start.addSecs(iSlotMinutes * 60).toString("hh:mm");
//     }
//     case ElectricityCostInputPrice:
//         if (vPrice[r].isNull()) return QVariant();
//         return role == Qt::EditRole ? vPrice[r]
//                                     : QVariant(QString::number(vPrice[r].toDouble(), 'f', 4));
//     case ElectricityCostInputKWh:
//         if (vKWh[r].isNull()) return QVariant();
//         return role == Qt::EditRole ? vKWh[r]
//                                     : QVariant(QString::number(vKWh[r].toDouble(), 'f', 3));
//     }
//     return QVariant();
// }

// bool ElectricityCostInputModel::setData(const QModelIndex &index, const QVariant &value, int role)
// {
//     if (role != Qt::EditRole || !index.isValid() || !dDay.isValid() ||
//         index.row() < 0 || index.row() >= iSlotsPerDay ||
//         index.column() <= ElectricityCostInputTime ||
//         index.column() >= ElectricityCostInputNbColumns)
//         return false;

//     QVariant newValue;
//     const QString strValue = value.toString().trimmed().replace(',', '.');
//     if (!strValue.isEmpty())
//     {
//         bool bOk = false;
//         const double dValue = strValue.toDouble(&bOk);
//         if (!bOk || dValue < 0.0)
//             return false;
//         newValue = dValue;
//     }

//     QVector<QVariant> &target = (index.column() == ElectricityCostInputPrice) ? vPrice : vKWh;
//     target[index.row()] = newValue;
//     emit dataChanged(index, index);
//     return true;
// }

// QVariant ElectricityCostInputModel::headerData(int section, Qt::Orientation orientation, int role) const
// {
//     if (role != Qt::DisplayRole)
//         return QVariant();
//     if (orientation == Qt::Vertical)
//         return section + 1;

//     switch (section)
//     {
//     case ElectricityCostInputTime:  return "Time (15 min)";
//     case ElectricityCostInputPrice: return "Price/KWh";
//     case ElectricityCostInputKWh:   return "KWh loaded";
//     }
//     return QVariant();
// }
