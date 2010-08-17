#include "CaseInAddWidget.h"

#include "staff/StaffModel.h"
#include "policestation/PoliceStationModel.h"
#include "casein/CaseInModel.h"

#include <QDebug>
#include <QMessageBox>

CaseInAddWidget::CaseInAddWidget(QWidget *parent) :
    QWidget(parent){
    ui.setupUi(this);

	qDebug() << "set staff combo list";
	ui.comboStaff->setModel( The::staffList(this) );
	ui.comboStation->setModel( The::policeStationList(this) );
}

void CaseInAddWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

void CaseInAddWidget::on_btnAdd_clicked()
{
	QString datawej = ui.dateIn->date().toString("yyyy-MM-dd");
	QString he = ui.edHe->text();
	QString jednostka =  ui.comboStation->model()->index(
			ui.comboStation->currentIndex(),0)
				.data(Qt::UserRole)
				.toString();
	QString rsd = ui.edRsd->text();
	QString opis = ui.edDesc->text();
	QString przydzial = ui.comboStaff->model()->index(
			ui.comboStaff->currentIndex(),0)
				.data(Qt::UserRole)
				.toString();
	QString rodzaj = ui.comboType->currentText();
	QString datazab = ui.dateProtect->date().toString("yyyy-MM-dd");
	QString uwagi = ui.edNotice->text();

	if ( ! The::caseIn()->insertCase(datawej, he, jednostka, rsd, opis, przydzial, rodzaj, datazab, uwagi))
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText( The::caseIn()->lastError() );
		msgBox.exec();
	}
}
