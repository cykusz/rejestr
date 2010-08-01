#include "CaseInItemDelegate.h"

#include "staff/StaffModel.h"
#include "policestation/PoliceStationModel.h"

#include <QDebug>

#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>

CaseInItemDelegate::CaseInItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *CaseInItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget* editor = NULL;
    if (index.column() == 1 || index.column() == 8)
    {
        editor = new QDateEdit(parent);
        static_cast<QDateEdit*>(editor)->setCalendarPopup(true);
		static_cast<QDateEdit*>(editor)->setDisplayFormat("dd.MM.yyyy");
        static_cast<QDateEdit*>(editor)->setFrame(false);
    }
	else if (index.column()==6 || index.column()==3)
    {
        editor = new QComboBox(parent);
		if (index.column()==3)
		{
			static_cast<QComboBox*>(editor)->setModel(The::policeStationList());
		} else
		{
			static_cast<QComboBox*>(editor)->setModel(The::staffList());
		}

		static_cast<QComboBox*>(editor)->setEditable(true);
        static_cast<QComboBox*>(editor)->setFrame(false);
    }
    else
    {
        editor = new QLineEdit(parent);
        static_cast<QLineEdit*>(editor)->setFrame(false);
    }


    return editor;
}

void CaseInItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    if (index.column()==1 || index.column() == 8)
    {
		QString dateStr = index.model()->data(index,Qt::EditRole).toString();
		QDate date = QDate::fromString(dateStr,"dd.MM.yyyy");
        QDateEdit* dateEdit = static_cast<QDateEdit*>(editor);
		dateEdit->setDate(date);
    }
	else if (index.column()==6 || index.column()==3)
    {
        QComboBox* comboEdit = static_cast<QComboBox*>(editor);
        QString value = index.model()->data(index,Qt::DisplayRole).toString();
        comboEdit->setEditText(value);
		comboEdit->setCurrentIndex(comboEdit->findText(value));
    }
    else
    {
        QString value = index.model()->data(index,Qt::EditRole).toString();

        QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(value);
    }


}

void CaseInItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column()==1 || index.column()==8)
    {
        QDateEdit* dateEdit = static_cast<QDateEdit*>(editor);
		QString value = dateEdit->date().toString("yyyy-MM-dd");

        model->setData(index,value, Qt::EditRole);
    }
	else if (index.column()==6 || index.column()==3)
    {
        QComboBox* comboEdit = static_cast<QComboBox*>(editor);
		int value = comboEdit->model()->index(
				comboEdit->currentIndex(),0)
					.data(Qt::UserRole)
					.toInt();

        model->setData(index,value, Qt::EditRole);
    }
    else
    {
        QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
        QString value = lineEdit->text();

        model->setData(index,value, Qt::EditRole);
    }

}

void CaseInItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
