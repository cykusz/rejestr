#ifndef MODELOBSERVER_H
#define MODELOBSERVER_H

#include <QObject>
#include <QSet>

class ModelSubject;

class ModelObserver
{
public:
    ModelObserver( ModelSubject* );
    ~ModelObserver();

    virtual void modelRowsDeleteBegan(int posStart, int posEnd);
    virtual void modelRowsDeleteFinished();

    virtual void modelRowsInsertBegan(int posStart, int posEnd);
    virtual void modelRowsInsertFinished();


    void modelDeleted();

private:
    ModelSubject* m_subject;
};

class ModelSubject : public QObject
{
    Q_OBJECT

    friend class ModelObserver;
protected:

    void rowsDeleteBeganNotify( int posStart, int posEnd );
    void rowsDeleteFinishedNotify( );
    void rowsInsertBeganNotify( int posStart, int posEnd );
    void rowsInsertFinishedNotify( );

private:
    void attach( ModelObserver* );
    void detach( ModelObserver* );

    QSet<ModelObserver*> m_observers;

public:
    explicit ModelSubject( QObject* parent = 0 );
    virtual ~ModelSubject();
};

#endif // MODELOBSERVER_H
