#include "ModelObserver.h"

ModelObserver::ModelObserver(ModelSubject * subject)
{
    m_subject = subject;
    m_subject->attach( this );
}

ModelObserver::~ModelObserver()
{
    if (m_subject)
        m_subject->detach(this);
}

void ModelObserver::modelRowsDeleteBegan(int posStart, int posEnd)
{
    Q_UNUSED(posStart)
    Q_UNUSED(posEnd)
}

void ModelObserver::modelRowsDeleteFinished()
{

}

void ModelObserver::modelRowsInsertBegan(int posStart, int posEnd)
{
    Q_UNUSED(posStart)
    Q_UNUSED(posEnd)
}

void ModelObserver::modelRowsInsertFinished()
{

}

void ModelObserver::modelDeleted()
{
    m_subject = 0;
}

ModelSubject::ModelSubject(QObject *parent) : QObject(parent)
{

}

ModelSubject::~ModelSubject()
{
    foreach ( ModelObserver* observer, m_observers )
        observer->modelDeleted();
}


void ModelSubject::rowsDeleteBeganNotify(int posStart, int posEnd)
{
    foreach ( ModelObserver* observer, m_observers )
        observer->modelRowsDeleteBegan(posStart, posEnd);
}

void ModelSubject::rowsDeleteFinishedNotify()
{
    foreach ( ModelObserver* observer, m_observers )
        observer->modelRowsDeleteFinished();
}

void ModelSubject::rowsInsertBeganNotify(int posStart, int posEnd)
{
    foreach ( ModelObserver* observer, m_observers )
        observer->modelRowsInsertBegan(posStart, posEnd);
}

void ModelSubject::rowsInsertFinishedNotify()
{
    foreach ( ModelObserver* observer, m_observers )
        observer->modelRowsInsertFinished();
}

void
ModelSubject::attach( ModelObserver * observer )
{
    if ( !observer || m_observers.contains( observer ) )
        return;

    m_observers.insert( observer );
}

void
ModelSubject::detach( ModelObserver * observer )
{
    m_observers.remove( observer );
}
