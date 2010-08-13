#include "ScrollTableWidget.h"
#include "model/RejestrTableModel.h"

#include <QDebug>

ScrollTableWidget::ScrollTableWidget(AbstractScrollableModel * model, QWidget *parent) :
	QWidget(parent)
	,m_tableModel(model)
{
    ui.setupUi(this);

	ui.tableView->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked);

	m_tableModel->setParent(this);

	RejestrTableModel* tableModel = new RejestrTableModel( m_tableModel, this );

	ui.tableView->setItemDelegate( m_tableModel->itemDelegate( this ) );

	ui.tableView->setModel( tableModel );

	connect(m_tableModel, SIGNAL(pageChanged()),this,SLOT(onPageChanged()));

	m_tableModel->setOnPage(ui.spinOnPage->value());
}

void ScrollTableWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

void ScrollTableWidget::onPageChanged()
{
	qDebug () << "set spin page value:" << m_tableModel->page()+1 << m_tableModel->page();

	ui.spinPage->setMaximum(m_tableModel->pageCount());
	ui.spinPage->setValue(m_tableModel->page()+1);

	ui.lblPageInfo->setText("Page: " + QString::number(m_tableModel->page()+1) + " / " + QString::number(m_tableModel->pageCount()));
}

void ScrollTableWidget::on_btnFirstPage_clicked()
{
	m_tableModel->firstPage();
}

void ScrollTableWidget::on_btnPrevPage_clicked()
{
	m_tableModel->prevPage();
}

void ScrollTableWidget::on_btnNextPage_clicked()
{
	m_tableModel->nextPage();
}

void ScrollTableWidget::on_btnLastPage_clicked()
{
	m_tableModel->lastPage();
}

void ScrollTableWidget::on_spinOnPage_editingFinished()
{
	m_tableModel->setOnPage(ui.spinOnPage->value());
}

void ScrollTableWidget::on_spinOnPage_valueChanged(int v)
{
	m_tableModel->setOnPage(v);
}

void ScrollTableWidget::on_spinPage_editingFinished()
{
	qDebug() << "spinPage" << ui.spinPage->value()-1;
	m_tableModel->setPage(ui.spinPage->value()-1);
}

void ScrollTableWidget::on_spinPage_valueChanged(int )
{
	qDebug() << "spinPage" << ui.spinPage->value()-1;
	m_tableModel->setPage(ui.spinPage->value()-1);
}
