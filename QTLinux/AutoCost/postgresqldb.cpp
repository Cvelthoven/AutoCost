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

#include <QSqlQuery>
#include <QVariant>

//---------------------------------------------------------------------------------------
//
//  Constructors
//
//---------------------------------------------------------------------------------------
PostGreSQLDB& PostGreSQLDB::instance()
{
    static PostGreSQLDB instance;
    return instance;
}

PostGreSQLDB::PostGreSQLDB(QObject* parent)
    : QObject(parent)
{

}

//---------------------------------------------------------------------------------------
//
//  Destructor
//
//---------------------------------------------------------------------------------------
PostGreSQLDB::~PostGreSQLDB()
{
    close();
}

//---------------------------------------------------------------------------------------
//
//  Class methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  close
//
//---------------------------------------------------------------------------------------
void PostGreSQLDB::close()
{
    //-----------------------------------------------------------------------------------
    //
    //  local variables
    //
    //-----------------------------------------------------------------------------------
    const QString strConName = m_strDBconnectionName;

    //-----------------------------------------------------------------------------------
    //
    //  Verify database is open
    //
    //-----------------------------------------------------------------------------------
    if ((m_Database.isValid() && (m_Database.isOpen())))
    {
        m_Database.close();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Remove connection
    //
    //-----------------------------------------------------------------------------------
    m_Database = QSqlDatabase();
    if (QSqlDatabase::contains(strConName))
    {
        QSqlDatabase::removeDatabase(strConName);
    }
}

//---------------------------------------------------------------------------------------
//
//  configure
//
//---------------------------------------------------------------------------------------
void PostGreSQLDB::configure(
    const QString& host,
    int port,
    const QString& databaseName,
    const QString& userName,
    const QString& password,
    const QString& connectionName)
{
    m_strDBServer = host,
    m_iDBServerPort = port;
    m_strDBName = databaseName,
    m_strDBUserName = userName,
    m_strDBPassword = password,
    m_strDBconnectionName = connectionName;

}

//---------------------------------------------------------------------------------------
//
//  lastError
//
//---------------------------------------------------------------------------------------
QSqlError PostGreSQLDB::lastError() const
{
    return m_Database.lastError();
}

//---------------------------------------------------------------------------------------
//
//  lastErrorText
//
//---------------------------------------------------------------------------------------
QString PostGreSQLDB::lastErrorText() const
{
    return m_Database.lastError().text();
}

//---------------------------------------------------------------------------------------
//
//  isOpen
//
//---------------------------------------------------------------------------------------
QSqlDatabase PostGreSQLDB::database() const
{
    return m_Database;
}

//---------------------------------------------------------------------------------------
//
//  isOpen
//
//---------------------------------------------------------------------------------------
bool PostGreSQLDB::isOpen() const
{
    return (m_Database.isValid() && m_Database.isOpen());
}

//---------------------------------------------------------------------------------------
//
//  Open
//
//---------------------------------------------------------------------------------------
bool PostGreSQLDB::open()
{
    //-----------------------------------------------------------------------------------
    //
    //  Reuse connection if already registered
    //
    if (QSqlDatabase::contains(m_strDBconnectionName))
    {
        m_Database = QSqlDatabase::database(m_strDBconnectionName);
    }
    //-----------------------------------------------------------------------------------
    //
    //  create connection
    //
    else
    {
        m_Database = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"),m_strDBconnectionName);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Open database connection
    //
    m_Database.setHostName(m_strDBServer);
    m_Database.setPort(m_iDBServerPort);
    m_Database.setDatabaseName(m_strDBName);
    m_Database.setUserName(m_strDBUserName);
    m_Database.setPassword(m_strDBPassword);

    if (m_Database.open())
    {
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------------------
//
//  Old code before redesign
//
//---------------------------------------------------------------------------------------
// #include "appconfiguration.h"
// #include "postgresqldb.h"

// #include <QMessageBox>
// #include <QtSql>
// #include <QSqlDatabase>
// #include <QSqlQueryModel>

// #include <QDebug>

// //---------------------------------------------------------------------------------------
// //
// //  AppSettings default constructor
// //
// //---------------------------------------------------------------------------------------
// // PostGreSQLDB::PostGreSQLDB(QObject *parent)
// //     : QSqlQueryModel(parent)
// PostGreSQLDB::PostGreSQLDB(AppConfiguration *appSettings)
//     : ApplicationConfig(appSettings)
// {
//     qDebug() << "PostGreSQLDB constructor called";
//     //    LoadDatabaseSettings();
// }

// //----- Overload to make compile working
// //----- Needs to be removed
// // PostGreSQLDB::PostGreSQLDB(AppSettings *Application)
// //     : Application(Application)
// // {
// //     qDebug() << "PostGreSQLDB constructor called";
// //     LoadDatabaseSettings();
// // }


// //---------------------------------------------------------------------------------------
// //
// //  Destructor
// //
// //  Cleanup:
// //  - close the connection with the database
// //  - delete the instance of ApplicationConfig
// //
// //---------------------------------------------------------------------------------------
// PostGreSQLDB::~PostGreSQLDB()
// {
//     qDebug() << "PostGreSQLDB destructor called";
//     dbAppDatabase.close();
//     qDebug() << "Database connection closed";
// }

// //---------------------------------------------------------------------------------------
// //
// //  Class methodes
// //
// //---------------------------------------------------------------------------------------
// //---------------------------------------------------------------------------------------
// //
// //  ExecQuery
// //
// //  This method runs a query
// //  Input:
// //      - strQuery: string containing the query that requires execution
// //
// //  Output:
// //      - ExecQuery:
// //          - number of rows in result
// //          - -1: query did fail
// //          - -2: query returned with an error
// //
// //---------------------------------------------------------------------------------------
// // int PostGreSQLDB::ExecQuery(QString *strQuery)
// // {
// //     QSqlQuery qQuery("",dbAppDatabase);
// //     if (qQuery.exec(*strQuery))
// //     {
// //         if (qQuery.size() >= 0)
// //         {
// //             rResult = qQuery.record();
// //             return qQuery.size();
// //         }
// //     }
// //     else
// //     {
// //         return -1;
// //     }
// //     return -2;
// // }

// //---------------------------------------------------------------------------------------
// //
// //  Handles select queries with returning also the result record
// //  Can handle only 1 record as result, returns it in a stringlist (stlRecordContent)
// //
// //---------------------------------------------------------------------------------------
// // int PostGreSQLDB::SelectQuery(QString *strQuery)
// // {
// //     QString strTemp ="";
// //     stlRecordContent.clear();
// //     stlRecordContent.squeeze();

// //     //-----------------------------------------------------------------------------------
// //     //
// //     //  Execute query and store content of 1 record in a stringlist
// //     //
// //     //-----------------------------------------------------------------------------------
// //     QSqlQuery qQuery("",dbAppDatabase);
// //     if ((qQuery.exec(*strQuery))&&(qQuery.size() == 1))
// //     {
// //         qQuery.next();
// //         rResult = qQuery.record();

// //         //-------------------------------------------------------------------------------
// //         //
// //         //  Create a stringlist with the content of the field in the record
// //         //
// //         //-------------------------------------------------------------------------------
// //         for (int iCnt1 = 0; iCnt1 < rResult.count(); iCnt1++)
// //         {
// //             stlRecordContent << qQuery.value(iCnt1).toString();
// //         }
// //         return 1;
// //     }
// //     else
// //     {
// //         return qQuery.size();
// //     }
// // }

// //---------------------------------------------------------------------------------------
// //
// //  Setters
// //
// //---------------------------------------------------------------------------------------
// void PostGreSQLDB::setStrConnectionName(const QString &newStrConnectionName)
// {
//     strConnectionName = newStrConnectionName;
// }

// // void PostGreSQLDB::setStrDBServerIP(const QString &newStrDBServerIP)
// // {
// //     strDBServerIP = newStrDBServerIP;
// // }

// // void PostGreSQLDB::setIDBServerPort(int newIDBServerPort)
// // {
// //     iDBServerPort = newIDBServerPort;
// // }

// // void PostGreSQLDB::setStrDBName(const QString &newStrDBName)
// // {
// //     strDBName = newStrDBName;
// // }

// // void PostGreSQLDB::setStrDBUserID(const QString &newStrDBUserID)
// // {
// //     strDBUserID = newStrDBUserID;
// // }

// // void PostGreSQLDB::setStrDBPassword(const QString &newStrDBPassword)
// // {
// //     strDBPassword = newStrDBPassword;
// // }

// //---------------------------------------------------------------------------------------
// //
// //  Close database connection
// //
// //---------------------------------------------------------------------------------------
// void PostGreSQLDB::close()
// {
//     dbAppDatabase.close();
// }


// //---------------------------------------------------------------------------------------
// //
// //  Connect to database
// //
// //---------------------------------------------------------------------------------------
// int PostGreSQLDB::ConnectDatabase()
// {
//     //-----------------------------------------------------------------------------------
//     //
//     //  Configer database connection
//     //
//     //-----------------------------------------------------------------------------------
//     if (strConnectionName.length() > 0)
//     {
//         dbAppDatabase = QSqlDatabase::addDatabase("QPSQL", strConnectionName);
//     }
//     else
//     {
//         dbAppDatabase = QSqlDatabase::addDatabase("QPSQL");
//     }
//     dbAppDatabase.setHostName(ApplicationConfig->ApplicationDBConfig[DBServerIP]);
//     dbAppDatabase.setPort(ApplicationConfig->ApplicationDBConfig[DBServerPort].toInt());
//     dbAppDatabase.setDatabaseName(ApplicationConfig->ApplicationDBConfig[DBName]);
//     dbAppDatabase.setUserName(ApplicationConfig->ApplicationDBConfig[DBAppUserId]);
//     dbAppDatabase.setPassword(ApplicationConfig->ApplicationDBConfig[DBAppPassword]);

//     if (dbAppDatabase.open())
//     {
//         qDebug() << "Database connection with connectionname: " << strConnectionName << "successfull";
//     }
//     else
//     {
//         qDebug() << "Database connection with connectionname: " << strConnectionName << "failed";

//     }


//     return 0;
// }

// //---------------------------------------------------------------------------------------
// //
// //  LoadDatabaseSettings
// //
// //---------------------------------------------------------------------------------------
// // int PostGreSQLDB::LoadDatabaseSettings()
// // {
// //     if (ApplicationConfig == nullptr)
// //         return 1;

// //     QString host, dbName, user, password, port;

// //     // ApplicationConfig->GetAppSettings("Database", "Host", host, false);
// //     // ApplicationConfig->GetAppSettings("Database", "Name", dbName, false);
// //     // ApplicationConfig->GetAppSettings("Database", "User", user, false);
// //     // ApplicationConfig->GetAppSettings("Database", "Password", password, true);
// //     // ApplicationConfig->GetAppSettings("Database", "Port", port, false);

// //     // assign these to your existing connection members/logic
// //     return 0;
// // }
