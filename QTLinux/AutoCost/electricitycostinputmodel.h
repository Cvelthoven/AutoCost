//---------------------------------------------------------------------------------------
//
//  Module: electricitycostinputmodel.h
//
//  Class ElectricityCostInputModel manages the electricity price and KWh loaded per
//  15 minutes for one day.
//
//  The default QT class QTableView handles the presentation (tblElectricityCostInput)
//
//---------------------------------------------------------------------------------------
#ifndef ELECTRICITYCOSTINPUTMODEL_H
#define ELECTRICITYCOSTINPUTMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QVector>

enum ElectricityCostInputColumns
{
    ElectricityCostInputTime = 0,
    ElectricityCostInputPrice,
    ElectricityCostInputKWh,
    ElectricityCostInputNbColumns
};

class ElectricityCostInputModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    static constexpr int iSlotMinutes = 15;
    static constexpr int iSlotsPerDay = 24 * 60 / iSlotMinutes;

    explicit ElectricityCostInputModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //  Initializes the 96 in-memory slots for the given day
    bool loadDay(const QDate &date);
    QDate day() const { return dDay; }

private:
    // bool ensureTable() const;
    // bool storeSlot(int row);
    // QDateTime slotStart(int row) const;

    QDate dDay;
    QVector<QVariant> vPrice;   // null = not entered
    QVector<QVariant> vKWh;
};

#endif // ELECTRICITYCOSTINPUTMODEL_H
