#include "DataStructure.h"

#include "SqlConnectionController.h"

#include <QSqlQuery>

DataStructure::DataStructure(QObject *parent) :
    QObject(parent)
{
}

void
DataStructure::initStructure()
{
    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec("CREATE TABLE IF NOT EXISTS \"jednostki\" (\"miasto\" VARCHAR NOT NULL , \"jednostka\" VARCHAR NOT NULL )");

    query.exec("CREATE TABLE IF NOT EXISTS \"pracownicy\" (\"imie\" VARCHAR NOT NULL , \"nazwisko\" VARCHAR NOT NULL , \"inicjaly\" VARCHAR NOT NULL ,\"k\" BOOL NOT NULL , \"uk\" BOOL NOT NULL , \"w\" BOOL NOT NULL , \"r\" BOOL NOT NULL  DEFAULT 0 )");
}
