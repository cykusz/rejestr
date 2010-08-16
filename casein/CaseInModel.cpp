#include "CaseInModel.h"
#include "SqlConnectionController.h"

#include "casein/CaseInItemDelegate.h"
#include "staff/StaffModel.h"
#include "policestation/PoliceStationModel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

#include "qmath.h"

CaseInModel* CaseInModel::m_instance = 0;

namespace The
{
    CaseInModel* caseIn()
    {
        return CaseInModel::instance();
    }
}

CaseInModel::CaseInModel(QObject *parent) :
	AbstractScrollableModel(parent)
{
    m_cache_size = 10;
	m_cache.resize( m_cache_size );
	updatePageCount();
}

CaseInModel::~CaseInModel()
{
    m_instance = 0;
}

CaseInModel* CaseInModel::instance()
{
    if ( m_instance == 0 )
        m_instance = new CaseInModel();

    return m_instance;
}

void CaseInModel::updatePageCount()
{
	QSqlQuery query( SqlConnectionController::qSqlDb() );

	query.exec("SELECT COUNT(1) as count FROM sprawy_wejscie");
	query.next();

	qDebug() << query.value(0).toDouble() << (qreal)onPage();

	setPageCount( qCeil(query.value(0).toDouble() / (qreal)onPage()) );
}

void CaseInModel::load_cache()
{
	rowsDeleteBeganNotify(0,m_cache[0].size()-1);

    m_cache.clear();
	m_cache.resize( m_cache_size );

	rowsDeleteFinishedNotify();

    QSqlQuery query( SqlConnectionController::qSqlDb() );

	query.exec( "SELECT sw.rowid, sw.*, j.miasto, j.jednostka, p.imie, p.nazwisko FROM sprawy_wejscie as sw, jednostki as j, pracownicy as p WHERE sw.id_przydzial = p.rowid AND sw.id_jednostka = j.rowid ORDER BY sw.rowid LIMIT " + QString::number(m_page*m_onPage) + ", " + QString::number(m_onPage) );
	int c = 0;
    while ( query.next() )
    {
        m_stationIds.append(query.value(3).toInt());
        m_staffIds.append(query.value(6).toInt());

        int i = 0;
		rowsInsertBeganNotify(c,c);
        m_cache[i].append(query.value(i)); i++;
		m_cache[i].append(query.value(i).toDate().toString("dd.MM.yyyy")); i++;
        m_cache[i].append(query.value(i)); i++;
        m_cache[i].append(query.value(10).toString() + " " + query.value(11).toString()); i++;
        m_cache[i].append(query.value(i)); i++;
        m_cache[i].append(query.value(i)); i++;
        m_cache[i].append(query.value(12).toString() + " " + query.value(13).toString()); i++;
        m_cache[i].append(query.value(i)); i++;
		m_cache[i].append(query.value(i).toDate().toString("dd.MM.yyyy")); i++;
        m_cache[i].append(query.value(i)); i++;
		rowsInsertFinishedNotify();
		c++;

    }
	/*rowsInsertBeganNotify(i,i);
	rowsInsertFinishedNotify();*/
}

QVariant CaseInModel::headerAt(int i) const
{
    switch ( i )
    {
    case 0:
        return QString("id");
    case 1:
        return QString("Data wejscia");
    case 2:
        return QString("Nr He");
    case 3:
        return QString("Jednostka");
    case 4:
        return QString("Nr Rsd");
    case 5:
        return QString("Opis");
    case 6:
        return QString("Przydzial");
    case 7:
        return QString("Rodzaj");
    case 8:
        return QString("Data zabezpieczenia");
    case 9:
        return QString("Uwagi");
    default:
        return QVariant();
    }
}

bool CaseInModel::isHeUnique(QString he)
{
	QSqlQuery query( SqlConnectionController::qSqlDb() );
	query.exec("SELECT 1 FROM sprawy_wejscie WHERE nr_he = '" + he + "'");
	return ! query.next();
}

bool CaseInModel::editData(int i, int j, QVariant newValue)
{
	if (j == 1 || j == 8)
	{
		QString rowid = m_cache[0][i].toString();
		QString pole = (j==1)?"data_wejscia":"data_zabezpieczenia";
		QSqlQuery query( SqlConnectionController::qSqlDb() );
		query.exec("UPDATE sprawy_wejscie SET " + pole + " = '" + newValue.toString() + "' WHERE rowid = " + rowid );
		m_cache[j][i].setValue(newValue.toDate().toString("dd.MM.yyyy"));
		return true;
	}
	else if (j == 2)
	{
		if (newValue.toString() != "")
		{
			QString rowid = m_cache[0][i].toString();

			if (isHeUnique(newValue.toString()))
			{
				QSqlQuery query( SqlConnectionController::qSqlDb() );
				query.exec("UPDATE sprawy_wejscie SET nr_he = '"+newValue.toString()+"' WHERE rowid = " + rowid);
				m_cache[j][i].setValue(newValue);
			}
			return true;
		}
	}
	else if (j == 6)
	{
		if (newValue.toString() != "0")
		{
			QString rowid = m_cache[0][i].toString();
			QSqlQuery query( SqlConnectionController::qSqlDb() );
			query.exec("UPDATE sprawy_wejscie SET id_przydzial = '" + newValue.toString() + "' WHERE rowid = " + rowid );
			m_cache[j][i].setValue(QVariant(StaffModel::nameSurnameByRowId(newValue.toString())));
			return true;
		}

	} else if (j == 3)
	{
		if (newValue.toString() != "0")
		{
			QString rowid = m_cache[0][i].toString();
			QSqlQuery query( SqlConnectionController::qSqlDb() );
			query.exec("UPDATE sprawy_wejscie SET id_jednostka = '" + newValue.toString() + "' WHERE rowid = " + rowid );
			m_cache[j][i].setValue(QVariant(PoliceStationModel::cityStationByRowId(newValue.toString())));
			return true;
		}
	}
	else if (j == 7)
	{
		QString v = newValue.toString();
		if ((QStringList() << "k" << "w" << "u" <<"uk" << "r").contains(v) )
		{
			QString rowid = m_cache[0][i].toString();
			QSqlQuery query( SqlConnectionController::qSqlDb() );
			query.exec("UPDATE sprawy_wejscie SET rodzaj = '" + newValue.toString() + "' WHERE rowid = " + rowid );
			m_cache[j][i].setValue(newValue);
			return true;
		}

	}
	else if (j == 4 || j == 5 || j == 9)
	{
		QString val = newValue.toString();
		if (val != "")
		{
			QString pole;
			QString rowid = m_cache[0][i].toString();
			switch (j)
			{
			case 4:
				pole = "nr_rsd";
				break;
			case 5:
				pole = "opis";
				break;
			case 9:
				pole = "uwagi";
				break;
			}
			QSqlQuery query( SqlConnectionController::qSqlDb() );
			query.exec("UPDATE sprawy_wejscie SET "+pole+" = '" + newValue.toString() + "' WHERE rowid = " + rowid );
			m_cache[j][i].setValue(newValue);
			return true;
		}

	}
	return false;
}

void CaseInModel::removeRow(int i)
{
	QString rowid = m_cache[0][i].toString();

	QSqlQuery query( SqlConnectionController::qSqlDb() );

	query.exec("DELETE FROM sprawy_wejscie WHERE rowid = " + rowid );

	rowsDeleteBeganNotify(i,i);

	for ( int j = 0; j < m_cache_size; ++j )
	{
		m_cache[j].remove(i);
	}

	rowsDeleteFinishedNotify();

	updatePageCount();
	load_cache();
}

bool CaseInModel::isColumnEditable(int i) const
{
    if ( i == 0 ) return false;
    else return true;
}

void CaseInModel::insertCase(QString datawej, QString he, QString jednostka, QString rsd, QString opis, QString przydzial, QString rodzaj, QString datazab, QString uwagi)
{
	QSqlQuery query( SqlConnectionController::qSqlDb() );

	if (isHeUnique(he))
	{
		if (jednostka != "0")
		{
			if (rsd != "")
			{
				if (przydzial != "0")
				{
					if ((QStringList() << "k" << "w" << "u" <<"uk" << "r").contains(rodzaj) )
					{
						query.exec("INSERT INTO sprawy_wejscie VALUES('"+datawej+"','"+he+"','"+jednostka+"','"+rsd+"','"+opis+"','"+przydzial+"','"+rodzaj+"','"+datazab+"','"+uwagi+"')");
					}
				}
			}
		}
	}


	updatePageCount();
	qDebug() << "go to last page";
	lastPage(true);
	qDebug() << "after go";

}

QAbstractItemDelegate* CaseInModel::itemDelegate(QObject *parent) const
{
    return new CaseInItemDelegate(parent);
}
