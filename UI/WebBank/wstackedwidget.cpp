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

    this->addWidget(myAccountPage);
    this->addWidget(accountQueryPage);
    this->addWidget(transferPage);
    this->addWidget(currentFixPage);
    this->addWidget(paymentPage);
    this->addWidget(autoPayPage);
    this->setCurrentIndex(5);
}

void WStackedWidget::updateLanguage()
{
    myAccountPage->updateLanguage();
    accountQueryPage->updateLanguage();
    transferPage->updateLanguage();
    currentFixPage->updateLanguage();
    paymentPage->updateLanguage();
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
