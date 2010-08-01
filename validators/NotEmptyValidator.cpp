#include "NotEmptyValidator.h"

NotEmptyValidator::NotEmptyValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State NotEmptyValidator::validate(QString &input, int &pos) const
{
	if (input == "zad") return QValidator::Invalid;
	else return QValidator::Acceptable;
}
