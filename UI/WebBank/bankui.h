#ifndef BANKUI_H
#define BANKUI_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QTranslator>

#include "wstackedwidget.h"
#include "qmenubutton.h"

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
    void changeLanguage();

private:
    QLabel *backgroundLabel;
    QMenuButton *userBtn;
    QMenuButton *settingBtn;
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
    WStackedWidget *centerStack;
    bool isPressed;
    QPoint movePoint;
    void setTranslator();
    void setStyle();
    void initUI();
    void setConnections();

    QTranslator wTranslator;
    bool isChinese;
};

#endif // BANKUI_H
