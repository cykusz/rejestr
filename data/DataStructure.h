#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QObject>

class DataStructure : public QObject
{
    Q_OBJECT
public:
    explicit DataStructure(QObject *parent = 0);

    static void initStructure();

};

#endif // DATASTRUCTURE_H
