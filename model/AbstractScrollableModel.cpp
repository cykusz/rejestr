#include "AbstractScrollableModel.h"

AbstractScrollableModel::AbstractScrollableModel(QObject *parent) :
    AbstractModel(parent)
	, m_onPage ( 100 )
	, m_page ( 0 )
{
}
