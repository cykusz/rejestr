#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestWidget(QWidget *parent = 0);
    ~TestWidget();

signals:

public slots:

};

#endif // TESTWIDGET_H