//---------------------------------------------------------------------------------------
//
//  Module: postgresqldb.cpp
//
//  This class manages an instance of a connection to a PostGreSql database
//  and it the connection can be reused application wide
//
//---------------------------------------------------------------------------------------
//
//  Usage:
//      auto& dbmDatabaseCon = PostGreSQLDB::instance();
//      dbmDatabaseCon.configure("localhost", 5432, "autocost", "postgres", "secret");
//      if (!dbmDatabaseCon.open()) { qWarning() << dbmDatabaseCon.lastErrorText(); }
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
    const QString strConName = m_strDBconnectionName;

    //-----------------------------------------------------------------------------------
    //
    //  Verify database is open
    //
    if ((m_Database.isValid() && (m_Database.isOpen())))
    {
        m_Database.close();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Remove connection
    //
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
//  database
//
//---------------------------------------------------------------------------------------
QSqlDatabase PostGreSQLDB::database() const
{
    return m_Database;
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

    if (!m_Database.open())
    {
        return false;
    }

    return true;
}

