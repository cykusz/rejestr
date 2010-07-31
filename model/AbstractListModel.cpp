#include "AbstractListModel.h"

AbstractListModel::AbstractListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    initModel();
}

QVariant AbstractListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_cache[1].at(index.row());
    }
    else if (role == Qt::UserRole)
    {
        return m_cache[0].at(index.row());
    }
}

int AbstractListModel::rowCount(const QModelIndex& ) const
{

    return m_cache[0].size();
}

void AbstractListModel::initModel()
{
}
