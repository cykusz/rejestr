#include "CaseInModel.h"


CaseInModel* CaseInModel::m_instance = 0;

namespace The
{
    CaseInModel* caseIn()
    {
        return CaseInModel::instance();
    }
}

CaseInModel::CaseInModel(QObject *parent) :
    AbstractModel(parent)
{
    m_cache_size = 9;
}

CaseInModel::~CaseInModel()
{
    m_instance = 0;
}

CaseInModel* CaseInModel::instance()
{
    if ( m_instance == 0 )
        m_instance = new CaseInModel();

    return m_instance;
}
