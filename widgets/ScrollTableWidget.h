#ifndef SCROLLTABLEWIDGET_H
#define SCROLLTABLEWIDGET_H

#include "ui_ScrollTableWidget.h"

class ScrollTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollTableWidget(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ScrollTableWidget ui;
};

#endif // SCROLLTABLEWIDGET_H
