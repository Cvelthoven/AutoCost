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
    QString CostAccuEnd();
    QString CostAccuLoadDelta();
    QString CostAccuStart();
    QString CostAccuUsedPercentage();
    QString CostElectricity();
    void CostElectricityFieldCalc();
    QString CostElectricityRecId();
    QString CostEuroPerKWh();
    QString CostKMperPercentage();
    QString CostKWhLoaded();
    QString CostKWhPerKM();
    QString CostKWhPerPercentage();
    QString CostLoadStartTime();
    QString CostMillage();
    QString CostMillageTrip();
    QString CostTripKwhUsed();
    QString CostOther();
    QString CostPeriodic();

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
    bool bAppDataOpen = false;

    double
        dElectrcityAccuUsedPercentage = 0,
        dElectricityEuroPerKWh = 0,
        dElectricityKMperPercentage = 0,
        dElectricityKWhperKM = 0,
        dElectricityKWhperPercentage = 0,
        dElectirictyTripUsage = 0,
        dElectricitySessionLoadPercentage = 0,
        dElectricityTotalKMPrev = 0,
        dElectrictyTripKM = 0;

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
        dElectricityAccuStart = -1,
        dElectricityAccuEnd = -1,
        dElectricityKWhLoaded = -1,
        dElectricityTotalKM = -1;
    int
        iAutoCostRecID = -1,
        iAutoCostType = -1,
        iAutoCostFrequency = -1,
        iElectricityRecID = -1;
    QDate
        dtAutoCoatDate;
    QString
        strAutoCostDescription = "";
    QTime
        tmElectricityStartTime;

};

#endif // DETAILCOSTDATAMODEL_H
