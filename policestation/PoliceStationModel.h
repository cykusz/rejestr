#ifndef POLICESTATIONMODEL_H
#define POLICESTATIONMODEL_H

#include <QVector>
#include <QVariant>
#include <QMap>
#include <QAbstractListModel>

#include "SqlConnectionController.h"
#include "model/AbstractModel.h"
#include "model/AbstractListModel.h"

class PoliceStationModel : public AbstractModel
{
    Q_OBJECT
public:
    explicit PoliceStationModel(QObject *parent = 0);
    static PoliceStationModel* instance();

    bool editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    bool isColumnEditable(int i) const;

    QVariant headerAt(int i) const;

    QAbstractItemDelegate* itemDelegate(QObject* parent = 0) const;

    QStringList* uniqueList(int i) const;

    ~PoliceStationModel();

public slots:
    void load_cache();

private:
    QVector< QStringList* > m_uniqueLists;

    void updateUniqueLists();

    static PoliceStationModel* m_instance;
};

class PoliceStationListModel : public AbstractListModel
{
    Q_OBJECT

public:
    explicit PoliceStationListModel(QObject* parent = 0);
    static PoliceStationListModel* instance();

private:
    static PoliceStationListModel* m_instance;

    QVector< QVector<QVariant> > m_cache;

    void initModel();

};

namespace The {
    PoliceStationModel* policeStation();
    PoliceStationListModel* policeStationList();
}

#endif // POLICESTATIONMODEL_H
