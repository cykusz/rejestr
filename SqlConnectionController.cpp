#include "SqlConnectionController.h"

SqlConnectionController::SqlConnectionController(SqlConnectionSubject *parent) :
    SqlConnectionSubject(parent)
{
    QSqlDatabase::addDatabase("QSQLITE");
}

SqlConnectionController* SqlConnectionController::m_instance = 0;

SqlConnectionController* SqlConnectionController::instance()
{
    if ( m_instance == 0 )
        m_instance = new SqlConnectionController();

    return m_instance;
}
