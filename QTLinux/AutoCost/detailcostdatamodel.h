//---------------------------------------------------------------------------------------
//
//  Module: detailcostdatamodel.h
//
//  This class manages the detail cost data
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTDATAMODEL_H
#define DETAILCOSTDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QDateTime>
#include <QObject>
#include <QString>
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
    //-----------------------------------------------------------------------------------
    //
    //  Private methods
    //
    //-----------------------------------------------------------------------------------
    QString buildDetailCostQuery() const;
    QString CostAccessory();
    QString CostElectricity();
    QString CostOther();
    QString CostPeriodic();

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
    bool bAppDataOpen = false;
    QSqlDatabase dbAutoCost;
    QSqlError queryError;
    QString strLastError;

    QVector<QString> strHeaders;
    QVector<QVector<QVariant>> m_rows;

    //-----------------------------------------------------------------------------------
    //
    //  Variables that contain record values
    //
    double
        dAutoCostTotalCost = -999999,
        dElectricityKWhLoaded = -1;
    int
        iAutoCostRecID = -1,
        iAutoCostType = -1,
        iAutoCostFrequency = -1,
        iElectricityRecID = -1,
        iElectricityTotalKM = -1,
        iElectricityAccuStart = -1,
        iElectricityAccuEnd = -1;
    QDate
        dtAutoCoatDate;
    QString
        strAutoCostDescription = "";
    QTime
        tmElectricityStartTime;

};

#endif // DETAILCOSTDATAMODEL_H
