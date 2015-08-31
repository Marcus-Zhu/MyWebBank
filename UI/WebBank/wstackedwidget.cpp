#include "wstackedwidget.h"
#include <QDebug>

WStackedWidget::WStackedWidget(QWidget *parent):
    QStackedWidget(parent)
{
    myAccountPage = new MyAccountPage(this);
    myAccountPage->setObjectName("MyAccountPage");
    transferPage = new TransferPage(this);
    transferPage->setObjectName("TransferPage");

    this->addWidget(myAccountPage);
    this->addWidget(transferPage);
    this->setCurrentIndex(1);

}


void WStackedWidget::showMyAccountPage(){
    this->setCurrentIndex(0);
}
void WStackedWidget::showTransferPage(){
    this->setCurrentIndex(1);
}
void WStackedWidget::showPaymentPage(){
    this->setCurrentIndex(2);
}
void WStackedWidget::showCardApplyPage(){
    this->setCurrentIndex(3);
}
