#include "MainWindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QTableView>
#include <QCompleter>
#include <QStringListModel>
#include <QStringList>

#include "model/RejestrTableModel.h"
#include "policestation/PoliceStationItemDelegate.h"
#include "staff/StaffModel.h"
#include "widgets/RejestrTableView.h"
#include "widgets/ScrollTableWidget.h"

#include "staff/StaffModel.h"
#include "policestation/PoliceStationModel.h"
#include "casein/CaseInModel.h"

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

        ui.menuDatabase->setEnabled(true);

        foreach (QAction *action, ui.menuDatabase->actions())
        {
            action->setEnabled(true);
        }

    }
    else
    {
        ui.actionConnect_to_a_database->setText( "Connect to a database" );

        ui.actionConnect_to_a_database->setIcon( QIcon( ":/icons/connect_ico.png" ) );

        ui.menuDatabase->setEnabled(false);

        foreach (QAction *action, ui.menuDatabase->actions())
        {
            action->setEnabled(false);
        }

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
	//setCentralWidget(0);

	RejestrTableView* tv = new RejestrTableView();

    tv->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked);

    model->setParent(tv);

    RejestrTableModel* tableModel = new RejestrTableModel( model, tv );

    tv->setItemDelegate( model->itemDelegate( tv ) );

    tv->setModel( tableModel );

	qDebug() << "set central widget";
	setCentralWidget(tv);
}

void MainWindow::showScrollTableView(AbstractScrollableModel *model)
{
	//qDebug() << "set central widget 0";
	//setCentralWidget(0);

	ScrollTableWidget* tv = new ScrollTableWidget( model );
	qDebug() << "set central widget";
	setCentralWidget(tv);
}


void MainWindow::on_actionStations_triggered()
{
    showTableView( The::policeStation() );
}

void MainWindow::on_actionStaff_triggered()
{
    showTableView( The::staff() );
}

void MainWindow::on_actionCase_In_triggered()
{
	showScrollTableView( The::caseIn() );
}
