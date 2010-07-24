#ifndef POLICESTATIONMODEL_H
#define POLICESTATIONMODEL_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include "SqlConnectionController.h"
#include "model/AbstractModel.h"

class PoliceStationModel : public AbstractModel
{
    Q_OBJECT
public:
    explicit PoliceStationModel(QObject *parent = 0);
    static PoliceStationModel* instance();
    int column_count() const;

    bool editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    bool isColumnEditable(int i) const;

    QVariant headerAt(int i) const;

    QAbstractItemDelegate* itemDelegate() const;

    QStringList* uniqueList(int i) const;

    ~PoliceStationModel();

public slots:
    void load_cache();

private:
    QVector< QStringList* > m_uniqueLists;

    void updateUniqueLists();

    static PoliceStationModel* m_instance;
};

namespace The {
    PoliceStationModel* policeStation();
}

#endif // POLICESTATIONMODEL_H
