#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

#include <QObject>

class ModelInterface : public QObject
{
    Q_OBJECT
public:
    explicit ModelInterface(QObject *parent = 0);

    virtual int row_count() const = 0;
    virtual int column_count() const = 0;

    virtual void editData(int i, int j, QVariant newValue) = 0;
    virtual void removeRow(int i) = 0;

    virtual void load_cache() = 0;
    virtual void clear_cache() = 0;

    virtual QVariant headerAt(int i) const = 0;

    virtual QVariant valueAt( int i, int j ) const = 0;

};

#endif // MODELINTERFACE_H
