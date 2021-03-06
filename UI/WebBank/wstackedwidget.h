#ifndef WSTACKEDWIDGET_H
#define WSTACKEDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include "pages.h"

class WStackedWidget : public QStackedWidget
{
public:
    WStackedWidget(QWidget *parent = 0);
    void updateLanguage();
    MyAccountPage *myAccountPage;
    AccountQueryPage *accountQueryPage;
    TransferPage *transferPage;
    CurrentFixPage *currentFixPage;
    PaymentPage *paymentPage;
    AutoPayPage *autoPayPage;
    CardApplyPage *cardApplyPage;
    CardActivatePage *cardActivatePage;
    CardRepayPage *cardRepayPage;
    CardLostPage *cardLostPage;
    UserInfoPage *userInfoPage;
    ChangePwPage *changePwPage;
    SysMsgPage *sysMsgPage;
    AboutPage *aboutPage;
    WelcomePage *welcomePage;
    PlotPage *plotPage;
    CurrencyPage *currencyPage;
};

#endif // WSTACKEDWIDGET_H
