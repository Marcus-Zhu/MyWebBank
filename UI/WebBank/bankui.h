#ifndef BANKUI_H
#define BANKUI_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

#include "wstackedwidget.h"

class BankUI : public QWidget
{
    Q_OBJECT

public:
    BankUI(QWidget *parent = 0);
    ~BankUI();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void popQuery();
    void popTransfer();
    void popPayment();
    void popCCard();

private:
    QLabel *backgroundLabel;
    QPushButton *userBtn;
    QPushButton *settingBtn;
    QPushButton *minBtn;
    QPushButton *closeBtn;
    QPushButton *queryBtn;
    QPushButton *transferBtn;
    QPushButton *paymentBtn;
    QPushButton *ccardBtn;
    QLabel *queryLabel;
    QLabel *transferLabel;
    QLabel *paymentLabel;
    QLabel *ccardLabel;
    QLabel *currentPosLabel;
    QLabel *logInfoLabel;
    QLabel *creditLabel;
    WStackedWidget w;
    bool isPressed;
    QPoint movePoint;
};

#endif // BANKUI_H
