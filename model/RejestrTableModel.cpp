#include "RejestrTableModel.h"
#include <QDebug>

RejestrTableModel::RejestrTableModel(ModelInterface *model, QObject *parent) :
    QAbstractTableModel(parent)
    , m_model ( model )
{
    m_model->load_cache();
}

RejestrTableModel::~RejestrTableModel()
{
    qDebug() << "delete table model";
    //m_model->clear_cache();
}

int RejestrTableModel::rowCount(const QModelIndex &parent) const
{
    if ( parent.isValid() ) return 0;
    else
    {
        return m_model->row_count() + 1;
    }
}

int RejestrTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    else
    {
        return m_model->column_count();
    }
}

QVariant RejestrTableModel::data(const QModelIndex &index, int role) const
{
    if ( ! index.isValid() )
        return QVariant();

    if ( index.column() >= 0
        && index.column() < columnCount()
        && index.row() >= 0
        && index.row() <= rowCount()
        && ( role == Qt::DisplayRole || role == Qt::EditRole ) )
    {
        return m_model->valueAt( index.row(), index.column() );
    }
    else
        return QVariant();
}

QVariant RejestrTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    if ( orientation == Qt::Horizontal )
    {
        return m_model->headerAt( section );
    } else return QString("%1").arg( section );
}

Qt::ItemFlags RejestrTableModel::flags(const QModelIndex &index) const
{
    if ( ! index.isValid() )
        return Qt::ItemIsEnabled;

    if ( ! m_model->isColumnEditable( index.column() ) ) return QAbstractItemModel::flags(index);
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool RejestrTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (index.isValid() && role == Qt::EditRole)
    {
        if ( m_model->editData(index.row(), index.column(), value) )
        {
            beginInsertRows(QModelIndex(),0,0);
            endInsertRows();
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool RejestrTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    if ( rows == 1 )
    {
        beginRemoveRows(QModelIndex(), position, position);
        m_model->removeRow(position);
        endRemoveRows();

        return true;
    }
    return false;
}
