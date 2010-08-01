#include "AbstractListModel.h"
#include <QDebug>

AbstractListModel::AbstractListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QVariant AbstractListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_cache[0].size())
            return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole )
    {
        return m_cache[1].at(index.row());
    }
    else if (role == Qt::UserRole)
    {
        return m_cache[0].at(index.row());
    } else
        return QVariant();
}

int AbstractListModel::rowCount(const QModelIndex& parent ) const
{
    if (parent.isValid()) return 0;
    else
        return m_cache[0].size();
}

/*bool AbstractListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < m_cache[0].size() && (role == Qt::EditRole || role == Qt::DisplayRole))
    {
        emit dataChanged(index,index);
        return true;

    }

    return false;
}*/

Qt::ItemFlags AbstractListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
