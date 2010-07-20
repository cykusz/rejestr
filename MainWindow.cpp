#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        SqlConnectionObserver(SqlConnectionController::instance())
{
    ui.setupUi(this);
}

void
MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

void
MainWindow::sqlConnectionChanged( ConnectionState newConnectionState )
{

}
