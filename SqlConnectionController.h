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

    void connectToDatabase( const QString& db_name);

    void disconnectFromDatabase();

    inline const QString& databaseName() const
    {
        return m_databaseName;
    }

    inline const bool& isConnected() const
    {
        return m_connected;
    }

    ~SqlConnectionController();

private:
    static SqlConnectionController* m_instance;

    SqlConnectionController( SqlConnectionSubject *parent = 0 );

    bool m_connected;

    QString m_databaseName;

signals:

public slots:

};

namespace The
{
    SqlConnectionController* sqlConnectionController();
};

#endif // SQLCONNECTIONCONTROLLER_H
