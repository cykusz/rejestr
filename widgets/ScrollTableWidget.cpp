#include "ScrollTableWidget.h"
#include "model/RejestrTableModel.h"

#include <QDebug>

ScrollTableWidget::ScrollTableWidget(QWidget *parent) :
	QWidget(parent)
	, m_tableModel(NULL)
{
	ui.setupUi(this);
}

void ScrollTableWidget::setScrollableModel(AbstractScrollableModel *model)
{
	m_tableModel = model;

	ui.tableView->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked);

	m_tableModel->setParent(this);

	RejestrTableModel* tableModel = new RejestrTableModel( m_tableModel, this );

	ui.tableView->setItemDelegate( m_tableModel->itemDelegate( this ) );

	ui.tableView->setModel( tableModel );

	connect(m_tableModel, SIGNAL(pageChanged()),this,SLOT(onPageChanged()));
	connect(m_tableModel, SIGNAL(recordInserted()),ui.tableView, SLOT(scrollToBottom()));

	m_tableModel->setOnPage(ui.spinOnPage->value());

	onPageChanged();
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
	ui.spinPage->setMaximum(m_tableModel->pageCount());
	ui.spinPage->setValue(m_tableModel->page()+1);

	ui.lblPageInfo->setText("Page: " + QString::number(m_tableModel->page()+1) + " / " + QString::number(m_tableModel->pageCount()));

	updateArrows();
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
	m_tableModel->setPage(ui.spinPage->value()-1);
}

void ScrollTableWidget::on_spinPage_valueChanged(int )
{
	m_tableModel->setPage(ui.spinPage->value()-1);
}

void ScrollTableWidget::setLeftArowsEnabled(bool enabled)
{
	ui.btnFirstPage->setEnabled(enabled);
	ui.btnPrevPage->setEnabled(enabled);
}

void ScrollTableWidget::setRightArowsEnabled(bool enabled)
{
	ui.btnLastPage->setEnabled(enabled);
	ui.btnNextPage->setEnabled(enabled);
}

void ScrollTableWidget::updateArrows()
{
	if ( m_tableModel->page()==0 )
	{
		setLeftArowsEnabled( false );
	}
	else
		setLeftArowsEnabled( true );

	if ( m_tableModel->page() == m_tableModel->pageCount()-1 )
	{
		setRightArowsEnabled( false );
	}
	else
		setRightArowsEnabled( true );
}
