#ifndef STAFFMODEL_H
#define STAFFMODEL_H

#include <QVector>
#include <QVariant>
#include <QAbstractItemDelegate>

#include "SqlConnectionController.h"

#include "model/AbstractModel.h"
#include "model/AbstractListModel.h"

class StaffModel : public AbstractModel
{
    Q_OBJECT
public:
    explicit StaffModel(QObject *parent = 0);
    static StaffModel* instance();
    ~StaffModel();

    bool editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    bool isColumnEditable(int i) const;

    QAbstractItemDelegate* itemDelegate(QObject* parent = 0) const;

    QVariant headerAt(int i) const;

public slots:
    void load_cache();

private:
    static StaffModel* m_instance;

};

class StaffListModel : public AbstractListModel
{
    Q_OBJECT

public:
    explicit StaffListModel(QObject* parent = 0);
    static StaffListModel* instance();

private:
    static StaffListModel* m_instance;

    QVector< QVector<QVariant> > m_cache;

    void initModel();

};

namespace The {
    StaffModel* staff();
    StaffListModel* staffList();
}

#endif // STAFFMODEL_H
