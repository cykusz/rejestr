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
    ModelInterface(parent)
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
PoliceStationModel::row_count() const
{
    return instance()->m_cache.size();
}

int PoliceStationModel::column_count() const
{
    return 2;
}

void PoliceStationModel::load_cache()
{
    m_cache.clear();

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec( "SELECT rowid, miasto, jednostka FROM jednostki ORDER BY rowid" );

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

void PoliceStationModel::editData(int i, int j, QVariant newValue)
{
    if ( i >= 0 && i < m_cache.size() )
    {
        m_cache[i][j].setValue(newValue);

        QSqlQuery query( SqlConnectionController::qSqlDb() );

        QString rowid = m_cache[i][0].toString();
        QString pole = (j==1)?"miasto":"jednostka";

        query.exec("UPDATE jednostki SET " + pole + " = '" + newValue.toString() + "' WHERE rowid = " + rowid );
    }
}

void PoliceStationModel::removeRow(int i)
{
    QString rowid = m_cache[i][0].toString();

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec("DELETE FROM jednostki WHERE rowid = " + rowid );

    m_cache.remove(i);
}

QVariant PoliceStationModel::headerAt(int i) const
{
    switch ( i )
    {
    case 0:
        return QString("Miasto");
    case 1:
        return QString("Jednostka");
    default:
        return QVariant();
    }
}
