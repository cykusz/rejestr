#include "RejestrTableView.h"

#include <QMessageBox>
#include <QHeaderView>

RejestrTableView::RejestrTableView(QWidget *parent) :
    QTableView(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ContiguousSelection);
    horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    horizontalHeader()->setCascadingSectionResizes(true);
    horizontalHeader()->setMovable(true);
}

void RejestrTableView::keyPressEvent(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_Delete )
    {
        QModelIndexList sr = selectionModel()->selectedRows();

        if ( sr.count() >= 1 )
        {
            QMessageBox msgBox;
            msgBox.setText("The rows are about to be deleted.");
            msgBox.setInformativeText("Do you want to delete these rows?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);

            int ret = msgBox.exec();
            if ( ret == QMessageBox::Yes )
            {
                for (int i = sr.count() - 1; i >= 0; i--)
                {
                    QModelIndex ind = sr.at(i);

                    model()->removeRow(ind.row(),QModelIndex());
                }
            }

        }
        else if ( selectionModel()->selectedIndexes().count() == 1 )
        {
             QTableView::keyPressEvent(event);
        }
    }
    else
    {
        QTableView::keyPressEvent(event);
    }


}
