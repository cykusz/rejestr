#ifndef CASEINADDWIDGET_H
#define CASEINADDWIDGET_H

#include "ui_CaseInAddWidget.h"

#include "casein/CaseInModel.h"

class CaseInAddWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaseInAddWidget(QWidget *parent = 0);

	inline void setModel(CaseInModel* model)
	{
		m_tableModel = model;
	}

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CaseInAddWidget ui;

	CaseInModel* m_tableModel;

private slots:
	void on_btnAdd_clicked();
};

#endif // CASEINADDWIDGET_H
