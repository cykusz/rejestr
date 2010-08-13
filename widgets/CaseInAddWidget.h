#ifndef CASEINADDWIDGET_H
#define CASEINADDWIDGET_H

#include "ui_CaseInAddWidget.h"

class CaseInAddWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaseInAddWidget(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CaseInAddWidget ui;

private slots:
	void on_btnAdd_clicked();
};

#endif // CASEINADDWIDGET_H
