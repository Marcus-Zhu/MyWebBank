#include <QMessageBox>
#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QApplication>

#include "bankui.h"
#include "qmenubutton.h"

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
    userBtn = new QMenuButton(this, QMenuButton::userBtn);
    settingBtn = new QMenuButton(this, QMenuButton::settingBtn);
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

    //Components setObjectName for QSS
    backgroundLabel->setObjectName("backgroundLabel");
    userBtn->setObjectName("userBtn");
    settingBtn->setObjectName("settingBtn");
    userBtn->menu->setObjectName("userBtnMenu");
    settingBtn->menu->setObjectName("settingBtnMenu");
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
    connect(queryBtn, SIGNAL(clicked(bool)), this, SLOT(changeLanguage()));
}

void BankUI::changeLanguage(){
    QString QmName;
    QTranslator *wTranslator = new QTranslator();
    if(isChinese)
    {
       isChinese = false;
       QmName = "english.qm";
    }
    else
    {
       isChinese = true;
       QmName = "chinese.qm";
    }
    if(wTranslator->load(QmName))
    {
       qDebug() << "change";
       qApp->installTranslator(wTranslator);
    }
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
