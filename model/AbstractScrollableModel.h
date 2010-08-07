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

	virtual inline void nextPage()
	{
		if ( m_page < m_pageCount - 1 )
		{
			setPage( page() + 1 );
		}
	}

	virtual inline void prevPage()
	{
		if ( m_page > 0 )
		{
			setPage( page() - 1 );
		}
	}

	virtual inline void lastPage()
	{
		setPage( pageCount() - 1 );
	}

	virtual inline void firstPage()
	{
		setPage( 0 );
	}

	virtual inline void setPage( const int& p )
	{
		if (p >= 0 && p < m_pageCount && p != m_page)
		{
			m_page = p;
			emit pageChanged();
			load_cache();
		}
	}

protected:
	inline void setPageCount(const int& p)
	{
		m_pageCount = p;
	}

	virtual void updatePageCount() = 0;

	int m_onPage;
	int m_page;
	int m_pageCount;

signals:
	void pageChanged();

};

#endif // ABSTRACTSCROLLABLEMODEL_H
