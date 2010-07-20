#include "SqlConnectionObserver.h"

#include <QDebug>
#include <QMessageBox>

/////////////////////////////////////////////////////////////////////////////////
//// SqlConnectionObserver Class
/////////////////////////////////////////////////////////////////////////////////

SqlConnectionObserver::SqlConnectionObserver(SqlConnectionSubject * subject)
{
    m_subject = subject;
    m_subject->attach( this );
}

SqlConnectionObserver::~SqlConnectionObserver()
{
    m_subject->detach(this);
}

void
SqlConnectionObserver::sqlConnectionChanged( SqlConnectionState newConnectionState )
{
    Q_UNUSED( newConnectionState );
}

SqlConnectionSubject::SqlConnectionSubject( QObject *parent ) : QObject( parent )
{

}

/////////////////////////////////////////////////////////////////////////////////
//// SqlConnectionSubject Class
/////////////////////////////////////////////////////////////////////////////////

void
SqlConnectionSubject::connectionChangedNotify( SqlConnectionObserver::SqlConnectionState newConnectionState )
{
    foreach ( SqlConnectionObserver* observer, m_observers )
        observer->sqlConnectionChanged( newConnectionState );
}

void
SqlConnectionSubject::attach( SqlConnectionObserver * observer )
{
    if ( !observer || m_observers.contains( observer ) )
        return;

    m_observers.insert( observer );
}

void
SqlConnectionSubject::detach( SqlConnectionObserver * observer )
{
    m_observers.remove( observer );
}
