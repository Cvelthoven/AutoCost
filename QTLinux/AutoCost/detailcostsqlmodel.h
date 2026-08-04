//---------------------------------------------------------------------------------------
//
//  Module: DetailCostSqlModel.h
//
//  This class retrieves the autocost records in a table format which is input for the
//  DetailCostTableModel class.
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTSQLMODEL_H
#define DETAILCOSTSQLMODEL_H

#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "appsettings.h"
#include "postgresqldb.h"

#include <QObject>
#include <QSqlTableModel>
#include <QString>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostSqlModel definitions
//
//---------------------------------------------------------------------------------------
class DetailCostSqlModel
  : public QSqlTableModel
{
    Q_OBJECT
public:
    DetailCostSqlModel(QObject *parent = nullptr);
//    explicit DetailCostSqlModel(AppSettings *appSettings, QObject *parent = nullptr);

    ~DetailCostSqlModel();

    void GetRecordData(const int iRecordNb,
                      int* iRecID,
                      int* iRecordType,
                      QString* strDate,
                      QString* strDescription,
                      double* dTotalCost,
                      int* iFrequency);

    //-----------------------------------------------------------------------------------
    //
    //  Public class variables
    //
    //-----------------------------------------------------------------------------------
    QSqlTableModel *tmSqlDetailCostRecords;

    int
        iNbRows = 0;

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private class methods
    //
    //-----------------------------------------------------------------------------------
    int SetDbConnectionConfig();

    //-----------------------------------------------------------------------------------
    //
    //  Private class variables
    //
    //-----------------------------------------------------------------------------------
    AppSettings *ApplicationConfig = nullptr;
    AppSettings *AutoCostTblConnectionConfig;
    PostGreSQLDB* acAutoCostTblData;

    bool bEncrypted = false;

    QString
        strConnectionName = "acAutoCost",
        strSectionName = strSectionNameAppDB,
        strKeyName = "",
        strDBServerIP = "",
        strDBServerPort = "",
        strDBName = "",
        strDBUserID = "",
        strDBPassword = "";


    enum acAutoCostFields
    {
        RecordID = 0,
        RecordType,
        Date,
        Description,
        Amount,
        Frequency
    };

};

#endif // DETAILCOSTSQLMODEL_H
