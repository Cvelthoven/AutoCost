//---------------------------------------------------------------------------------------
//
//  Module: electricitycostinputmodel.cpp
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "electricitycostinputmodel.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTime>

#include <QDebug>

ElectricityCostInputModel::ElectricityCostInputModel(QObject *parent)
    : QAbstractTableModel(parent),
    vPrice(iSlotsPerDay),
    vKWh(iSlotsPerDay)
{
}

int ElectricityCostInputModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : iSlotsPerDay;
}

int ElectricityCostInputModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : ElectricityCostInputNbColumns;
}

QDateTime ElectricityCostInputModel::slotStart(int row) const
{
    return QDateTime(dDay, QTime(0, 0).addSecs(row * iSlotMinutes * 60));
}

QVariant ElectricityCostInputModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= iSlotsPerDay)
        return QVariant();

    if (role == Qt::TextAlignmentRole)
        return int(index.column() == ElectricityCostInputTime ? Qt::AlignCenter
                                                              : Qt::AlignRight | Qt::AlignVCenter);

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    const int r = index.row();
    switch (index.column())
    {
    case ElectricityCostInputTime:
    {
        const QTime start = QTime(0, 0).addSecs(r * iSlotMinutes * 60);
        return start.toString("hh:mm") + " - " +
               start.addSecs(iSlotMinutes * 60).toString("hh:mm");
    }
    case ElectricityCostInputPrice:
        if (vPrice[r].isNull()) return QVariant();
        return role == Qt::EditRole ? vPrice[r]
                                    : QVariant(QString::number(vPrice[r].toDouble(), 'f', 4));
    case ElectricityCostInputKWh:
        if (vKWh[r].isNull()) return QVariant();
        return role == Qt::EditRole ? vKWh[r]
                                    : QVariant(QString::number(vKWh[r].toDouble(), 'f', 3));
    }
    return QVariant();
}

bool ElectricityCostInputModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid() || !dDay.isValid() ||
        index.column() == ElectricityCostInputTime)
        return false;

    QVariant newValue;
    const QString strValue = value.toString().trimmed().replace(',', '.');
    if (!strValue.isEmpty())
    {
        bool bOk = false;
        const double dValue = strValue.toDouble(&bOk);
        if (!bOk || dValue < 0.0)
            return false;
        newValue = dValue;
    }

    QVector<QVariant> &target = (index.column() == ElectricityCostInputPrice) ? vPrice : vKWh;
    const QVariant oldValue = target[index.row()];
    target[index.row()] = newValue;
    if (!storeSlot(index.row()))
    {
        target[index.row()] = oldValue;
        return false;
    }
    emit dataChanged(index, index);
    return true;
}

QVariant ElectricityCostInputModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Vertical)
        return section + 1;

    switch (section)
    {
    case ElectricityCostInputTime:  return "Time (15 min)";
    case ElectricityCostInputPrice: return "Price/KWh";
    case ElectricityCostInputKWh:   return "KWh loaded";
    }
    return QVariant();
}

Qt::ItemFlags ElectricityCostInputModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    Qt::ItemFlags f = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.column() != ElectricityCostInputTime && dDay.isValid())
        f |= Qt::ItemIsEditable;
    return f;
}

//---------------------------------------------------------------------------------------
//
//  ensureTable: creates the table when it does not exist yet
//
//---------------------------------------------------------------------------------------
bool ElectricityCostInputModel::ensureTable() const
{
    QSqlDatabase db = QSqlDatabase::database(strApplicationDatabaseConnectionName, false);
    if (!db.isValid() || !db.isOpen())
        return false;

    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS public.\"acElectricityCost\" ("
                    "\"SlotStart\" timestamp without time zone NOT NULL, "
                    "\"PricePerKWh\" real, "
                    "\"KWhLoaded\" real, "
                    "CONSTRAINT \"acElectricityCost_pkey\" PRIMARY KEY (\"SlotStart\"))"))
    {
        qDebug() << "Create acElectricityCost failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool ElectricityCostInputModel::loadDay(const QDate &date)
{
    beginResetModel();
    dDay = date;
    vPrice = QVector<QVariant>(iSlotsPerDay);
    vKWh = QVector<QVariant>(iSlotsPerDay);

    bool bOk = ensureTable();
    if (bOk && dDay.isValid())
    {
        QSqlQuery query(QSqlDatabase::database(strApplicationDatabaseConnectionName, false));
        query.prepare("SELECT \"SlotStart\", \"PricePerKWh\", \"KWhLoaded\" "
                      "FROM public.\"acElectricityCost\" "
                      "WHERE \"SlotStart\" >= :from AND \"SlotStart\" < :to");
        query.bindValue(":from", QDateTime(dDay, QTime(0, 0)));
        query.bindValue(":to", QDateTime(dDay.addDays(1), QTime(0, 0)));
        bOk = query.exec();
        while (bOk && query.next())
        {
            const QTime t = query.value(0).toDateTime().time();
            const int row = (t.hour() * 60 + t.minute()) / iSlotMinutes;
            if (row >= 0 && row < iSlotsPerDay)
            {
                vPrice[row] = query.value(1);
                vKWh[row] = query.value(2);
            }
        }
        if (!bOk)
            qDebug() << "Load acElectricityCost failed:" << query.lastError().text();
    }
    endResetModel();
    return bOk;
}

//---------------------------------------------------------------------------------------
//
//  storeSlot: upserts the slot, removes the record when both values are empty
//
//---------------------------------------------------------------------------------------
bool ElectricityCostInputModel::storeSlot(int row)
{
    if (!ensureTable())
        return false;

    QSqlQuery query(QSqlDatabase::database(strApplicationDatabaseConnectionName, false));
    if (vPrice[row].isNull() && vKWh[row].isNull())
    {
        query.prepare("DELETE FROM public.\"acElectricityCost\" WHERE \"SlotStart\" = :slot");
        query.bindValue(":slot", slotStart(row));
    }
    else
    {
        query.prepare("INSERT INTO public.\"acElectricityCost\" "
                      "(\"SlotStart\", \"PricePerKWh\", \"KWhLoaded\") "
                      "VALUES (:slot, :price, :kwh) "
                      "ON CONFLICT (\"SlotStart\") DO UPDATE SET "
                      "\"PricePerKWh\" = EXCLUDED.\"PricePerKWh\", "
                      "\"KWhLoaded\" = EXCLUDED.\"KWhLoaded\"");
        query.bindValue(":slot", slotStart(row));
        query.bindValue(":price", vPrice[row].isNull() ? QVariant(QMetaType(QMetaType::Double))
                                                       : vPrice[row]);
        query.bindValue(":kwh", vKWh[row].isNull() ? QVariant(QMetaType(QMetaType::Double))
                                                   : vKWh[row]);
    }
    if (!query.exec())
    {
        qDebug() << "Store acElectricityCost failed:" << query.lastError().text();
        return false;
    }
    return true;
}
