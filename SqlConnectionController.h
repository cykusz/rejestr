#ifndef SQLCONNECTIONCONTROLLER_H
#define SQLCONNECTIONCONTROLLER_H

#include <QObject>
#include <QtSql/QSqlDatabase>

#include "core/sql/SqlConnectionObserver.h"

class SqlConnectionController : public SqlConnectionSubject
{
    Q_OBJECT
public:
    static SqlConnectionController* instance();

private:
    static SqlConnectionController* m_instance;

    SqlConnectionController( SqlConnectionSubject *parent = 0 );

    bool m_connected;

signals:

public slots:

};

#endif // SQLCONNECTIONCONTROLLER_H
