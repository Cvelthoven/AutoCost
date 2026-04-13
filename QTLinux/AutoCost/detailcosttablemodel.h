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
#include <QTableView>
#include <QObject>
#include <QString>

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
    ~DetailCostTableModel();

    //-----------------------------------------------------------------------------------
    //
    //  Default methodes used by TableView
    //
    //-----------------------------------------------------------------------------------
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private methodes
    //
    //-----------------------------------------------------------------------------------
    void ConvertSqlrecordToTableViewRow(int iRowNumber);

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
    DetailCostSqlModel *DetailedCostSqlTable;

    QString
        strRecID = "",
        strRecType = "",
        strRecDate = "",
        strRecDescription = "",
        strRecPeriodic ="",
        strRecElectricity = "",
        strRecOther = "",
        strRecAccessory = "",
        strRecMillage = "",
        strRecMillageTrip = "",
        strRecKWhTrip = "",
        strRecKWhLoaded = "",
        strRecCostKWhPerKm = "",
        strRecCostKWhperKM = "",
        strRecAvgEuroPerKWh = "",
        strKWhPercentage = "",
        strKmPerPercentage = "",
        strAccuStartPercentage = "",
        strAccuEndPercentage = "",
        strAccuLoadDeltaPercentange = "",
        strPeriod = "";

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
