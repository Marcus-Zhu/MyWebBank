#include "wstackedwidget.h"
#include <QDebug>

WStackedWidget::WStackedWidget(QWidget *parent):
    QStackedWidget(parent)
{
    myAccountPage = new MyAccountPage(this);
    myAccountPage->setObjectName("MyAccountPage");
    accountQueryPage = new AccountQueryPage(this);
    accountQueryPage->setObjectName("AccountQueryPage");
    transferPage = new TransferPage(this);
    transferPage->setObjectName("TransferPage");
    currentFixPage = new CurrentFixPage(this);
    currentFixPage->setObjectName("CurrentFixPage");
    paymentPage = new PaymentPage(this);
    paymentPage->setObjectName("PaymentPage");
    autoPayPage = new AutoPayPage(this);
    autoPayPage->setObjectName("AutoPayPage");
    cardApplyPage = new CardApplyPage(this);
    cardApplyPage->setObjectName("CardApplyPage");
    cardActivatePage = new CardActivatePage(this);
    cardActivatePage->setObjectName("CardActivatePage");
    cardRepayPage = new CardRepayPage(this);
    cardRepayPage->setObjectName("CardRepayPage");
    cardLostPage = new CardLostPage(this);
    cardLostPage->setObjectName("CardLostPage");
    userInfoPage = new UserInfoPage(this);
    userInfoPage->setObjectName("UserInfoPage");
    changePwPage = new ChangePwPage(this);
    changePwPage->setObjectName("ChangePwPage");
    sysMsgPage = new SysMsgPage(this);
    sysMsgPage->setObjectName("SysMsgPage");
    aboutPage = new AboutPage(this);
    aboutPage->setObjectName("AboutPage");

    this->addWidget(myAccountPage);
    this->addWidget(accountQueryPage);
    this->addWidget(transferPage);
    this->addWidget(currentFixPage);
    this->addWidget(paymentPage);
    this->addWidget(autoPayPage);
    this->addWidget(cardApplyPage);
    this->addWidget(cardActivatePage);
    this->addWidget(cardRepayPage);
    this->addWidget(cardLostPage);
    this->addWidget(userInfoPage);
    this->addWidget(changePwPage);
    this->addWidget(sysMsgPage);
    this->addWidget(aboutPage);
    this->setCurrentIndex(5);
}

void WStackedWidget::updateLanguage()
{
    myAccountPage->updateLanguage();
    accountQueryPage->updateLanguage();
    transferPage->updateLanguage();
    currentFixPage->updateLanguage();
    paymentPage->updateLanguage();
    autoPayPage->updateLanguage();
    cardApplyPage->updateLanguage();
    cardActivatePage->updateLanguage();
    cardRepayPage->updateLanguage();
    cardLostPage->updateLanguage();
    userInfoPage->updateLanguage();
    changePwPage->updateLanguage();
    sysMsgPage->updateLanguage();
    aboutPage->updateLanguage();
}

void WStackedWidget::showMyAccountPage()
{
    this->setCurrentIndex(0);
}
void WStackedWidget::showTransferPage()
{
    this->setCurrentIndex(1);
}
void WStackedWidget::showPaymentPage()
{
    this->setCurrentIndex(2);
}
void WStackedWidget::showCardApplyPage()
{
    this->setCurrentIndex(3);
}
