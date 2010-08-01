#ifndef CASEINITEMDELEGATE_H
#define CASEINITEMDELEGATE_H

#include <QItemDelegate>

class CaseInItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CaseInItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // CASEINITEMDELEGATE_H
