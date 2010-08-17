#include "widgets/CaseInWidget.h"

CaseInWidget::CaseInWidget(CaseInModel *model, QWidget *parent) :
    QWidget(parent){
    ui.setupUi(this);

	ui.scrollWidget->setScrollableModel(model);
	ui.addCaseWidget->setModel(model);
}

void CaseInWidget::changeEvent(QEvent *e)
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
