#include "PoliceStationTableModel.h"
#include <QDebug>

PoliceStationTableModel::PoliceStationTableModel(QObject *parent) :
    QAbstractTableModel(parent)
    , m_model ( The::policeStation() )
{
    m_model->load_cache();
}

PoliceStationTableModel::~PoliceStationTableModel()
{
    m_model->clear_cache();
}

int PoliceStationTableModel::rowCount(const QModelIndex &parent) const
{
    if ( parent.isValid() ) return 0;
    else
    {
        return m_model->row_count();
    }
}

int PoliceStationTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    else
    {
        return 2;
    }
}

QVariant PoliceStationTableModel::data(const QModelIndex &index, int role) const
{
    if ( ! index.isValid() )
        return QVariant();

    if ( index.column() >= 0
        && index.column() < columnCount()
        && index.row() >= 0
        && index.row() < rowCount()
        && ( role == Qt::DisplayRole || role == Qt::EditRole ) )
    {
        return m_model->valueAt( index.row(), index.column() + 1 );
    }
    else
        return QVariant();
}

QVariant PoliceStationTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    if ( orientation == Qt::Horizontal )
    {
        switch ( section )
        {
        case 0:
            return QString("Miasto");
        case 1:
            return QString("Jednostka");
        default:
            return QVariant();
        }
    } else return QString("%1").arg( m_model->valueAt( section, 0 ).toInt() );
}

Qt::ItemFlags PoliceStationTableModel::flags(const QModelIndex &index) const
{
    if ( ! index.isValid() )
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool PoliceStationTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        m_model->editData(index.row(), index.column()+1, value);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}
