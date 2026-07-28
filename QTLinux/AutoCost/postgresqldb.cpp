//---------------------------------------------------------------------------------------
//
//  Module: postgresqldb.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
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
    qDebug() << "PostGreSQLDB constructor called";
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
    qDebug() << "PostGreSQLDB destructor called";
    dbAppDatabase.close();
    qDebug() << "Database connection closed";
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
//  Handles select queries with returning also the result record
//  Can handle only 1 record as result, returns it in a stringlist (stlRecordContent)
//
//---------------------------------------------------------------------------------------
int PostGreSQLDB::SelectQuery(QString *strQuery)
{
    QString strTemp ="";
    stlRecordContent.clear();
    stlRecordContent.squeeze();

    //-----------------------------------------------------------------------------------
    //
    //  Execute query and store content of 1 record in a stringlist
    //
    //-----------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------
//
//  Setters
//
//---------------------------------------------------------------------------------------
void PostGreSQLDB::close()
{
    dbAppDatabase.close();
}

void PostGreSQLDB::setStrConnectionName(const QString &newStrConnectionName)
{
    strConnectionName = newStrConnectionName;
}

void PostGreSQLDB::setStrDBServerIP(const QString &newStrDBServerIP)
{
    strDBServerIP = newStrDBServerIP;
}

void PostGreSQLDB::setIDBServerPort(int newIDBServerPort)
{
    iDBServerPort = newIDBServerPort;
}

void PostGreSQLDB::setStrDBName(const QString &newStrDBName)
{
    strDBName = newStrDBName;
}

void PostGreSQLDB::setStrDBUserID(const QString &newStrDBUserID)
{
    strDBUserID = newStrDBUserID;
}

void PostGreSQLDB::setStrDBPassword(const QString &newStrDBPassword)
{
    strDBPassword = newStrDBPassword;
}

//---------------------------------------------------------------------------------------
//
//  Connect to database
//
//---------------------------------------------------------------------------------------
int PostGreSQLDB::ConnectDatabase()
{
    //-----------------------------------------------------------------------------------
    //
    //  Configer database connection
    //
    //-----------------------------------------------------------------------------------
    if (strConnectionName.length() >= 0)
    {
        dbAppDatabase = QSqlDatabase::addDatabase("QPSQL", strConnectionName);
    }
    else
    {
        dbAppDatabase = QSqlDatabase::addDatabase("QPSQL");
    }
    dbAppDatabase.setHostName(strDBServerIP);
    dbAppDatabase.setPort(iDBServerPort);
    dbAppDatabase.setDatabaseName(strDBName);
    dbAppDatabase.setUserName(strDBUserID);
    dbAppDatabase.setPassword(strDBPassword);

    if (dbAppDatabase.open())
    {
        qDebug() << "Database connected";
    }


    return 0;
}

