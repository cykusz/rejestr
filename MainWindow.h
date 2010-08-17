#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>

#include "ui_MainWindow.h"

#include "core/sql/SqlConnectionObserver.h"
#include "SqlConnectionController.h"
#include "model/ModelInterface.h"
#include "model/AbstractScrollableModel.h"

class MainWindow : public QMainWindow, public SqlConnectionObserver
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

    // sqlConnectionObserver methods
    void sqlConnectionChanged(SqlConnectionState newConnectionState);

private:
    Ui::MainWindow ui;

    void showTableView(ModelInterface* model);

private slots:
    void on_actionCase_In_triggered();
    void on_actionStaff_triggered();
    void on_actionStations_triggered();
    void on_actionConnect_to_a_database_triggered();

};

#endif // MAINWINDOW_H
