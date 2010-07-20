#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include <QObject>
#include <QSet>

class SqlConnectionSubject;

class SqlConnectionObserver
{
public:
    SqlConnectionObserver( SqlConnectionSubject* );
    ~SqlConnectionObserver();

    enum ConnectionState
    {
        Connected, Disconnected
    };

    virtual void sqlConnectionChanged( ConnectionState newConnectionState );

private:
    SqlConnectionSubject* m_subject;
};

class SqlConnectionSubject : public QObject
{
    Q_OBJECT

    friend class SqlConnectionObserver;
protected:

    void connectionChangedNotify( SqlConnectionObserver::ConnectionState newConnectionState );

private:
    void attach( SqlConnectionObserver* );
    void detach( SqlConnectionObserver* );

    QSet<SqlConnectionObserver*> m_observers;

public:
    explicit SqlConnectionSubject( QObject* parent = 0 );
};

#endif // SQLCONNECTION_H
