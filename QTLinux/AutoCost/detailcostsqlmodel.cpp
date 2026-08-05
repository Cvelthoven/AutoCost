//---------------------------------------------------------------------------------------
//
//  Module: DetailCostSqlModel.cpp
//
//  This class retrieves the autocost records in a table format which is input for the
//  DetailCostTableModel class.
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettings.h"
#include "detailcostsqlmodel.h"
#include "postgresqldb.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QString>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  DetailCostSqlModel default constructor
//
//---------------------------------------------------------------------------------------
DetailCostSqlModel::DetailCostSqlModel(QObject *parent)
{
    // acAutoCostTblData = new PostGreSQLDB(ApplicationConfig);
    // if (SetDbConnectionConfig() != 0)
    // {
    //     qDebug() << "error in database configuration definition in config file";
    // }
    // if (acAutoCostTblData->ConnectDatabase() != 0)
    // {
    //     qDebug() << "Database connection to acAutoCost failed";
    // }

    //-----------------------------------------------------------------------------------
    //
    //  Create a QSqlTableModel
    //
    //-----------------------------------------------------------------------------------
    tmSqlDetailCostRecords = new QSqlTableModel(this, acAutoCostTblData->dbAppDatabase);
    tmSqlDetailCostRecords->setTable("acAutoCost");
    tmSqlDetailCostRecords->setSort(Date, Qt::AscendingOrder);
    tmSqlDetailCostRecords->select();
    iNbRows = tmSqlDetailCostRecords->rowCount();
}

//---------------------------------------------------------------------------------------
//
//  DetailCostSqlModel destructor
//
//---------------------------------------------------------------------------------------
DetailCostSqlModel::~DetailCostSqlModel()
{
    qDebug() << "DetailCostSqlModel destructor called";
    //-----------------------------------------------------------------------------------
    //
    //  Close autocost db connection
    //
    //-----------------------------------------------------------------------------------
    if (acAutoCostTblData != nullptr)
    {
        qDebug() << "db connection for autocost closed in DetailCostSqlModel destructor";
        delete acAutoCostTblData;
    }
    QSqlDatabase::removeDatabase(strConnectionName);

    //-----------------------------------------------------------------------------------
    //
    //  Clean up
    //
    //-----------------------------------------------------------------------------------
    qDebug() << "Destructor of QSqlTableModel called in DetailCostSqlModel destructor";
    delete tmSqlDetailCostRecords;

}

//---------------------------------------------------------------------------------------
//
//  Class methodes
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  SetDbConnectionConfig
//
//---------------------------------------------------------------------------------------
int DetailCostSqlModel::SetDbConnectionConfig()
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variable
    //
    //-----------------------------------------------------------------------------------
    int
        iDBServerPort = 0,
        iRC = 0;
    QMessageBox errorMessage;

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve acAutoCost table database configuration
    //
    //-----------------------------------------------------------------------------------
    AutoCostTblConnectionConfig = new AppSettings(strApplicationDomain,
                                        strApplicationName,
                                        strApplicationOrganization);

    //-----------------------------------------------------------------------------------
    //
    //  Database server IP
    //
    strKeyName = strAppDBServerIPKey;
    if (AutoCostTblConnectionConfig->GetAppSettings(strSectionName,
                                                    strKeyName,
                                                    strDBServerIP,
                                                    bEncrypted) == 0)
    {
        if (strDBServerIP.length() > 0)
        {
            acAutoCostTblData->setStrDBServerIP(strDBServerIP);
        }
        else
        {
            strDBServerIP = "";
            iRC = 1;
        }
    }
    else
    {
        strDBServerIP = "";
        iRC = 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Database server port
    //
    strKeyName = strAppDBServerPortKey;
    if (AutoCostTblConnectionConfig->GetAppSettings(strSectionName,
                                                    strKeyName,
                                                    strDBServerPort,
                                                    bEncrypted) == 0)
    {
        if (strDBServerPort.length() > 0)
        {
            iDBServerPort = strDBServerPort.toInt();
        }
        else
        {
            iDBServerPort = 0;
        }
        if (iDBServerPort > 0)
        {
            acAutoCostTblData->setIDBServerPort(iDBServerPort);
        }
        else
        {
            strDBServerPort = "";
            iRC = 1;
        }
    }
    else
    {
        strDBServerPort = "";
        iRC = 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Database Name
    //
    strKeyName = strAppDBNameKey;
    if (AutoCostTblConnectionConfig->GetAppSettings(strSectionName,
                                                    strKeyName,
                                                    strDBName,
                                                    bEncrypted) == 0)
    {
        if (strDBName.length() > 0)
        {
            acAutoCostTblData->setStrDBName(strDBName);
        }
        else
        {
            strDBName = "";
            iRC = 1;
        }
    }
    else
    {
        strDBName = "";
        iRC = 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Application database userid
    //
    strKeyName = strAppDBUserIDKey;
    if (AutoCostTblConnectionConfig->GetAppSettings(strSectionName,
                                                    strKeyName,
                                                    strDBUserID,
                                                    bEncrypted) == 0)
    {
        if (strDBUserID.length() > 0)
        {
            acAutoCostTblData->setStrDBUserID(strDBUserID);
        }
        else
        {
            strDBUserID = "";
            iRC = 1;
        }
    }
    else
    {
        strDBUserID = "";
        iRC = 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Application database password
    //
    strKeyName = strAppDBUserPasswordKey;
    bEncrypted = true;
    if (AutoCostTblConnectionConfig->GetAppSettings(strSectionName,
                                                    strKeyName,
                                                    strDBPassword,
                                                    bEncrypted) == 0)
    {
        if (strDBPassword.length() > 0)
        {
            acAutoCostTblData->setStrDBPassword(strDBPassword);
        }
        else
        {
            strDBPassword = "";
            iRC = 1;
        }
    }
    else
    {
        strDBPassword = "";
        iRC = 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  acAutoCost database connection name
    //
    acAutoCostTblData->setStrConnectionName(strConnectionName);

    return iRC;

}


//---------------------------------------------------------------------------------------
//
//  GetRecordData
//
//  Input:
//      - iRecordNb: position of the record in sorted table (not RecID)
//  Output:
//      - iRecID: recordID
//      - iRecordType: record type
//      - strDate: content date field
//      - strDescription: content description field
//      - dTotalCost: content totalcost field
//      - iFrequency: content frequency field
//
//---------------------------------------------------------------------------------------
void DetailCostSqlModel::GetRecordData(const int iRecordNb,
                                      int* iRecID,
                                      int* iRecordType,
                                      QString* strDate,
                                      QString* strDescription,
                                      double* dTotalCost,
                                      int* iFrequency)
{
    bool bOk;
    double dTemp;
    int iTemp;
    QSqlRecord tmSqlDetailCostRecord = tmSqlDetailCostRecords->record(iRecordNb);
    iTemp = tmSqlDetailCostRecord.value("AutoCostRecID").toInt(&bOk);
    if (bOk)
    {
        *iRecID = iTemp;
    }
    else
    {
        *iRecID = -1;
    }
    iTemp = tmSqlDetailCostRecord.value("RecordType").toInt(&bOk);
    if (bOk)
    {
        *iRecordType = iTemp;
    }
    else
    {
        *iRecordType = -1;
    }
    *strDate = tmSqlDetailCostRecord.value("Date").toString();
    *strDescription = tmSqlDetailCostRecord.value("Description").toString();
    dTemp = tmSqlDetailCostRecord.value("TotalCost").toDouble(&bOk);
    if (bOk)
    {
        *dTotalCost = dTemp;
    }
    else
    {
        *dTotalCost = -9999999;
    }
    iTemp = tmSqlDetailCostRecord.value("Frequency").toInt(&bOk);
    if (bOk)
    {
        *iFrequency = iTemp;
    }
    else
    {
        *iFrequency = -1;
    }

}

