#ifndef ABSTRACTSCROLLABLEMODEL_H
#define ABSTRACTSCROLLABLEMODEL_H

#include "model/AbstractModel.h"

class AbstractScrollableModel : public AbstractModel
{
    Q_OBJECT
public:
    explicit AbstractScrollableModel(QObject *parent = 0);

	inline void setOnPage(const int& onp)
	{
		if (onp > 0)
		{
			m_onPage = onp;
			updatePageCount();

			if (m_page >= m_pageCount)
				setPage(pageCount() - 1);
			else
			{
				load_cache();
				emit pageChanged();
			}

		}
	}

	inline const int& onPage() const
	{
		return m_onPage;
	}

	inline const int& page() const
	{
		return m_page;
	}

	inline const int& pageCount() const
	{
		return m_pageCount;
	}

	virtual inline void nextPage(bool forceChange = false)
	{
		if ( m_page < m_pageCount - 1 )
		{
			setPage( page() + 1, forceChange );
		}
	}

	virtual inline void prevPage(bool forceChange = false)
	{
		if ( m_page > 0 )
		{
			setPage( page() - 1, forceChange );
		}
	}

	virtual inline void lastPage(bool forceChange = false)
	{
		setPage( pageCount() - 1, forceChange );
	}

	virtual inline void firstPage(bool forceChange = false)
	{
		setPage( 0, forceChange );
	}

	virtual inline void setPage( const int& p, bool forceChange = false )
	{
		if ( ( p >= 0 && p < m_pageCount && p != m_page ) || forceChange )
		{
			m_page = p;

			load_cache();
		}

		emit pageChanged();
	}

protected:
	inline void setPageCount(const int& p)
	{
		m_pageCount = p;

		if ( m_pageCount >= m_page )
		{
			if (m_page >= m_pageCount)
				setPage(pageCount() - 1);

		}
	}

	virtual void updatePageCount() = 0;

	int m_onPage;
	int m_page;
	int m_pageCount;

signals:
	void pageChanged();

};

#endif // ABSTRACTSCROLLABLEMODEL_H
