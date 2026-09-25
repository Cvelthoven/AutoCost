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
#include <QAbstractTableModel>
#include <QObject>
#include <QVector>

class TotalCostDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TotalCostDataModel(QObject *parent = nullptr);

    // QAbstractTableModel overrides
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // Override to provide custom headers
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void loadTotals(const DetailCostDataModel &detailModel);

private:
    QVector<QString> strHeaders;
    QVector<QVector<QVariant>> m_rows;

    QVector<int> years;
    QVector<double> totalCost;
    QVector<double> periodic;
    QVector<double> electricity;
    QVector<double> other;
    QVector<double> accessory;

    //-----------------------------------------------------------------------------------
    //
    //  Descriptive names for the total Cost overview
    //
    enum TotalCostColumn
    {
        TotalCostViewYear = 0,
        TotalCostViewTotal,
        TotalCostViewPeriodic,
        TotalCostViewElectricity,
        TotalCostViewOther,
        TotalCostViewAccessory,
        TotalCostViewMillage
    };

};

#endif // TOTALCOSTDATAMODEL_H
