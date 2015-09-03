#ifndef BANKUI_H
#define BANKUI_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QMouseEvent>
#include <QTranslator>

#include "wstackedwidget.h"
#include "bars.h"

class BankUI : public QWidget
{
    Q_OBJECT

public:
    BankUI(QWidget *parent = 0);
    ~BankUI();
    void openUX();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void changeLanguage();
    void showMyAccountPage();
    void showAccountQueryPage();
    void showTransferPage();
    void shouCurrentFixPage();
    void showPaymentPage();
    void showAutoPayPage();
    void showCardApplyPage();
    void showCardActivatePage();
    void showCardRepayPage();
    void showCardLostPage();
    void showUserInfoPage();
    void showChangePwPage();
    void showSysMsgPage();
    void showAboutPage();
    void showWelcomePage();
    bool closeWindow();
    void openUX2();
    void openUX3();
    void openUX4();
    void openUX5();


private:
    QLabel *backgroundLabel;
    WTopbar *topbar;
    WNavbar *navbar;
    QLabel *logInfoLabel;
    QLabel *creditLabel;
    WStackedWidget *centerStack;
    QTimer *timer;
    bool isPressed;
    double openingOpacity;
    QPoint movePoint;
    void setTranslator();
    void initUI();
    void setConnections();
    void updateLanguage();

    QTranslator wTranslator;
    bool isChinese;
};

#endif // BANKUI_H
