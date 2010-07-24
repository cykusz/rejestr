#include "StaffModel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "staff/StaffItemDelegate.h"

StaffModel* StaffModel::m_instance = 0;

namespace The {
    StaffModel* staff()
    {
        return StaffModel::instance();
    }
}

StaffModel* StaffModel::instance()
{
    if (m_instance == 0)
        m_instance = new StaffModel();

    return m_instance;
}

StaffModel::~StaffModel()
{
    clear_cache();

    m_instance = 0;
}

StaffModel::StaffModel(QObject *parent) :
    AbstractModel(parent)
{
    m_cache_size = 7;
    load_cache();
}

void StaffModel::load_cache()
{
    m_cache.clear();
    m_cache.resize( m_cache_size );
    m_addRow.clear();
    m_addRow.resize( m_cache_size );
    m_addRow[0] = "+";
    m_addRow[4] = QVariant(false);
    m_addRow[5] = QVariant(false);
    m_addRow[6] = QVariant(false);

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec( "SELECT rowid, * FROM pracownicy ORDER BY rowid" );

    while ( query.next() )
    {
        for ( int i = 0; i < m_cache_size; ++i )
        {
            m_cache[i].append(query.value(i));
        }
    }
}

bool StaffModel::editData(int i, int j, QVariant newValue)
{
    if ( i >= 0 && i < m_cache[0].size() )
    {
        QString pole = "";
        switch (j) {
        case 1:
            pole = QString("imie");
            break;
        case 2:
            pole = QString("nazwisko");
            break;
        case 3:
            pole = QString("inicjaly");
            break;
        case 4:
            pole = QString("k");
            break;
        case 5:
            pole = QString("uk");
            break;
        case 6:
            pole = QString("w");
            break;
        default:
            return false;
        }

        m_cache[j][i].setValue(newValue);

        QSqlQuery query( SqlConnectionController::qSqlDb() );

        QString rowid = m_cache[0][i].toString();

        query.exec("UPDATE pracownicy SET " + pole + " = '" + newValue.toString() + "' WHERE rowid = " + rowid );
    } else if ( i == m_cache[0].size() )
    {
        if ( j > 0 )
        {
            m_addRow[j] = newValue;

            if ( m_addRow[1].isValid()
                && m_addRow[2].isValid()
                && m_addRow[3].isValid()
                && m_addRow[4].isValid()
                && m_addRow[5].isValid()
                && m_addRow[6].isValid())
            {
                QString imie = m_addRow[1].toString();
                QString nazwisko = m_addRow[2].toString();
                QString inicjaly = m_addRow[3].toString();
                QString k = m_addRow[4].toString();
                QString uk = m_addRow[5].toString();
                QString w = m_addRow[6].toString();

                QSqlQuery query( SqlConnectionController::qSqlDb() );

                query.exec("INSERT INTO pracownicy VALUES('"+imie+"','"+nazwisko+"','"+inicjaly+"','"+k+"','"+uk+"','"+w+"')");
                QVariant insertId = query.lastInsertId();

                m_cache[0].append(insertId);
                m_cache[1].append(m_addRow[1]);
                m_cache[2].append(m_addRow[2]);
                m_cache[3].append(m_addRow[3]);
                m_cache[4].append(m_addRow[4]);
                m_cache[5].append(m_addRow[5]);
                m_cache[6].append(m_addRow[6]);

                m_addRow[1] = QVariant();
                m_addRow[2] = QVariant();
                m_addRow[3] = QVariant();
                m_addRow[4] = QVariant(false);
                m_addRow[5] = QVariant(false);
                m_addRow[6] = QVariant(false);

                return true;
            }
        }
    }

    return false;
}

void StaffModel::removeRow(int i)
{
    QString rowid = m_cache[0][i].toString();

    QSqlQuery query( SqlConnectionController::qSqlDb() );

    query.exec("DELETE FROM pracownicy WHERE rowid = " + rowid );

    for ( int j = 0; j < m_cache_size; ++j )
    {
        m_cache[j].remove(i);
    }
}

QVariant StaffModel::headerAt(int i) const
{
    switch ( i )
    {
    case 0:
        return QString("id");
    case 1:
        return QString("Imie");
    case 2:
        return QString("Nazwisko");
    case 3:
        return QString("Inicjaly");
    case 4:
        return QString("k");
    case 5:
        return QString("uk");
    case 6:
        return QString("w");
    default:
        return QVariant();
    }
}

bool StaffModel::isColumnEditable(int i) const
{
    if ( i == 0 ) return false;
    else return true;
}

QAbstractItemDelegate* StaffModel::itemDelegate(QObject* parent) const
{
    return new StaffItemDelegate( parent );
}
