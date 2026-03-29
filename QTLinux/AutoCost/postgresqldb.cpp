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

#include <QAbstractTableModel>
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
            qDebug() << "Database connection failed";
        }
    }
    else
    {
        qDebug() << "Not all parameters for connection are set";
    }
}

//---------------------------------------------------------------------------------------
//
//  Destructor
//
//---------------------------------------------------------------------------------------
PostGreSQLDB::~PostGreSQLDB()
{
    dbAppDatabase.close();
    qDebug() << "PostgreSQLDB destructor is callled";

}

int PostGreSQLDB::rowCount(const QModelIndex &) const
{
    return 5;
}

int PostGreSQLDB::columnCount(const QModelIndex &) const
{
    return 10;
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
//
//---------------------------------------------------------------------------------------
int PostGreSQLDB::ExecQuery(QString *strQuery)
{
    QSqlQuery qQuery("",dbAppDatabase);
    if (qQuery.exec(*strQuery))
    {
        return qQuery.size();
    }
    else
    {
        return -1;
    }
}
