#include <QtGui/QApplication>
#include <QDebug>
#include <QStyleFactory>

#include "MainWindow.h"
#include "SqlConnectionController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
