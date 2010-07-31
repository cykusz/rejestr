#ifndef ABSTRACTLISTMODEL_H
#define ABSTRACTLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>

class AbstractListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AbstractListModel(QObject *parent = 0);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex() ) const;


protected:

    QVector< QVector<QVariant> > m_cache;

    virtual void initModel();

};

#endif // ABSTRACTLISTMODEL_H
