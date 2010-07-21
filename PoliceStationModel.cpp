#include "PoliceStationModel.h"

#include <QSqlQuery>
#include <QDebug>

PoliceStationModel* PoliceStationModel::m_instance = 0;

namespace The {
    PoliceStationModel* policeStation()
    {
        return PoliceStationModel::instance();
    }
}

PoliceStationModel::PoliceStationModel(QObject *parent) :
    QObject(parent)
    , m_row_count ( -1 )
{
}

PoliceStationModel*
PoliceStationModel::instance()
{
    if (m_instance == 0)
        m_instance = new PoliceStationModel();

    return m_instance;
}

int
PoliceStationModel::row_count()
{
    if ( instance()->m_row_count < 0 )
    {
        QSqlQuery query( SqlConnectionController::qSqlDb() );

        query.exec( "SELECT COUNT(1) as cnt FROM jednostki" );

        query.next();

        instance()->m_row_count = query.value(0).toInt();

    }

    return instance()->m_row_count;
}

void PoliceStationModel::load_cache()
{
    m_cache.clear();

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec( "SELECT rowid, miasto, jednostka FROM jednostki ORDER BY miasto, jednostka" );

    while ( query.next() )
    {
        QVector<QVariant> rob;
        rob.resize(3);
        rob[0] = query.value(0);
        rob[1] = query.value(1);
        rob[2] = query.value(2);

        m_cache.append(rob);
    }
}

void PoliceStationModel::clear_cache()
{
    m_cache.clear();
}

QVariant PoliceStationModel::valueAt(int i, int j) const
{
    if ( i >= 0 && i < m_cache.size() )
    {
        return m_cache.at(i)[j];
    }
    else
        return QVariant();
}
