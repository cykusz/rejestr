#ifndef CASEINMODEL_H
#define CASEINMODEL_H

#include "model/AbstractScrollableModel.h"

class CaseInModel : public AbstractScrollableModel
{
    Q_OBJECT
public:
    explicit CaseInModel(QObject *parent = 0);
    static CaseInModel* instance();
    ~CaseInModel();

    bool editData(int i, int j, QVariant newValue);
    void removeRow(int i);

    bool isColumnEditable(int i) const;

    QAbstractItemDelegate* itemDelegate(QObject* parent = 0) const;

    QVariant headerAt(int i) const;

	bool insertCase(QString datawej, QString he, QString jednostka, QString rsd, QString opis, QString przydzial, QString rodzaj, QString datazab, QString uwagi);

	static bool isHeUnique(QString he);

	inline const QString& lastError() const
	{
		return m_lastError;
	}

public slots:
    void load_cache();

private:
    static CaseInModel* m_instance;

	void updatePageCount();

    QVector< int > m_stationIds;
    QVector< int > m_staffIds;

	QString m_lastError;

};

namespace The
{
    CaseInModel* caseIn();
}

#endif // CASEINMODEL_H
