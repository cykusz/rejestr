#ifndef CASEINMODEL_H
#define CASEINMODEL_H

#include "model/AbstractModel.h"

class CaseInModel : public AbstractModel
{
    Q_OBJECT
public:
    explicit CaseInModel(QObject *parent = 0);
    static CaseInModel* instance();
    ~CaseInModel();

private:
    static CaseInModel* m_instance;

};

namespace The
{
    CaseInModel* caseIn();
}

#endif // CASEINMODEL_H
