#ifndef CASEINWIDGET_H
#define CASEINWIDGET_H

#include "ui_CaseInWidget.h"

#include "casein/CaseInModel.h"

class CaseInWidget : public QWidget
{
    Q_OBJECT

public:
	explicit CaseInWidget(CaseInModel* model, QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CaseInWidget ui;
};

#endif // CASEINWIDGET_H
