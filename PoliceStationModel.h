#ifndef POLICESTATIONMODEL_H
#define POLICESTATIONMODEL_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include "SqlConnectionController.h"
#include "model/ModelInterface.h"

class PoliceStationModel : public ModelInterface
{
    Q_OBJECT
public:
    static PoliceStationModel* instance();
    int row_count() const;
    int column_count() const;

    bool editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    void load_cache();
    void clear_cache();

    bool isColumnEditable(int i) const;

    QVariant headerAt(int i) const;

    QVariant valueAt( int i, int j ) const;

    QStringList* uniqueList(int i) const;

    QAbstractItemDelegate* itemDelegate() const;

    ~PoliceStationModel();

private:
    explicit PoliceStationModel(QObject *parent = 0);

    int m_row_count;

    QVector< QVector<QVariant> > m_cache;
    QVector<QVariant> m_addRow;
    QVector< QStringList* > m_uniqueLists;

    void updateUniqueLists();

    static PoliceStationModel* m_instance;
};

namespace The {
    PoliceStationModel* policeStation();
}

#endif // POLICESTATIONMODEL_H
