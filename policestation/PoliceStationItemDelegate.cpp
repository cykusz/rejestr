#include "PoliceStationItemDelegate.h"

#include <QLineEdit>
#include <QCompleter>
#include <QDebug>

PoliceStationItemDelegate::PoliceStationItemDelegate(PoliceStationModel *model, QObject *parent) :
    QItemDelegate(parent)
    , m_policeModel( model )
{
}

QWidget *PoliceStationItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* editor = new QLineEdit(parent);
    editor->setFrame(false);

    QCompleter* completer = new QCompleter( *m_policeModel->uniqueList( index.column() ),parent );
    completer->setCompletionMode( QCompleter::PopupCompletion );
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    editor->setCompleter(completer);


    return editor;
}

void PoliceStationItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index,Qt::EditRole).toString();
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(value);
}

void PoliceStationItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text();

    model->setData(index,value, Qt::EditRole);
}

void PoliceStationItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
