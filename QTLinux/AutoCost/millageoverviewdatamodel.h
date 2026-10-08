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
#include <QAbstractTableModel>
#include <QObject>
#include <QString>
#include <QVector>

class MillageOverviewDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MillageOverviewDataModel(QObject *parent = nullptr);

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    bool loadMillageData(const DetailCostDataModel &detailModel);

    //-----------------------------------------------------------------------------------
    //
    //  Default QAbstractTableModel overrides
    //
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;


private:
    double dMillageCurrent = -1;

    QVector<QString> strHeaders;
    QVector<QVector<QVariant>> m_rows;

    QVector<double> dMillageYearStart;
    QVector<int> years;


};

#endif // MILLAGEOVERVIEWDATAMODEL_H
