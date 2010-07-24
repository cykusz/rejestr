#include "StaffItemDelegate.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QApplication>
#include <QWidget>
#include <QStyle>
#include <QDebug>

StaffItemDelegate::StaffItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void StaffItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.column() > 3)
    {
        QStyleOptionButton checkboxstyle;
        QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);
        checkboxstyle.rect = option.rect;
        checkboxstyle.rect.setLeft(option.rect.x() +
                option.rect.width()/2 - checkbox_rect.width()/2);

        if (index.model()->data(index,Qt::DisplayRole) == "1")
        {
            checkboxstyle.state = QStyle::State_On | QStyle::State_Enabled;
        }
        else
        {
            checkboxstyle.state = QStyle::State_Off | QStyle::State_Enabled;
        }
        QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                            &checkboxstyle, painter);
    } else
    {
        QItemDelegate::paint(painter,option,index);
    }
}

QWidget *StaffItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
    QWidget* editor = NULL;
    if (index.column() > 3)
    {
        editor = new QCheckBox(parent);

    } else {
        editor = new QLineEdit(parent);
        static_cast<QLineEdit*>(editor)->setFrame(false);
    }


    return editor;
}

void StaffItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index,Qt::EditRole).toString();
    if (index.column() > 3)
    {
        QCheckBox* checkbox = static_cast<QCheckBox*>(editor);

        checkbox->setChecked((value=="0")?false:true);
    } else {
        QLineEdit* line = static_cast<QLineEdit*>(editor);


        line->setText(value);
    }


}

void StaffItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QString value = "";
    if (index.column() > 3)
    {
        QCheckBox* checkbox = static_cast<QCheckBox*>(editor);
        value = (checkbox->isChecked())?"1":"0";
    }
    else
    {
        QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
        value = lineEdit->text();
    }

    model->setData(index,value, Qt::EditRole);
}

void StaffItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.column() > 3)
    {
        QStyleOptionButton checkboxstyle;
        QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);
        QRect r = option.rect;

        r.setLeft(r.x() +
                  r.width()/2 - checkbox_rect.width()/2);
        editor->setGeometry(r);

    }
    else
    {
        editor->setGeometry(option.rect);
    }

}
