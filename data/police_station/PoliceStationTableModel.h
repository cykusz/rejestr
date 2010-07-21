#ifndef POLICESTATIONTABLEMODEL_H
#define POLICESTATIONTABLEMODEL_H

#include <QAbstractTableModel>

#include "PoliceStationModel.h"

class PoliceStationTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PoliceStationTableModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex() ) const;
    int columnCount(const QModelIndex &parent = QModelIndex() ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

    ~PoliceStationTableModel();

private:
    PoliceStationModel* m_model;

signals:

public slots:

};

#endif // POLICESTATIONTABLEMODEL_H
