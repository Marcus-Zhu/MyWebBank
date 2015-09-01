#include <QMessageBox>
#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QPropertyAnimation>

#include "bankui.h"

BankUI::BankUI(QWidget *parent)
    : QWidget(parent)
{
    setTranslator();
    setStyle();
    initUI();

    centerStack = new WStackedWidget(this);
    centerStack->setObjectName("centerStack");
    centerStack->setGeometry(QRect(242, 148, 751, 534));

    setConnections();
    openWindow();
}

BankUI::~BankUI()
{

}

void BankUI::setTranslator()
{
    isChinese = false;
}

void BankUI::setStyle()
{
    QFile file(":/ui/ui.qss");
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        this->setStyleSheet(file.readAll());
        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("QSS file missing!"));
        this->close();
    }
}

void BankUI::initUI()
{
    //Main Widget SetUp
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMaximumSize(1000, 750);
    this->setMinimumSize(1000, 750);
    this->setObjectName("MainWindow");

    //Components New
    backgroundLabel = new QLabel("", this);
    navbarLabel = new QLabel("", this);
    topbarLabel = new QLabel("", this);
    menubarLabel = new QLabel("", this);
    userBtn = new QPushButton("", this);
    settingBtn = new QPushButton("", this);

    userMenu = new QMenu(this);
    settingMenu = new QMenu(this);
    personalInfoAction = new QAction(tr("Personal Info"), this);
    changepwAction = new QAction(tr("Change Password"), this);
    sysmsgAction = new QAction(tr("Message"), this);
    logoutAction = new QAction(tr("Log Out"), this);
    languageAction = new QAction(tr("Language"), this);
    aboutAction = new QAction(tr("About"), this);
    minBtn  = new QPushButton("", this);
    closeBtn = new QPushButton("", this);

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

    logInfoLabel = new QLabel(tr("User: "), this);
    creditLabel = new QLabel(tr("Credit to Zhu Yilin & Tian Xingyu"), this);

    userMenu->addAction(personalInfoAction);
    userMenu->addAction(changepwAction);
    userMenu->addAction(sysmsgAction);
    userMenu->addAction(logoutAction);
    settingMenu->addAction(languageAction);
    settingMenu->addAction(aboutAction);

    //Components setObjectName for QSS
    backgroundLabel->setObjectName("backgroundLabel");
    topbarLabel->setObjectName("topbarLabel");
    menubarLabel->setObjectName("menubarLabel");
    navbarLabel->setObjectName("navbarLabel");
    userBtn->setObjectName("userBtn");
    settingBtn->setObjectName("settingBtn");
    userMenu->setObjectName("userBtnMenu");
    settingMenu->setObjectName("settingBtnMenu");
    personalInfoAction->setObjectName(("personalInfoAction"));
    changepwAction->setObjectName(("ChangepwAction"));
    sysmsgAction->setObjectName(("MessageAction"));
    logoutAction->setObjectName(("logoutAction"));
    languageAction->setObjectName(("languageAction"));
    aboutAction->setObjectName(("aboutAction"));
    minBtn->setObjectName("minBtn");
    closeBtn->setObjectName("closeBtn");

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

    logInfoLabel->setObjectName("logInfoLabel");
    creditLabel->setObjectName("creditLabel");

    //Components' position and size
    backgroundLabel->setGeometry(QRect(0, 0, 1000, 750));
    menubarLabel->setGeometry(QRect(0, -40, 1000, 33));
    userBtn->setGeometry(QRect(856, 60, 48, 48));
    settingBtn->setGeometry(QRect(928, 60, 48, 48));
    minBtn->setGeometry(QRect(950, 12, 10, 15));
    closeBtn->setGeometry(QRect(975, 12, 10, 15));

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

    logInfoLabel->setGeometry(QRect(10, 722, 300, 24));
    creditLabel->setGeometry(QRect(700, 724, 290, 24));

    //other settings
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

    creditLabel->setAlignment(Qt::AlignRight);
}

void BankUI::setConnections()
{
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
    connect(minBtn, SIGNAL(clicked(bool)), this, SLOT(showMinimized()));
    connect(userBtn, SIGNAL(clicked(bool)), this, SLOT(popUserMenu()));
    connect(settingBtn, SIGNAL(clicked(bool)), this, SLOT(popSettingMenu()));

    //connections for POP BUTTONS
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

    //connections for CHANGE PAGE
    connect(queryBtn, SIGNAL(clicked(bool)), this, SLOT(showMyAccountPage()));
    connect(myAccountBtn, SIGNAL(clicked(bool)), this, SLOT(showMyAccountPage()));
    connect(accountQueryBtn, SIGNAL(clicked(bool)), this, SLOT(showAccountQueryPage()));
    connect(transferBtn, SIGNAL(clicked(bool)), this, SLOT(showTransferPage()));
    connect(currTransferBtn, SIGNAL(clicked(bool)), this, SLOT(showTransferPage()));
    connect(currentFixBtn, SIGNAL(clicked(bool)), this, SLOT(shouCurrentFixPage()));
    connect(paymentBtn, SIGNAL(clicked(bool)), this, SLOT(showPaymentPage()));
    connect(ccardBtn, SIGNAL(clicked(bool)), this, SLOT(showCardApplyPage()));
    connect(ccApplyBtn, SIGNAL(clicked(bool)), this, SLOT(showCardApplyPage()));
    connect(ccActivateBtn, SIGNAL(clicked(bool)), this, SLOT(showCardActivatePage()));
    connect(ccRepayBtn, SIGNAL(clicked(bool)), this, SLOT(showCardRepayPage()));
    connect(ccLostBtn, SIGNAL(clicked(bool)), this, SLOT(showCardLostPage()));

    //connections for ACTIONS
    connect(personalInfoAction, SIGNAL(triggered(bool)), this, SLOT(showUserInfoPage()));
    connect(changepwAction, SIGNAL(triggered(bool)), this, SLOT(showChangePwPage()));
    connect(sysmsgAction, SIGNAL(triggered(bool)), this, SLOT(showSysMsgPage()));
    connect(logoutAction, SIGNAL(triggered(bool)), this, SLOT(closeWindow()));
    connect(languageAction, SIGNAL(triggered(bool)), this, SLOT(changeLanguage()));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(showAboutPage()));
}

void BankUI::changeLanguage()
{
    QString QmName;
    QTranslator *wTranslator = new QTranslator();
    isChinese ? QmName = "eng.qm" : QmName = "chn.qm";
    isChinese ? isChinese = false : isChinese = true;
    if(wTranslator->load(QmName))
    {
        qApp->installTranslator(wTranslator);
    }
    updateLanguage();
}
void BankUI::updateLanguage()
{
    personalInfoAction->setText(tr("Personal Info"));
    changepwAction->setText(tr("Change Password"));
    sysmsgAction->setText(tr("Message"));
    logoutAction->setText(tr("Log Out"));
    languageAction->setText(tr("Language"));
    aboutAction->setText(tr("About"));

    logInfoLabel->setText(tr("User: "));
    creditLabel->setText(tr("Credit to Zhu Yilin & Tian Xingyu"));

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
    centerStack->updateLanguage();
}

void BankUI::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressed && (movePoint.ry() < 160 || movePoint.ry() > 726))
    {
        QPoint point = event->globalPos();
        move(point - movePoint);
    }
}
void BankUI::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        isPressed = true;
    movePoint = event->globalPos() - pos();
}
void BankUI::mouseReleaseEvent(QMouseEvent *event)
{
    event;
    isPressed = false;
}

void BankUI::checkQuery()
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
void BankUI::checkMyAccount()
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
void BankUI::checkAccountQuery()
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
void BankUI::checkTransfer()
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
void BankUI::checkCurrentTransfer()
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
void BankUI::checkCurrentFix()
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
void BankUI::checkPayment()
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
void BankUI::checkCCard()
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
void BankUI::checkCCApply()
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
void BankUI::checkCCActivate()
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
void BankUI::checkCCRepay()
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
void BankUI::checkCCLost()
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

void BankUI::popUserMenu()
{
    QPoint pos;
    pos.setX(pos.x() - userBtn->geometry().width());
    pos.setY(pos.y() + userBtn->geometry().height());
    userMenu->exec(userBtn->mapToGlobal(pos));
}
void BankUI::popSettingMenu()
{
    QPoint pos;
    pos.setX(pos.x() - settingBtn->geometry().width());
    pos.setY(pos.y() + settingBtn->geometry().height());
    settingMenu->exec(settingBtn->mapToGlobal(pos));
}

void BankUI::showMyAccountPage()
{
    centerStack->setCurrentIndex(0);
}
void BankUI::showAccountQueryPage()
{
    centerStack->setCurrentIndex(1);
}
void BankUI::showTransferPage()
{
    centerStack->setCurrentIndex(2);
}
void BankUI::shouCurrentFixPage()
{
    centerStack->setCurrentIndex(3);
}
void BankUI::showPaymentPage()
{
    centerStack->setCurrentIndex(4);
}
void BankUI::showAutoPayPage()
{
    centerStack->setCurrentIndex(5);
}
void BankUI::showCardApplyPage()
{
    centerStack->setCurrentIndex(6);
}
void BankUI::showCardActivatePage()
{
    centerStack->setCurrentIndex(7);
}
void BankUI::showCardRepayPage()
{
    centerStack->setCurrentIndex(8);
}
void BankUI::showCardLostPage()
{
    centerStack->setCurrentIndex(9);
}
void BankUI::showUserInfoPage()
{
    centerStack->setCurrentIndex(10);
}
void BankUI::showChangePwPage()
{
    centerStack->setCurrentIndex(11);
}
void BankUI::showSysMsgPage()
{
    centerStack->setCurrentIndex(12);
}
void BankUI::showAboutPage()
{
    centerStack->setCurrentIndex(13);
}

void BankUI::openWindow(){
    userBtn->setVisible(false);
    settingBtn->setVisible(false);
    minBtn->setVisible(false);
    closeBtn->setVisible(false);

    queryLabel->setVisible(false);
    myAccountLabel->setVisible(false);
    accountQueryLabel->setVisible(false);
    transferLabel->setVisible(false);
    currTransferLabel->setVisible(false);
    currentFixLabel->setVisible(false);
    paymentLabel->setVisible(false);
    ccardLabel->setVisible(false);
    ccApplyLabel->setVisible(false);
    ccActivateLabel->setVisible(false);
    ccRepayLabel->setVisible(false);
    ccLostLabel->setVisible(false);

    logInfoLabel->setVisible(false);
    creditLabel->setVisible(false);
    centerStack->setVisible(false);
}

void BankUI::openUX()
{
    // QRect pos = QApplication::desktop()->screenGeometry();
    // int height = pos.height();
    // int width = pos.width();
    // QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    // animation1->setDuration(150);
    // animation1->setStartValue(QRect((width - 400) / 2, (height - 300) / 2 + 50, 400, 300));
    // animation1->setEndValue(QRect((width - 1000) / 2, (height - 750) / 2, 1000, 750));
    // animation1->setEasingCurve(QEasingCurve::OutQuint);
    // QPropertyAnimation *animation2 = new QPropertyAnimation(this, "windowOpacity");
    // animation2->setDuration(200);
    // animation2->setStartValue(0);
    // animation2->setEndValue(1);
    // animation2->setEasingCurve(QEasingCurve::OutQuint);
    // animation1->start();
    // animation2->start();
    // topbarLabel->setGeometry(QRect(0, 0, 1000, 161));
    // menubarLabel->setGeometry(QRect(0, 0, 1000, 33));
    // navbarLabel->setGeometry(QRect(0, 0, 260, 751));
    QPropertyAnimation *a1 = new QPropertyAnimation(topbarLabel, "geometry");
    a1->setDuration(1000);
    a1->setStartValue(QRect(0, -40, 1000, 161));
    a1->setEndValue(QRect(0, 0, 1000, 161));
    a1->setEasingCurve(QEasingCurve::OutExpo);
    a1->start();
    QPropertyAnimation *a3 = new QPropertyAnimation(menubarLabel, "geometry");
    a3->setDuration(1000);
    a3->setStartValue(QRect(0, -40, 1000, 33));
    a3->setEndValue(QRect(0, 0, 1000, 33));
    a3->setEasingCurve(QEasingCurve::OutExpo);
    a3->start();
    QTimer::singleShot(450,this,SLOT(openUX2()));
}

void BankUI::openUX2(){
    QPropertyAnimation *a2 = new QPropertyAnimation(navbarLabel, "geometry");
    a2->setDuration(750);
    a2->setStartValue(QRect(-30, 0, 260, 751));
    a2->setEndValue(QRect(0, 0, 260, 751));
    a2->setEasingCurve(QEasingCurve::OutExpo);
    a2->start();
    QTimer::singleShot(700,this,SLOT(showWidgets()));
}

void BankUI::showWidgets(){
    userBtn->setVisible(true);
    settingBtn->setVisible(true);

    queryLabel->setVisible(true);
    myAccountLabel->setVisible(true);
    accountQueryLabel->setVisible(true);
    transferLabel->setVisible(true);
    currTransferLabel->setVisible(true);
    currentFixLabel->setVisible(true);
    paymentLabel->setVisible(true);
    ccardLabel->setVisible(true);
    ccApplyLabel->setVisible(true);
    ccActivateLabel->setVisible(true);
    ccRepayLabel->setVisible(true);
    ccLostLabel->setVisible(true);

    minBtn->setVisible(true);
    closeBtn->setVisible(true);

    logInfoLabel->setVisible(true);
    creditLabel->setVisible(true);
    centerStack->setVisible(true);
}

bool BankUI::closeWindow()
{
    QPoint pos = this->mapToGlobal(QPoint(0, 0));
    this->setMinimumSize(400,300);
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(165);
    animation1->setStartValue(QRect(pos.rx(), pos.ry(), 1000, 750));
    animation1->setEndValue(QRect(pos.rx() + 300, pos.ry() + 250, 400, 300));
    animation1->setEasingCurve(QEasingCurve::OutSine);
    QPropertyAnimation *animation2 = new QPropertyAnimation(this, "windowOpacity");
    animation2->setDuration(165);
    animation2->setStartValue(1);
    animation2->setEndValue(0);
    animation1->start();
    animation2->start();
    connect(animation2, SIGNAL(finished()), this, SLOT(close()));
    return true;
}
