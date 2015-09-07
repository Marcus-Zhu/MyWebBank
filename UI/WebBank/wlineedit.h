#ifndef WLINEEDIT_H
#define WLINEEDIT_H

#include <QObject>
#include <QLineEdit>
#include <QMouseEvent>

class WLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit WLineEdit(QWidget *parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent *e);
signals:
    void Wclicked();
};

#endif // WLINEEDIT_H

