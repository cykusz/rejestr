#include "PoliceStationModel.h"

#include <QSqlQuery>
#include <QDebug>
#include <QStringList>

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

PoliceStationModel::~PoliceStationModel()
{
    m_instance = 0;
}

int
PoliceStationModel::row_count() const
{
    return instance()->m_cache[0].size();
}

int PoliceStationModel::column_count() const
{
    return 3;
}

void PoliceStationModel::load_cache()
{
    m_cache.clear();
    m_cache.resize(3);

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec( "SELECT rowid, miasto, jednostka FROM jednostki ORDER BY rowid" );

    while ( query.next() )
    {
        QVector<QVariant> rob;

        rob.resize(3);
        rob[0] = query.value(0);
        rob[1] = query.value(1);
        rob[2] = query.value(2);

        m_cache[0].append(rob[0]);
        m_cache[1].append(rob[1]);
        m_cache[2].append(rob[2]);
    }
}

void PoliceStationModel::clear_cache()
{
    m_cache.clear();
}

QVariant PoliceStationModel::valueAt(int i, int j) const
{
    if ( i >= 0 && i < m_cache[0].size() )
    {
        return m_cache[j][i];
    }
    else
        return QVariant();
}

void PoliceStationModel::editData(int i, int j, QVariant newValue)
{
    if ( i >= 0 && i < m_cache.size() )
    {
        QString pole = "";
        if ( j == 1 )
        {
            pole = "miasto";
        } else {
            pole = "jednostka";
        }

        m_cache[j][i].setValue(newValue);

        QSqlQuery query( SqlConnectionController::qSqlDb() );

        QString rowid = m_cache[0][i].toString();

        query.exec("UPDATE jednostki SET " + pole + " = '" + newValue.toString() + "' WHERE rowid = " + rowid );


    }
}

void PoliceStationModel::removeRow(int i)
{
    QString rowid = m_cache[0][i].toString();

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec("DELETE FROM jednostki WHERE rowid = " + rowid );

    m_cache[0].remove(i);
    m_cache[1].remove(i);
    m_cache[2].remove(i);
}

QVariant PoliceStationModel::headerAt(int i) const
{
    switch ( i )
    {
    case 0:
        return QString("id");
    case 1:
        return QString("Miasto");
    case 2:
        return QString("Jednostka");
    default:
        return QVariant();
    }
}

bool PoliceStationModel::isColumnEditable(int i) const
{
    if ( i == 0 ) return false;
    else return true;
}

QStringList* PoliceStationModel::uniqueList(int i) const
{
    QSet<QString> set;
    foreach (QVariant city, m_cache[i])
    {
        set.insert(city.toString());
    }
    return new QStringList(set.toList());
}
