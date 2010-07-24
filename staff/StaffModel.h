#ifndef STAFFMODEL_H
#define STAFFMODEL_H

#include <QVector>
#include <QVariant>
#include <QAbstractItemDelegate>

#include "SqlConnectionController.h"

#include "model/AbstractModel.h"

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

    QAbstractItemDelegate* itemDelegate() const;

    QVariant headerAt(int i) const;

public slots:
    void load_cache();

private:
    static StaffModel* m_instance;

};

namespace The {
    StaffModel* staff();
}

#endif // STAFFMODEL_H
