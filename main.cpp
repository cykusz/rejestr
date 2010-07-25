#include <QtGui/QApplication>
#include <QDebug>
#include <QStyleFactory>

#include "MainWindow.h"
#include "SqlConnectionController.h"

int main(int argc, char *argv[])
{
    //qDebug() << QStyleFactory::keys();
    //QApplication::setStyle("Plastique");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
