#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

#include "core/sql/SqlConnectionObserver.h"
#include "SqlConnectionController.h"

class MainWindow : public QMainWindow, public SqlConnectionObserver
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

    // sqlConnectionObserver methods
    virtual void sqlConnectionChanged(ConnectionState newConnectionState);

private:
    Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
