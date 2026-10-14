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
#include <QAbstractTableModel>
#include <QObject>
#include <QString>
#include <QVector>

class ElectricityOverviewDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ElectricityOverviewDataModel(QObject *parent = nullptr);

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
    QVector<QString> strHeaders;

    QVector<QVector<QVariant>> m_rows;


};

#endif // ELECTRICITYOVERVIEWDATAMODEL_H
