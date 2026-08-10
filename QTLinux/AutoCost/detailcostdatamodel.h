//---------------------------------------------------------------------------------------
//
//  Module: detailcostdatamodel.h
//
//  This class manages the detail cost data
//  The class DetailCostDataView manages the presentation of the detailed cost data
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTDATAMODEL_H
#define DETAILCOSTDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QObject>

#include <QAbstractTableModel>
#include <QSqlDatabase>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostDataModel definitions
//
//---------------------------------------------------------------------------------------
class DetailCostDataModel :
    public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DetailCostDataModel(QObject *parent = nullptr);

    bool getBAppDataOpen() const;

    int RetrieveDetailCostData();


    //-----------------------------------------------------------------------------------
    //
    //  Default methods required by QAbstractTableModel
    //
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QSqlDatabase dbAutoCost;

    bool
        bAppDataOpen = false;

};

#endif // DETAILCOSTDATAMODEL_H
