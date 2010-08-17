#ifndef SCROLLTABLEWIDGET_H
#define SCROLLTABLEWIDGET_H

#include "ui_ScrollTableWidget.h"

#include "model/AbstractScrollableModel.h"

class ScrollTableWidget : public QWidget
{
    Q_OBJECT

public:
	explicit ScrollTableWidget(QWidget *parent = 0);

	void setScrollableModel(AbstractScrollableModel * model);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ScrollTableWidget ui;

	void setLeftArowsEnabled(bool enabled);
	void setRightArowsEnabled(bool enabled);


	AbstractScrollableModel* m_tableModel;

private slots:
	void on_spinPage_valueChanged(int );
	void on_spinPage_editingFinished();
	void on_spinOnPage_valueChanged(int );
	void on_spinOnPage_editingFinished();
	void on_btnLastPage_clicked();
	void on_btnNextPage_clicked();
	void on_btnPrevPage_clicked();
	void on_btnFirstPage_clicked();

	void onPageChanged();
	void updateArrows();
};

#endif // SCROLLTABLEWIDGET_H
