#include "CaseInAddWidget.h"

#include "staff/StaffModel.h"
#include "policestation/PoliceStationModel.h"
#include "casein/CaseInModel.h"

CaseInAddWidget::CaseInAddWidget(QWidget *parent) :
    QWidget(parent){
    ui.setupUi(this);

	ui.comboStaff->setModel( The::staffList() );
	ui.comboStation->setModel( The::policeStationList() );
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

	The::caseIn()->insertCase(datawej, he, jednostka, rsd, opis, przydzial, rodzaj, datazab, uwagi);
}
