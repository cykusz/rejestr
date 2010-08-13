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

    virtual int row_count() const;

    bool editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    bool isColumnEditable(int i) const;

    QAbstractItemDelegate* itemDelegate(QObject* parent = 0) const;

    QVariant headerAt(int i) const;

	static QString nameSurnameByRowId(QString rowid);

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
	static StaffListModel* instance(QObject *parent = 0);
	~StaffListModel();

private:
    static StaffListModel* m_instance;

    void initModel();

};

namespace The {
    StaffModel* staff();
	StaffListModel* staffList(QObject *parent = 0);
}

#endif // STAFFMODEL_H
