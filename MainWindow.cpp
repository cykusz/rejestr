#include "MainWindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QTableView>

#include "model/RejestrTableModel.h"
#include "model/delegates/PoliceStationItemDelegate.h"
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

        showTableView( The::policeStation() );

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

void MainWindow::showTableView(ModelInterface *model)
{
    RejestrTableView* tv = new RejestrTableView();

    RejestrTableModel* tableModel = new RejestrTableModel( model );

    PoliceStationItemDelegate *id = new PoliceStationItemDelegate(static_cast<PoliceStationModel*>(model));

    tv->setItemDelegate(id);

    tv->setModel( tableModel );

    setCentralWidget(tv);

    connect(tv, SIGNAL(destroyed()),model,SLOT(deleteLater()));
}
