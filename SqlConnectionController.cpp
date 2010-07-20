#include "SqlConnectionController.h"
#include <QDebug>
#include <QStringList>

namespace The
{
    SqlConnectionController* sqlConnectionController() { return SqlConnectionController::instance(); };
}

SqlConnectionController* SqlConnectionController::m_instance = 0;

SqlConnectionController* SqlConnectionController::instance()
{
    if ( m_instance == 0 )
    {
        m_instance = new SqlConnectionController();
    }

    return m_instance;
}

SqlConnectionController::SqlConnectionController(SqlConnectionSubject *parent) :
    SqlConnectionSubject(parent)
    , m_databaseName("")
    , m_connected( false )
{
    QSqlDatabase::addDatabase("QSQLITE","rejestr");

}

SqlConnectionController::~SqlConnectionController()
{
    QSqlDatabase::removeDatabase("rejestr");
}

void SqlConnectionController::connectToDatabase(const QString &db_name)
{
    QSqlDatabase db = QSqlDatabase::database("rejestr",false);

    if ( ! db.isOpen() )
    {
        db.setDatabaseName(db_name);

        if ( db.open() )
        {
            m_databaseName = db_name;

            m_connected = true;

            connectionChangedNotify( SqlConnectionObserver::Connected );
        }
    }
    else
        disconnectFromDatabase();

}

void SqlConnectionController::disconnectFromDatabase()
{
    QSqlDatabase db = QSqlDatabase::database("rejestr");

    if ( db.isOpen() )
    {
        db.close();

        m_connected = false;

        connectionChangedNotify( SqlConnectionObserver::Disconnected );
    }
}
