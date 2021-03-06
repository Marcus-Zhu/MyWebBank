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

enum COLOR {blue, green, orange, purple, red, yellow};

class BankUI : public QWidget
{
    Q_OBJECT

public:
    BankUI(QWidget *parent = 0, int trans = 0);
    void openUX();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void changeLanguage();
    void changeColor();
    void changeToBlue();
    void changeToGreen();
    void changeToOrange();
    void changeToPurple();
    void changeToRed();
    void changeToYellow();
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
    void showCurrencyPage();
    void showPlotPage();
    bool closeWindow();
    bool restartColor();
    bool restartWindow();
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
    void setTranslator(int i);
    void initUI();
    void updateLanguage();
    bool closeColor();

    QTranslator wTranslator;
    bool isChinese;//record the current language
    COLOR color;//record the current color
};

#endif // BANKUI_H
