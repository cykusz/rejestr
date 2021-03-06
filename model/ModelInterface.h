#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

#include <QObject>
#include <QAbstractItemDelegate>

#include "core/model/ModelObserver.h"

class ModelInterface : public ModelSubject
{
    Q_OBJECT
public:
    ModelInterface(QObject *parent = 0);

    virtual int row_count() const = 0;
    virtual int column_count() const = 0;

    virtual bool editData(int i, int j, QVariant newValue) = 0;
    virtual void removeRow(int i) = 0;

    virtual void load_cache() = 0;
    virtual void clear_cache() = 0;

    virtual bool isColumnEditable(int i) const = 0;

    virtual QVariant headerAt(int i) const = 0;

    virtual QVariant valueAt( int i, int j, int role = Qt::DisplayRole) const = 0;

    virtual QAbstractItemDelegate* itemDelegate(QObject* parent = 0) const = 0;
};

#endif // MODELINTERFACE_H
