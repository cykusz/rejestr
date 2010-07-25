#ifndef REJESTRTABLEMODEL_H
#define REJESTRTABLEMODEL_H

#include <QAbstractTableModel>

//#include "policestation/PoliceStationModel.h"
#include "model/ModelInterface.h"

#include "core/model/ModelObserver.h"

class RejestrTableModel : public QAbstractTableModel, public ModelObserver
{
    Q_OBJECT
public:
    explicit RejestrTableModel(ModelInterface* model, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex() ) const;
    int columnCount(const QModelIndex &parent = QModelIndex() ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    void modelRowsInsertBegan(int posStart, int posEnd);
    void modelRowsInsertFinished();
    void modelRowsDeleteBegan(int posStart, int posEnd);
    void modelRowsDeleteFinished();

    ~RejestrTableModel();

private:
    ModelInterface* m_model;

signals:

public slots:

};

#endif // REJESTRTABLEMODEL_H
