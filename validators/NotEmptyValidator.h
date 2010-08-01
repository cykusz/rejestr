#ifndef NOTEMPTYVALIDATOR_H
#define NOTEMPTYVALIDATOR_H

#include <QValidator>

class NotEmptyValidator : public QValidator
{
    Q_OBJECT
public:
    explicit NotEmptyValidator(QObject *parent = 0);

	State validate ( QString & input, int & pos ) const;

};

#endif // NOTEMPTYVALIDATOR_H
