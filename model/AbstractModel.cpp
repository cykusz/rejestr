#include "AbstractModel.h"
#include <QItemDelegate>

AbstractModel::AbstractModel(QObject *parent) :
    ModelInterface(parent)
    , m_row_count( -1 )
{
}

QVariant AbstractModel::valueAt(int i, int j, int role) const
{
    if ( i >= 0 && i < m_cache[0].size() )
    {
        return m_cache[j][i];
    }
    else if ( i == m_cache[0].size() )
    {
        return m_addRow[j];
    }
    else
        return QVariant();
}

QVariant AbstractModel::headerAt(int i) const
{
    return QVariant(i);
}

void AbstractModel::load_cache()
{

}

void AbstractModel::clear_cache()
{
    m_cache.clear();
}

int
AbstractModel::row_count() const
{
    return m_cache[0].size();

}

int AbstractModel::column_count() const
{
    return m_cache_size;
}

bool AbstractModel::editData(int i, int j, QVariant newValue)
{
    Q_UNUSED(i)
    Q_UNUSED(j)
    Q_UNUSED(newValue)
}

void AbstractModel::removeRow(int i)
{
    Q_UNUSED(i)
}

QStringList* AbstractModel::uniqueList(int i) const
{
    return NULL;
}

QAbstractItemDelegate* AbstractModel::itemDelegate(QObject* parent) const
{
    return new QItemDelegate(parent);
}

bool AbstractModel::isColumnEditable(int i) const
{
    return false;
}
