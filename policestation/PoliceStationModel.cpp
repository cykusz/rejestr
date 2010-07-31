#include "PoliceStationModel.h"
#include "policestation/PoliceStationItemDelegate.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>

PoliceStationModel* PoliceStationModel::m_instance = 0;
PoliceStationListModel* PoliceStationListModel::m_instance = 0;

namespace The {
    PoliceStationModel* policeStation()
    {
        return PoliceStationModel::instance();
    }

    PoliceStationListModel* policeStationList()
    {
        return PoliceStationListModel::instance();
    }
}

PoliceStationModel::PoliceStationModel(QObject *parent) :
    AbstractModel(parent)
{
    m_cache_size = 3;
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

    clear_cache();

    qDebug() << "delete policeStation";

    foreach (QStringList *item, m_uniqueLists)
    {
        delete item;
    }
}

void PoliceStationModel::load_cache()
{
    m_cache.clear();
    m_cache.resize( m_cache_size );
    m_addRow.clear();
    m_addRow.resize( m_cache_size );
    m_addRow[0] = "+";

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec( "SELECT rowid, miasto, jednostka FROM jednostki ORDER BY rowid" );

    while ( query.next() )
    {        
        for ( int i = 0; i < m_cache_size; ++i )
        {
            m_cache[i].append(query.value(i));
        }
    }

    updateUniqueLists();
}

bool PoliceStationModel::editData(int i, int j, QVariant newValue)
{
    if ( i >= 0 && i < m_cache[0].size() )
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

        updateUniqueLists();
    } else if ( i == m_cache[0].size() )
    {
        if ( j > 0 )
        {
            m_addRow[j] = newValue;

            if ( m_addRow[1].isValid() && m_addRow[2].isValid() )
            {
                QString miasto = m_addRow[1].toString();
                QString jednostka = m_addRow[2].toString();

                QSqlQuery query( SqlConnectionController::qSqlDb() );

                query.exec("INSERT INTO jednostki VALUES('"+miasto+"','"+jednostka+"')");



                QVariant insertId = query.lastInsertId();

                rowsInsertBeganNotify(m_cache[0].size(),m_cache[0].size());

                m_cache[0].append(insertId);
                m_cache[1].append(m_addRow[1]);
                m_cache[2].append(m_addRow[2]);

                m_addRow[1] = QVariant();
                m_addRow[2] = QVariant();

                rowsInsertFinishedNotify();

                updateUniqueLists();

                return true;
            }
        }
    }

    return false;
}

void PoliceStationModel::removeRow(int i)
{
    QString rowid = m_cache[0][i].toString();

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec("DELETE FROM jednostki WHERE rowid = " + rowid );

    updateUniqueLists();

    rowsDeleteBeganNotify(i,i);

    for ( int j = 0; j < m_cache_size; ++j )
    {
        m_cache[j].remove(i);
    }

    rowsDeleteFinishedNotify();
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

void PoliceStationModel::updateUniqueLists()
{
    m_uniqueLists.clear();
    m_uniqueLists.resize(2);
    QSet<QString> set;
    for (int i = 1; i < 3; ++i)
    {
        set.clear();
        foreach (QVariant str, m_cache[i])
        {
            set.insert(str.toString());
        }
        m_uniqueLists[i-1] = new QStringList(set.toList());
    }

}

QStringList* PoliceStationModel::uniqueList(int i) const
{
    return m_uniqueLists[i-1];
}

QAbstractItemDelegate* PoliceStationModel::itemDelegate(QObject* parent) const
{
    return new PoliceStationItemDelegate( m_instance, parent );
}

//**************
//PoliceStationListModel
//**************

PoliceStationListModel* PoliceStationListModel::instance()
{
    if (m_instance == 0)
        m_instance = new PoliceStationListModel();

    return m_instance;
}

PoliceStationListModel::PoliceStationListModel(QObject *parent) :
    AbstractListModel(parent)
{
}

void PoliceStationListModel::initModel()
{
    m_cache.clear();
    m_cache.resize(2);

    QSqlQuery query( SqlConnectionController::qSqlDb() );
    query.exec( "SELECT rowid, miasto, jednostka FROM jednostki ORDER BY rowid" );

    while ( query.next() )
    {
        m_cache[0].append(query.value(0).toInt());
        m_cache[1].append(query.value(1).toString() + " " + query.value(2).toString());
    }
}
