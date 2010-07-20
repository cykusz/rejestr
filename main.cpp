#include <QtGui/QApplication>
#include "MainWindow.h"

#include "SqlConnectionController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    SqlConnectionController* inst = SqlConnectionController::instance();

    //inst->run_test();

    return a.exec();
}
