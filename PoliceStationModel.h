#ifndef POLICESTATIONMODEL_H
#define POLICESTATIONMODEL_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include "SqlConnectionController.h"

class PoliceStationModel : public QObject
{
    Q_OBJECT
public:
    static PoliceStationModel* instance();
    static int row_count();

    void editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    void load_cache();
    void clear_cache();

    QVariant valueAt( int i, int j ) const;

private:
    explicit PoliceStationModel(QObject *parent = 0);

    int m_row_count;

    QVector< QVector<QVariant> > m_cache;

    static PoliceStationModel* m_instance;
};

namespace The {
    PoliceStationModel* policeStation();
}

#endif // POLICESTATIONMODEL_H
