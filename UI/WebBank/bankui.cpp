#include <QMessageBox>
#include <QFile>

#include "bankui.h"

BankUI::BankUI(QWidget *parent)
    : QWidget(parent)
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
        QMessageBox::warning(this,tr("Warning"),tr("QSS file missing!"));
        this->close();
    }

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMaximumSize(1000,750);
    this->setMinimumSize(1000,750);
    this->setObjectName("MainWindow");

    backgroundLabel = new QLabel("", this);
    userBtn = new QPushButton("", this);
    settingBtn = new QPushButton("", this);
    minBtn  = new QPushButton("", this);
    closeBtn = new QPushButton("", this);
    queryLabel = new QLabel(tr(" My Account"), this);
    transferLabel = new QLabel(tr(" Transfer"), this);
    paymentLabel = new QLabel(tr(" Payment"), this);
    ccardLabel = new QLabel(tr(" Credit Card"), this);
    queryBtn = new QPushButton("", this);
    transferBtn = new QPushButton("", this);
    paymentBtn = new QPushButton("", this);
    ccardBtn = new QPushButton("", this);
    currentPosLabel = new QLabel(tr("Current Position: "), this);
    logInfoLabel = new QLabel(tr("User: "), this);
    creditLabel = new QLabel(tr("Credit to Zhu Yilin & Tian Xingyu"), this);

    backgroundLabel->setObjectName("backgroundLabel");
    userBtn->setObjectName("userBtn");
    settingBtn->setObjectName("settingBtn");
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

    queryBtn->setCheckable(true);
    transferBtn->setCheckable(true);
    paymentBtn->setCheckable(true);
    ccardBtn->setCheckable(true);

    backgroundLabel->setGeometry(QRect(0,0,1000,750));
    userBtn->setGeometry(QRect(856,60,48,48));
    settingBtn->setGeometry(QRect(928,60,48,48));
    minBtn->setGeometry(QRect(955,7,10,10));
    closeBtn->setGeometry(QRect(980,7,10,10));
    queryBtn->setGeometry(QRect(0,152,240,64));
    transferBtn->setGeometry(QRect(0,216,240,64));
    paymentBtn->setGeometry(QRect(0,280,240,64));
    ccardBtn->setGeometry(QRect(0,344,240,64));
    queryLabel->setGeometry(QRect(0,152,240,64));
    transferLabel->setGeometry(QRect(0,216,240,64));
    paymentLabel->setGeometry(QRect(0,280,240,64));
    ccardLabel->setGeometry(QRect(0,344,240,64));
    currentPosLabel->setGeometry(QRect(250,160,200,24));
    logInfoLabel->setGeometry(QRect(0,726,300,24));
    creditLabel->setGeometry(QRect(700,725,300,24));

    creditLabel->setAlignment(Qt::AlignRight);

    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(minBtn, SIGNAL(clicked(bool)), this, SLOT(showMinimized()));
    connect(queryBtn, SIGNAL(clicked(bool)), this, SLOT(popQuery()));
    connect(transferBtn, SIGNAL(clicked(bool)), this, SLOT(popTransfer()));
    connect(paymentBtn, SIGNAL(clicked(bool)), this, SLOT(popPayment()));
    connect(ccardBtn, SIGNAL(clicked(bool)), this, SLOT(popCCard()));
}

BankUI::~BankUI()
{

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
    movePoint = event->globalPos()-pos();
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
