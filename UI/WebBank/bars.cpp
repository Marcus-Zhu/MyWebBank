#include <QDebug>
#include <QPoint>

#include "bars.h"

WTopbar::WTopbar(QWidget *parent) : QWidget(parent)
{
    topbarLabel = new QLabel("", this);

    userBtn = new QPushButton("", this);
    settingBtn = new QPushButton("", this);
    minBtn  = new QPushButton("", this);
    closeBtn = new QPushButton("", this);

    userMenu = new QMenu(this);
    settingMenu = new QMenu(this);
    personalInfoAction = new QAction(tr("Personal Info"), this);
    changepwAction = new QAction(tr("Change Password"), this);
    sysmsgAction = new QAction(tr("Message"), this);
    logoutAction = new QAction(tr("Log Out"), this);
    languageAction = new QAction(tr("Language"), this);
    aboutAction = new QAction(tr("About"), this);

    userMenu->addAction(personalInfoAction);
    userMenu->addAction(changepwAction);
    userMenu->addAction(sysmsgAction);
    userMenu->addAction(logoutAction);
    settingMenu->addAction(languageAction);
    settingMenu->addAction(aboutAction);

    topbarLabel->setObjectName("topbarLabel");

    userBtn->setObjectName("userBtn");
    settingBtn->setObjectName("settingBtn");
    minBtn->setObjectName("minBtn");
    closeBtn->setObjectName("closeBtn");

    userMenu->setObjectName("userBtnMenu");
    settingMenu->setObjectName("settingBtnMenu");
    personalInfoAction->setObjectName(("personalInfoAction"));
    changepwAction->setObjectName(("ChangepwAction"));
    sysmsgAction->setObjectName(("MessageAction"));
    logoutAction->setObjectName(("logoutAction"));
    languageAction->setObjectName(("languageAction"));
    aboutAction->setObjectName(("aboutAction"));

    topbarLabel->setGeometry(QRect(0, 0, 1000, 161));
    userBtn->setGeometry(QRect(856, 60, 48, 48));
    settingBtn->setGeometry(QRect(928, 60, 48, 48));
    minBtn->setGeometry(QRect(950, 12, 10, 15));
    closeBtn->setGeometry(QRect(975, 12, 10, 15));

    connect(userBtn, SIGNAL(clicked(bool)), this, SLOT(popUserMenu()));
    connect(settingBtn, SIGNAL(clicked(bool)), this, SLOT(popSettingMenu()));

    connect(closeBtn, SIGNAL(clicked(bool)), parent, SLOT(closeWindow()));
    connect(minBtn, SIGNAL(clicked(bool)), parent, SLOT(showMinimized()));

    connect(personalInfoAction, SIGNAL(triggered(bool)), parent, SLOT(showUserInfoPage()));
    connect(changepwAction, SIGNAL(triggered(bool)), parent, SLOT(showChangePwPage()));
    connect(sysmsgAction, SIGNAL(triggered(bool)), parent, SLOT(showSysMsgPage()));
    connect(logoutAction, SIGNAL(triggered(bool)), parent, SLOT(closeWindow()));
    connect(languageAction, SIGNAL(triggered(bool)), parent, SLOT(changeLanguage()));
    connect(aboutAction, SIGNAL(triggered(bool)), parent, SLOT(showAboutPage()));
}

void WTopbar::updateLanguage(){
    personalInfoAction->setText(tr("Personal Info"));
    changepwAction->setText(tr("Change Password"));
    sysmsgAction->setText(tr("Message"));
    logoutAction->setText(tr("Log Out"));
    languageAction->setText(tr("Language"));
    aboutAction->setText(tr("About"));
}

void WTopbar::popUserMenu()
{
    QPoint pos;
    pos.setX(pos.x() - userBtn->geometry().width());
    pos.setY(pos.y() + userBtn->geometry().height());
    userMenu->exec(userBtn->mapToGlobal(pos));
}
void WTopbar::popSettingMenu()
{
    QPoint pos;
    pos.setX(pos.x() - settingBtn->geometry().width());
    pos.setY(pos.y() + settingBtn->geometry().height());
    settingMenu->exec(settingBtn->mapToGlobal(pos));
}


WNavbar::WNavbar(QWidget *parent) : QWidget(parent)
{
    navbarLabel = new QLabel("", this);

    queryLabel = new QLabel(tr("My Account"), this);
    myAccountLabel = new QLabel(tr("My Account"), this);
    accountQueryLabel = new QLabel(tr("Account Query"), this);
    transferLabel = new QLabel(tr("Transfer"), this);
    currTransferLabel = new QLabel(tr("Current Transfer"), this);
    currentFixLabel = new QLabel(tr("Current-Fixed"), this);
    paymentLabel = new QLabel(tr("Payment"), this);
    ccardLabel = new QLabel(tr("Credit Card"), this);
    ccApplyLabel = new QLabel(tr("Apply"), this);
    ccActivateLabel = new QLabel(tr("Activate"), this);
    ccRepayLabel = new QLabel(tr("Repay"), this);
    ccLostLabel = new QLabel(tr("Loss Report"), this);

    queryBtn = new QPushButton("", this);
    myAccountBtn = new QPushButton("", this);
    accountQueryBtn = new QPushButton("", this);
    transferBtn = new QPushButton("", this);
    currTransferBtn = new QPushButton("", this);
    currentFixBtn = new QPushButton("", this);
    paymentBtn = new QPushButton("", this);
    ccardBtn = new QPushButton("", this);
    ccApplyBtn = new QPushButton("", this);
    ccActivateBtn = new QPushButton("", this);
    ccRepayBtn = new QPushButton("", this);
    ccLostBtn = new QPushButton("", this);

    navbarLabel->setObjectName("navbarLabel");

    queryLabel->setObjectName("queryLabel");
    myAccountLabel->setObjectName("myAccountLabel");
    accountQueryLabel->setObjectName("accountQueryLabel");
    transferLabel->setObjectName("transferLabel");
    currTransferLabel->setObjectName("currTransferLabel");
    currentFixLabel->setObjectName("currentFixLabel");
    paymentLabel->setObjectName("paymentLabel");
    ccardLabel->setObjectName("ccardLabel");
    ccApplyLabel->setObjectName("ccApplyLabel");
    ccActivateLabel->setObjectName("ccActivateLabel");
    ccRepayLabel->setObjectName("ccRepayLabel");
    ccLostLabel->setObjectName("ccLostLabel");

    queryBtn->setObjectName("queryBtn");
    myAccountBtn->setObjectName("myAccountBtn");
    accountQueryBtn->setObjectName("accountQueryBtn");
    transferBtn->setObjectName("transferBtn");
    currTransferBtn->setObjectName("currTransferBtn");
    currentFixBtn->setObjectName("currentFixBtn");
    paymentBtn->setObjectName("paymentBtn");
    ccardBtn->setObjectName("ccardBtn");
    ccApplyBtn->setObjectName("ccApplyBtn");
    ccActivateBtn->setObjectName("ccActivateBtn");
    ccRepayBtn->setObjectName("ccRepayBtn");
    ccLostBtn->setObjectName("ccLostBtn");

    navbarLabel->setGeometry(QRect(0, 0, 260, 751));

    queryBtn->setGeometry(QRect(5, 152, 237, 64));
    myAccountBtn->setGeometry(QRect(5, 216, 237, 36));
    accountQueryBtn->setGeometry(QRect(5, 252, 237, 36));
    transferBtn->setGeometry(QRect(5, 296, 237, 64));
    currTransferBtn->setGeometry(QRect(5, 360, 237, 36));
    currentFixBtn->setGeometry(QRect(5, 396, 237, 36));
    paymentBtn->setGeometry(QRect(5, 440, 237, 64));
    ccardBtn->setGeometry(QRect(5, 504, 237, 64));
    ccApplyBtn->setGeometry(QRect(5, 568, 237, 36));
    ccActivateBtn->setGeometry(QRect(5, 604, 237, 36));
    ccRepayBtn->setGeometry(QRect(5, 640, 237, 36));
    ccLostBtn->setGeometry(QRect(5, 676, 237, 36));

    queryLabel->setGeometry(QRect(0, 160, 237, 64));
    myAccountLabel->setGeometry(QRect(0, 216, 237, 36));
    accountQueryLabel->setGeometry(QRect(0, 252, 237, 36));
    transferLabel->setGeometry(QRect(0, 296, 237, 64));
    currTransferLabel->setGeometry(QRect(0, 360, 237, 36));
    currentFixLabel->setGeometry(QRect(0, 396, 237, 36));
    paymentLabel->setGeometry(QRect(0, 440, 237, 64));
    ccardLabel->setGeometry(QRect(0, 504, 237, 64));
    ccApplyLabel->setGeometry(QRect(0, 568, 237, 36));
    ccActivateLabel->setGeometry(QRect(0, 604, 237, 36));
    ccRepayLabel->setGeometry(QRect(0, 640, 237, 36));
    ccLostLabel->setGeometry(QRect(0, 676, 237, 36));

    connect(queryBtn, SIGNAL(clicked(bool)), this, SLOT(checkQuery()));
    connect(myAccountBtn, SIGNAL(clicked(bool)), this, SLOT(checkMyAccount()));
    connect(accountQueryBtn, SIGNAL(clicked(bool)), this, SLOT(checkAccountQuery()));
    connect(transferBtn, SIGNAL(clicked(bool)), this, SLOT(checkTransfer()));
    connect(currTransferBtn, SIGNAL(clicked(bool)), this, SLOT(checkCurrentTransfer()));
    connect(currentFixBtn, SIGNAL(clicked(bool)), this, SLOT(checkCurrentFix()));
    connect(paymentBtn, SIGNAL(clicked(bool)), this, SLOT(checkPayment()));
    connect(ccardBtn, SIGNAL(clicked(bool)), this, SLOT(checkCCard()));
    connect(ccApplyBtn, SIGNAL(clicked(bool)), this, SLOT(checkCCApply()));
    connect(ccActivateBtn, SIGNAL(clicked(bool)), this, SLOT(checkCCActivate()));
    connect(ccRepayBtn, SIGNAL(clicked(bool)), this, SLOT(checkCCRepay()));
    connect(ccLostBtn, SIGNAL(clicked(bool)), this, SLOT(checkCCLost()));

    connect(queryBtn, SIGNAL(clicked(bool)), parent, SLOT(showMyAccountPage()));
    connect(myAccountBtn, SIGNAL(clicked(bool)), parent, SLOT(showMyAccountPage()));
    connect(accountQueryBtn, SIGNAL(clicked(bool)), parent, SLOT(showAccountQueryPage()));
    connect(transferBtn, SIGNAL(clicked(bool)), parent, SLOT(showTransferPage()));
    connect(currTransferBtn, SIGNAL(clicked(bool)), parent, SLOT(showTransferPage()));
    connect(currentFixBtn, SIGNAL(clicked(bool)), parent, SLOT(shouCurrentFixPage()));
    connect(paymentBtn, SIGNAL(clicked(bool)), parent, SLOT(showPaymentPage()));
    connect(ccardBtn, SIGNAL(clicked(bool)), parent, SLOT(showCardApplyPage()));
    connect(ccApplyBtn, SIGNAL(clicked(bool)), parent, SLOT(showCardApplyPage()));
    connect(ccActivateBtn, SIGNAL(clicked(bool)), parent, SLOT(showCardActivatePage()));
    connect(ccRepayBtn, SIGNAL(clicked(bool)), parent, SLOT(showCardRepayPage()));
    connect(ccLostBtn, SIGNAL(clicked(bool)), parent, SLOT(showCardLostPage()));

    queryBtn->setCheckable(true);
    myAccountBtn->setCheckable(true);
    accountQueryBtn->setCheckable(true);
    transferBtn->setCheckable(true);
    currTransferBtn->setCheckable(true);
    currentFixBtn->setCheckable(true);
    paymentBtn->setCheckable(true);
    ccardBtn->setCheckable(true);
    ccApplyBtn->setCheckable(true);
    ccActivateBtn->setCheckable(true);
    ccRepayBtn->setCheckable(true);
    ccLostBtn->setCheckable(true);

}

void WNavbar::updateLanguage(){
    queryLabel->setText(tr("My Account"));
    myAccountLabel->setText(tr("My Account"));
    accountQueryLabel->setText(tr("Account Query"));
    transferLabel->setText(tr("Transfer"));
    currTransferLabel->setText(tr("Current Transfer"));
    currentFixLabel->setText(tr("Current-Fixed"));
    paymentLabel->setText(tr("Payment"));
    ccardLabel->setText(tr("Credit Card"));
    ccApplyLabel->setText(tr("Apply"));
    ccActivateLabel->setText(tr("Activate"));
    ccRepayLabel->setText(tr("Repay"));
    ccLostLabel->setText(tr("Loss Report"));	
}

void WNavbar::checkQuery()
{
    queryBtn->setChecked(true);
    myAccountBtn->setChecked(true);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkMyAccount()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(true);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkAccountQuery()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(true);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkTransfer()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(true);
    currTransferBtn->setChecked(true);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkCurrentTransfer()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(true);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkCurrentFix()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(true);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkPayment()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(true);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkCCard()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(true);
    ccApplyBtn->setChecked(true);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkCCApply()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(true);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkCCActivate()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(true);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkCCRepay()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(true);
    ccLostBtn->setChecked(false);
}
void WNavbar::checkCCLost()
{
    queryBtn->setChecked(false);
    myAccountBtn->setChecked(false);
    accountQueryBtn->setChecked(false);
    transferBtn->setChecked(false);
    currTransferBtn->setChecked(false);
    currentFixBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
    ccApplyBtn->setChecked(false);
    ccActivateBtn->setChecked(false);
    ccRepayBtn->setChecked(false);
    ccLostBtn->setChecked(true);
}
