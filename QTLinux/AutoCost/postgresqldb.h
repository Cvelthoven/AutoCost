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
    bool isOpen() const;
    QSqlDatabase database() const;
    QSqlError lastError() const;
    QString lastErrorText() const;

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private constructor and destructor
    //
    //-----------------------------------------------------------------------------------
    explicit PostGreSQLDB(QObject* parent = nullptr);
    ~PostGreSQLDB();

    Q_DISABLE_COPY_MOVE(PostGreSQLDB)

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------
//
//  Old code before redesign
//
//---------------------------------------------------------------------------------------
// #include <QSqlDatabase>
// #include <QtSql>
// #include <QSqlQueryModel>
// #include <QString>
// //#include <QStringList>

// //---------------------------------------------------------------------------------------
// //
// //  Class PostGreSQLDB definitions
// //
// //---------------------------------------------------------------------------------------
// class PostGreSQLDB : public QSqlQueryModel
// {
//     Q_OBJECT
// public:
//     //    PostGreSQLDB(QObject *parent = nullptr);
//     //    explicit PostGreSQLDB(AppSettings *Application);// needs to be removed
//     explicit PostGreSQLDB(AppConfiguration *appSettings);
//     ~PostGreSQLDB();



//     //-----------------------------------------------------------------------------------
//     //
//     //  Setters
//     //
//     //-----------------------------------------------------------------------------------
//     void setStrConnectionName(const QString &newStrConnectionName);
//     // void setStrDBServerIP(const QString &newStrDBServerIP);
//     // void setIDBServerPort(int newIDBServerPort);
//     // void setStrDBName(const QString &newStrDBName);
//     // void setStrDBUserID(const QString &newStrDBUserID);
//     // void setStrDBPassword(const QString &newStrDBPassword);

//     //-----------------------------------------------------------------------------------
//     //
//     //  Other public methods
//     //
//     //-----------------------------------------------------------------------------------
//     int ConnectDatabase();
//     //    int ExecQuery(QString *strQuery);
//     //    int SelectQuery(QString *strQuery);
//     void close();

//     //-----------------------------------------------------------------------------------
//     //
//     //  Public variables
//     //
//     //-----------------------------------------------------------------------------------
//     QSqlDatabase dbAppDatabase;

//     //    QStringList stlRecordContent;

// private:
//     //-----------------------------------------------------------------------------------
//     //
//     //  Private variables
//     //
//     //-----------------------------------------------------------------------------------
//     //    int LoadDatabaseSettings();

//     AppConfiguration *ApplicationConfig = nullptr;
//     //    AppSettings *Application = nullptr;

//     int iDBServerPort = 0;

//     QString
//         strConnectionName = "",
//         strDBServerIP = "",
//         strDBServerPort = "",
//         strDBName = "",
//         strDBUserID = "",
//         strDBPassword = "";

//     QSqlRecord rResult;

// };

#endif // POSTGRESQLDB_H
