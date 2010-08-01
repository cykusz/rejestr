#ifndef CASEINMODEL_H
#define CASEINMODEL_H

#include "model/AbstractModel.h"

class CaseInModel : public AbstractModel
{
    Q_OBJECT
public:
    explicit CaseInModel(QObject *parent = 0);
    static CaseInModel* instance();
    ~CaseInModel();

    bool editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    bool isColumnEditable(int i) const;

    QAbstractItemDelegate* itemDelegate(QObject* parent = 0) const;

    QVariant headerAt(int i) const;

public slots:
    void load_cache();

private:
    static CaseInModel* m_instance;

    QVector< int > m_stationIds;
    QVector< int > m_staffIds;

};

namespace The
{
    CaseInModel* caseIn();
}

#endif // CASEINMODEL_H
