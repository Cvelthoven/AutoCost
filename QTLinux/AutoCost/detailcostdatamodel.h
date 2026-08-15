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
#include <QAbstractTableModel>
#include <QVector>

class DetailCostDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DetailCostDataModel(QObject *parent = nullptr);
    ~DetailCostDataModel();

    // Load data from database using your JOIN query
    bool loadDetailCostData();

    // QAbstractTableModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

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

    QVector<QString> m_headers;
    QVector<QVector<QVariant>> m_rows;
};

#endif // DETAILCOSTDATAMODEL_H
