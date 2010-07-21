#ifndef REJESTRTABLEVIEW_H
#define REJESTRTABLEVIEW_H

#include <QTableView>

#include <QKeyEvent>

class RejestrTableView : public QTableView
{
    Q_OBJECT
public:
    explicit RejestrTableView(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *event);

};

#endif // REJESTRTABLEVIEW_H
