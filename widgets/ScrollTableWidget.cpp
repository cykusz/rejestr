#include "ScrollTableWidget.h"

ScrollTableWidget::ScrollTableWidget(QWidget *parent) :
    QWidget(parent){
    ui.setupUi(this);
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
