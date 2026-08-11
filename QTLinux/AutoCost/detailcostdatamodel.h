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
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>

class DetailCostDataModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit DetailCostDataModel(QObject *parent = nullptr);
    ~DetailCostDataModel();

    // Load data from database using your JOIN query
    bool loadDetailCostData();

    // Override to provide custom headers
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool getBAppDataOpen() const;
    QString getLastError() const;

private:
    QString buildDetailCostQuery() const;

    QSqlDatabase dbAutoCost;
    bool bAppDataOpen = false;
    QString strLastError;
    QSqlError queryError;

};

#endif // DETAILCOSTDATAMODEL_H
