//---------------------------------------------------------------------------------------
//
//  Module: millageoverviewdatamodel.h
//
//  Class MillageOverviewDataModel manages the millage overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef MILLAGEOVERVIEWDATAMODEL_H
#define MILLAGEOVERVIEWDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostdatamodel.h"
#include "tabledatamodel.h"
#include <QObject>
#include <QVector>

class MillageOverviewDataModel : public TableDataModel
{
    Q_OBJECT
public:
    MillageOverviewDataModel(QObject *parent = nullptr);

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    void loadMillageData(const DetailCostDataModel &detailModel);

protected:
    //-----------------------------------------------------------------------------------
    //
    //  Subclasses override to customise alignment (default: right aligned)
    //
    virtual Qt::Alignment columnAlignment(int column) const;

private:
    double dMillageCurrent = -1;

    QVector<double>
        dMillageYearEnd,
        dMillageYearRemaining,
        dMillageYearStart,
        dMillageYearUsed;

    QVector<int> years;

};

#endif // MILLAGEOVERVIEWDATAMODEL_H
