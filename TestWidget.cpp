#include "TestWidget.h"
#include <QWidget>
#include <QDebug>

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "create test widget";
}

TestWidget::~TestWidget()
{
    qDebug() << "delete test widget";
}

