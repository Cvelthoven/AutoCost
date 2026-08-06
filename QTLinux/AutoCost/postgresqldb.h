//---------------------------------------------------------------------------------------
//
//  Module: postgresqldb.h
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
#ifndef POSTGRESQLDB_H
#define POSTGRESQLDB_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>

//---------------------------------------------------------------------------------------
//
//  Class PostGreSQLDB definitions
//
//---------------------------------------------------------------------------------------
class PostGreSQLDB : public QObject
{
    Q_OBJECT
public:
    //-----------------------------------------------------------------------------------
    //
    //  Public constructor
    //
    //-----------------------------------------------------------------------------------
    static PostGreSQLDB& instance();

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    //-----------------------------------------------------------------------------------
    void configure(const QString& host,
                   int port,
                   const QString& databaseName,
                   const QString& userName,
                   const QString& password,
                   const QString& connectionName);
    //-----------------------------------------------------------------------------------
    //
    //  Open/Close
    //
    bool open();
    void close();
    //-----------------------------------------------------------------------------------
    //
    //  Status and information
    //
    bool isOpen() const;
    QSqlDatabase database() const;
    QSqlError lastError() const;
    QString lastErrorText() const;

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private constructor and destructor
    //
    explicit PostGreSQLDB(QObject* parent = nullptr);
    ~PostGreSQLDB();

    Q_DISABLE_COPY_MOVE(PostGreSQLDB)

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    int
        m_iDBServerPort = 0;

    QString
        m_strDBServer = "",
        m_strDBName = "",
        m_strDBUserName = "",
        m_strDBPassword = "",
        m_strDBconnectionName = "";

    QSqlDatabase
        m_Database;
};

#endif // POSTGRESQLDB_H
