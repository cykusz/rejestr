#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include <model/ModelInterface.h>

class AbstractModel : public ModelInterface
{
    Q_OBJECT
public:
    explicit AbstractModel(QObject *parent = 0);

    virtual int row_count() const;
    virtual int column_count() const;

    virtual bool editData(int i, int j, QVariant newValue);
    virtual void removeRow(int i);

    virtual bool isColumnEditable(int i) const;

    virtual QVariant valueAt( int i, int j ) const;
    virtual QVariant headerAt(int i) const;

    virtual QStringList* uniqueList(int i) const;

    virtual QAbstractItemDelegate* itemDelegate() const;

public slots:
    virtual void load_cache();
    virtual void clear_cache();


protected:
    int m_cache_size;
    int m_row_count;

    QVector< QVector<QVariant> > m_cache;
    QVector<QVariant> m_addRow;
};

#endif // ABSTRACTMODEL_H
