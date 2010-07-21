#include "MainWindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QTableView>

#include "data/police_station/PoliceStationTableModel.h"
#include "widgets/RejestrTableView.h"
#include "TestWidget.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , SqlConnectionObserver( The::sqlConnectionController() )
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
MainWindow::sqlConnectionChanged( SqlConnectionState newConnectionState )
{
    if ( newConnectionState == Connected )
    {
        ui.actionConnect_to_a_database->setText( "Disconnect from database" );

        ui.actionConnect_to_a_database->setIcon( QIcon( ":/icons/disconnect_ico.png" ) );

        RejestrTableView* tv = new RejestrTableView();
        PoliceStationTableModel* model = new PoliceStationTableModel();

        tv->setModel(model);

        tv->setSelectionBehavior(QAbstractItemView::SelectItems);
        tv->setSelectionMode(QAbstractItemView::ContiguousSelection);

        setCentralWidget(tv);

        connect(tv, SIGNAL(destroyed()),model,SLOT(deleteLater()));

    }
    else
    {
        ui.actionConnect_to_a_database->setText( "Connect to a database" );

        ui.actionConnect_to_a_database->setIcon( QIcon( ":/icons/connect_ico.png" ) );

        setCentralWidget(0);
    }
}

void
MainWindow::on_actionConnect_to_a_database_triggered()
{
    if ( ! The::sqlConnectionController()->isConnected() )
    {

        QFileDialog fileDialog(this);
        fileDialog.setWindowTitle("Select database file");
        fileDialog.setFileMode(QFileDialog::AnyFile);
        fileDialog.setNameFilter("SQLite files (*.sqlite)");
        fileDialog.setViewMode(QFileDialog::Detail);

        if ( fileDialog.exec() )
        {
            QString file = fileDialog.selectedFiles().at(0);

            if ( ! file.isEmpty() )
            {
                The::sqlConnectionController()->connectToDatabase(file);
            }
        }
    }
    else
    {
        The::sqlConnectionController()->disconnectFromDatabase();
    }
}
