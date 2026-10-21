//---------------------------------------------------------------------------------------
//
//  Module: totalcostdatamodel.h
//
//  This class manages the total cost data
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef TOTALCOSTDATAMODEL_H
#define TOTALCOSTDATAMODEL_H

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

class TotalCostDataModel : public TableDataModel
{
    Q_OBJECT
public:
    TotalCostDataModel(QObject *parent = nullptr);

    void loadTotals(const DetailCostDataModel &detailModel);

protected:
    Qt::Alignment columnAlignment(int column) const override;

private:
    QVector<int> years;

    QVector<double> accessory;
    QVector<double> electricity;
    QVector<double> MillageYearStart;
    QVector<double> other;
    QVector<double> periodic;
    QVector<double> totalCost;

};

#endif // TOTALCOSTDATAMODEL_H
