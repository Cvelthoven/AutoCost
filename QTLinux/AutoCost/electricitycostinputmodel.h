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
#include "tabledatamodel.h"

#include <QDate>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  Class DataInputDialog enumerations
//
//---------------------------------------------------------------------------------------
enum ElectricityCostInputColumns
{
    ElectricityCostInputHour = 0,
    ElectricityCostInputHour00,
    ElectricityCostInputKWh00,
    ElectricityCostInputHour15,
    ElectricityCostInputKWh15,
    ElectricityCostInputHour30,
    ElectricityCostInputKWh30,
    ElectricityCostInputHour45,
    ElectricityCostInputKWh45
};

//---------------------------------------------------------------------------------------
//
//  Class DataInputDialog definitions
//
//---------------------------------------------------------------------------------------
class ElectricityCostInputModel : public TableDataModel
{
    Q_OBJECT
public:
    static constexpr int iSlotMinutes = 15;
    static constexpr int iSlotsPerDay = 24 * 60 / iSlotMinutes;

    explicit ElectricityCostInputModel(QObject *parent = nullptr);

    // int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // bool setData(const QModelIndex &index, const QVariant &value,
    //              int role = Qt::EditRole) override;
    // QVariant headerData(int section, Qt::Orientation orientation,
    //                     int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //  Initializes the 96 in-memory slots for the given day
    bool loadDay();
//    QDate day() const { return dDay; }

protected:
    //-----------------------------------------------------------------------------------
    //
    //  Subclasses override to customise alignment (default: right aligned)
    //
    virtual Qt::Alignment columnAlignment(int column) const override;

private:
    QDate dDay;
    QVector<QVariant> vPrice;   // null = not entered
    QVector<QVariant> vKWh;
};

#endif // ELECTRICITYCOSTINPUTMODEL_H
