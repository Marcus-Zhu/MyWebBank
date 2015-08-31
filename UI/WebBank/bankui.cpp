#include <QMessageBox>
#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QApplication>

#include "bankui.h"

BankUI::BankUI(QWidget *parent)
    : QWidget(parent)
{
    setTranslator();
    setStyle();
    initUI();
    setConnections();
}

BankUI::~BankUI()
{

}

void BankUI::setTranslator(){
    isChinese = true;
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
    transferLabel = new QLabel(tr("Transfer"), this);
    paymentLabel = new QLabel(tr("Payment"), this);
    ccardLabel = new QLabel(tr("Credit Card"), this);
    queryBtn = new QPushButton("", this);
    transferBtn = new QPushButton("", this);
    paymentBtn = new QPushButton("", this);
    ccardBtn = new QPushButton("", this);
    currentPosLabel = new QLabel(tr("Current Position: "), this);
    logInfoLabel = new QLabel(tr("User: "), this);
    creditLabel = new QLabel(tr("Credit to Zhu Yilin & Tian Xingyu"), this);
    centerStack = new WStackedWidget(this);

    userMenu->addAction(personalInfoAction);
    userMenu->addAction(changepwAction);
    userMenu->addAction(sysmsgAction);
    userMenu->addAction(logoutAction);
    settingMenu->addAction(languageAction);
    settingMenu->addAction(aboutAction);

    //Components setObjectName for QSS
    backgroundLabel->setObjectName("backgroundLabel");
    userBtn->setObjectName("userBtn");
    settingBtn->setObjectName("settingBtn");
    userMenu->setObjectName("userBtnMenu");
    settingMenu->setObjectName("settingBtnMenu");
    minBtn->setObjectName("minBtn");
    closeBtn->setObjectName("closeBtn");
    queryBtn->setObjectName("queryBtn");
    transferBtn->setObjectName("transferBtn");
    paymentBtn->setObjectName("paymentBtn");
    ccardBtn->setObjectName("ccardBtn");
    queryLabel->setObjectName("queryLabel");
    transferLabel->setObjectName("transferLabel");
    paymentLabel->setObjectName("paymentLabel");
    ccardLabel->setObjectName("ccardLabel");
    currentPosLabel->setObjectName("currentPosLabel");
    logInfoLabel->setObjectName("logInfoLabel");
    creditLabel->setObjectName("creditLabel");

    //Components' position and size
    backgroundLabel->setGeometry(QRect(0, 0, 1000, 750));
    userBtn->setGeometry(QRect(856, 60, 48, 48));
    settingBtn->setGeometry(QRect(928, 60, 48, 48));
    minBtn->setGeometry(QRect(950, 12, 10, 15));
    closeBtn->setGeometry(QRect(975, 12, 10, 15));
    queryBtn->setGeometry(QRect(5, 153, 237, 64));
    transferBtn->setGeometry(QRect(5, 217, 237, 64));
    paymentBtn->setGeometry(QRect(5, 281, 237, 64));
    ccardBtn->setGeometry(QRect(5, 345, 237, 64));
    queryLabel->setGeometry(QRect(0, 160, 240, 64));
    transferLabel->setGeometry(QRect(0, 224, 240, 64));
    paymentLabel->setGeometry(QRect(0, 288, 240, 64));
    ccardLabel->setGeometry(QRect(0, 352, 240, 64));
    currentPosLabel->setGeometry(QRect(254, 158, 200, 24));
    logInfoLabel->setGeometry(QRect(10, 722, 300, 24));
    creditLabel->setGeometry(QRect(700, 724, 290, 24));

    //other settings
    queryBtn->setCheckable(true);
    transferBtn->setCheckable(true);
    paymentBtn->setCheckable(true);
    ccardBtn->setCheckable(true);

    creditLabel->setAlignment(Qt::AlignRight);
}

void BankUI::setConnections(){
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(minBtn, SIGNAL(clicked(bool)), this, SLOT(showMinimized()));
    connect(queryBtn, SIGNAL(clicked(bool)), this, SLOT(popQuery()));
    connect(transferBtn, SIGNAL(clicked(bool)), this, SLOT(popTransfer()));
    connect(paymentBtn, SIGNAL(clicked(bool)), this, SLOT(popPayment()));
    connect(ccardBtn, SIGNAL(clicked(bool)), this, SLOT(popCCard()));
    connect(userBtn, SIGNAL(clicked(bool)),this, SLOT(popUserMenu()));
    connect(settingBtn, SIGNAL(clicked(bool)),this, SLOT(popSettingMenu()));
    connect(languageAction, SIGNAL(triggered(bool)), this, SLOT(changeLanguage()));
}

void BankUI::changeLanguage(){
    QString QmName;
    QTranslator *wTranslator = new QTranslator();
    isChinese ? QmName = "eng.qm" : QmName = "chn.qm";
    isChinese ? isChinese = false : isChinese = true;
    if(wTranslator->load(QmName))
    {
       qApp->installTranslator(wTranslator);
    }
    personalInfoAction->setText(tr("Personal Info"));
    changepwAction->setText(tr("Change Password"));
    sysmsgAction->setText(tr("Message"));
    logoutAction->setText(tr("Log Out"));
    languageAction->setText(tr("Language"));
    aboutAction->setText(tr("About"));
    queryLabel->setText(tr("My Account"));
    transferLabel->setText(tr("Transfer"));
    paymentLabel->setText(tr("Payment"));
    ccardLabel->setText(tr("Credit Card"));
    currentPosLabel->setText(tr("Current Position: "));
    logInfoLabel->setText(tr("User: "));
    creditLabel->setText(tr("Credit to Zhu Yilin & Tian Xingyu"));
}

void BankUI::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressed)
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

void BankUI::popQuery()
{
    transferBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
}

void BankUI::popTransfer()
{
    queryBtn->setChecked(false);
    paymentBtn->setChecked(false);
    ccardBtn->setChecked(false);
}

void BankUI::popPayment()
{
    queryBtn->setChecked(false);
    transferBtn->setChecked(false);
    ccardBtn->setChecked(false);
}

void BankUI::popCCard()
{
    queryBtn->setChecked(false);
    transferBtn->setChecked(false);
    paymentBtn->setChecked(false);
}

void BankUI::popUserMenu(){
    QPoint pos;
    pos.setX(pos.x() - userBtn->geometry().width());
    pos.setY(pos.y() + userBtn->geometry().height());
    userMenu->exec(userBtn->mapToGlobal(pos));
}

void BankUI::popSettingMenu(){
    QPoint pos;
    pos.setX(pos.x() - settingBtn->geometry().width());
    pos.setY(pos.y() + settingBtn->geometry().height());
    settingMenu->exec(settingBtn->mapToGlobal(pos));
}
