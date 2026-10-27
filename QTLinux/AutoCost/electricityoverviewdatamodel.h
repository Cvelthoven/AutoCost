//---------------------------------------------------------------------------------------
//
//  Module: electricityoverviewdatamodel.h
//
//  Class ElectricityOverviewDataModel manages the millage overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef ELECTRICITYOVERVIEWDATAMODEL_H
#define ELECTRICITYOVERVIEWDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostdatamodel.h"
#include "tabledatamodel.h"
#include <QObject>
#include <QString>
#include <QVector>

class ElectricityOverviewDataModel : public TableDataModel
{
    Q_OBJECT
public:
    ElectricityOverviewDataModel(QObject *parent = nullptr);

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    bool loadElectricityData(const DetailCostDataModel &detailModel);

protected:
    //-----------------------------------------------------------------------------------
    //
    //  Subclasses override to customise alignment (default: right aligned)
    //
    virtual Qt::Alignment columnAlignment(int column) const;

private:
    QVector<double>
        dTotalElectricity,
        dMillageYearEnd,
        dMillageYearStart,
        dTotalKWh;

    QVector<int>
        years;

};

#endif // ELECTRICITYOVERVIEWDATAMODEL_H
