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
public slots:
    void showMyAccountPage();
    void showTransferPage();
    void showPaymentPage();
    void showCardApplyPage();
private:
    MyAccountPage *myAccountPage;
    TransferPage *transferPage;
};

#endif // WSTACKEDWIDGET_H
