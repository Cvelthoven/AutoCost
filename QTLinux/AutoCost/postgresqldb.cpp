//---------------------------------------------------------------------------------------
//
//  Module: postgresqldb.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "appsettings.h"
#include "postgresqldb.h"

#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
PostGreSQLDB::PostGreSQLDB(QObject *parent)
    : QSqlQueryModel(parent)
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variable
    //
    //-----------------------------------------------------------------------------------
    int iDBServerPort = 0;
    QMessageBox errorMessage;

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve application database configuration
    //
    //-----------------------------------------------------------------------------------
    ApplicationConfig = new AppSettings(strApplicationDomain,
                                        strApplicationName,
                                        strApplicationOrganization);
    strKeyName = strAppDBServerIPKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBServerIP, bEncrypted) != 0)
    {
        strDBServerIP = "";
    }
    strKeyName = strAppDBServerPortKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBServerPort, bEncrypted) != 0)
    {
        strDBServerPort = "";
    }
    else
    {
        iDBServerPort = strDBServerPort.toInt();
    }
    strKeyName = strAppDBNameKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBName, bEncrypted) != 0)
    {
        strDBName = "";
    }
    strKeyName = strAppDBUserIDKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBUserID, bEncrypted) != 0)
    {
        strDBUserID = "";
    }
    strKeyName = strAppDBUserPasswordKey;
    bEncrypted = true;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBPassword, bEncrypted) != 0)
    {
        strDBPassword = "";
    }

    //-----------------------------------------------------------------------------------
    //
    //  Connect to application database
    //
    //-----------------------------------------------------------------------------------
    if ((!strDBServerIP.isEmpty())&&
        (!strDBServerPort.isEmpty())&&
        (!strDBName.isEmpty())&&
        (!strDBUserID.isEmpty())&&
        (!strDBPassword.isEmpty()))
    {
        dbAppDatabase = QSqlDatabase::addDatabase("QPSQL");
        dbAppDatabase.setHostName(strDBServerIP);
        dbAppDatabase.setPort(iDBServerPort);
        dbAppDatabase.setDatabaseName(strDBName);
        dbAppDatabase.setUserName(strDBUserID);
        dbAppDatabase.setPassword(strDBPassword);

        if (dbAppDatabase.open())
        {
            qDebug() << "Database connected";
        }
        else
        {
            errorMessage.setText("Database connection failed.");
            errorMessage.exec();
        }
    }
    else
    {
        errorMessage.setText("Not all parameters for connection are set.");
        errorMessage.exec();
    }
}

//---------------------------------------------------------------------------------------
//
//  Destructor
//
//  Cleanup:
//  - close the connection with the database
//  - delete the instance of ApplicationConfig
//
//---------------------------------------------------------------------------------------
PostGreSQLDB::~PostGreSQLDB()
{
    dbAppDatabase.close();
    delete ApplicationConfig;
}

//---------------------------------------------------------------------------------------
//
//  Class methodes
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  ExecQuery
//
//  This method runs a query
//  Input:
//      - strQuery: string containing the query that requires execution
//
//  Output:
//      - ExecQuery:
//          - number of rows in result
//          - -1: query did fail
//          - -2: query returned with an error
//
//---------------------------------------------------------------------------------------
int PostGreSQLDB::ExecQuery(QString *strQuery)
{
    QSqlQuery qQuery("",dbAppDatabase);
    if (qQuery.exec(*strQuery))
    {
        if (qQuery.size() >= 0)
        {
//            QSqlRecord rResult = qQuery.record();
            rResult = qQuery.record();
            return qQuery.size();
        }
    }
    else
    {
        return -1;
    }
    return -2;
}

//---------------------------------------------------------------------------------------
//
//  Handles select queries with returning also the result records
//
//---------------------------------------------------------------------------------------
int PostGreSQLDB::SelectQuery(QString *strQuery)
{
    QString strTemp ="";
    QSqlQuery qQuery("",dbAppDatabase);
    if ((qQuery.exec(*strQuery))&&(qQuery.size() == 1))
    {
        qQuery.next();
        rResult = qQuery.record();

        //-------------------------------------------------------------------------------
        //
        //  Create a stringlist with the content of the field in the record
        //
        //-------------------------------------------------------------------------------
        for (int iCnt1 = 0; iCnt1 < rResult.count(); iCnt1++)
        {
            stlRecordContent << qQuery.value(iCnt1).toString();
        }
        return 1;
    }
    else
    {
        return qQuery.size();
    }
}
