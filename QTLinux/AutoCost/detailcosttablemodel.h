//---------------------------------------------------------------------------------------
//
//  Module: DetailCostTableModel.h
//
//  This class prepares the data from detailcostsqlmodel to be displayed.
//  All reformating and filling the calculated columns are part of this class
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTTABLEMODEL_H
#define DETAILCOSTTABLEMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostsqlmodel.h"

#include <QAbstractTableModel>
#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostTableModel definitions
//
//---------------------------------------------------------------------------------------
class DetailCostTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DetailCostTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    DetailCostSqlModel *DetailedCostSqlTable;

    //-----------------------------------------------------------------------------------
    //
    //  Enums for Cost overview dialog columns with descriptive names
    //
    enum CostOverViewCol
    {
        CostOverViewRecID = 0,
        CostOverViewRecType,
        CostOverViewDate,
        CostOverViewDescription,
        CostOverViewPeriodic,
        CostOverViewElectricity,
        CostOverViewOther,
        CostOverViewAccessory,
        CostOverViewMillage,
        CostOverViewMillageTrip,
        CostOverViewKWhTrip,
        CostOverViewKWhLoaded,
        CostOverViewCostKWhperKM,
        CostOverViewAvgEuroPerKWh,
        CostOverViewKWhPerPercentage,
        CostOverViewKMPerPercentage,
        CostOverViewAccuStartPercentage,
        CostOverViewAccuEndPercentage,
        CostOverViewAccuUsagePercentage,
        CostOverViewAccuLoadDeltaPercentage,
        CostOverViewPeriod

    };

};

#endif // DETAILCOSTTABLEMODEL_H
