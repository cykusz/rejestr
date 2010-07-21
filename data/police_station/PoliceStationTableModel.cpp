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
        && role == Qt::DisplayRole )
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
