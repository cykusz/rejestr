#ifndef POLICESTATIONITEMDELEGATE_H
#define POLICESTATIONITEMDELEGATE_H

#include <QItemDelegate>

#include "PoliceStationModel.h"

class PoliceStationItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PoliceStationItemDelegate(PoliceStationModel* model, QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    PoliceStationModel* m_policeModel;

};

#endif // POLICESTATIONITEMDELEGATE_H
