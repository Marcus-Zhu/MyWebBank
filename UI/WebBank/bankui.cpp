#include <QMessageBox>
#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QGraphicsEffect>
#include <QPropertyAnimation>

#include "bankui.h"

BankUI::BankUI(QWidget *parent)
    : QWidget(parent)
{
    setTranslator();
    initUI();

    setConnections();
}

BankUI::~BankUI()
{

}

void BankUI::setTranslator()
{
    isChinese = true;
}

void BankUI::initUI()
{
    //Main Widget SetUp
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMaximumSize(1000, 750);
    this->setMinimumSize(1000, 750);
    this->setObjectName("MainWindow");
    this->setAttribute(Qt::WA_TranslucentBackground);

    //Components New
    backgroundLabel = new QLabel("", this);
    navbar = new WNavbar(this);
    topbar = new WTopbar(this);
    centerStack = new WStackedWidget(this);

    logInfoLabel = new QLabel(tr("User: "), this);
    creditLabel = new QLabel(tr("Credit to Zhu Yilin & Tian Xingyu"), this);

    //Components setObjectName for QSS
    backgroundLabel->setObjectName("backgroundLabel");
    centerStack->setObjectName("centerStack");

    logInfoLabel->setObjectName("logInfoLabel");
    creditLabel->setObjectName("creditLabel");

    //Components' position and size
    backgroundLabel->setGeometry(QRect(0, 0, 1000, 750));
    topbar->setGeometry(QRect(0, 0, 1000, 161));
    navbar->setGeometry(QRect(5, 0, 261, 750));
    centerStack->setGeometry(QRect(242, 152, 751, 566));

    logInfoLabel->setGeometry(QRect(10, 722, 300, 24));
    creditLabel->setGeometry(QRect(700, 724, 290, 24));

    //other settings
    creditLabel->setAlignment(Qt::AlignRight);
    openingOpacity = 0;
}

void BankUI::setConnections()
{
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
    logInfoLabel->setText(tr("User: "));
    creditLabel->setText(tr("Credit to Zhu Yilin & Tian Xingyu"));

    topbar->updateLanguage();
    navbar->updateLanguage();
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
void BankUI::showWelcomePage()
{
    centerStack->setCurrentIndex(14);
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
    navbar->setVisible(false);
    logInfoLabel->setVisible(false);
    creditLabel->setVisible(false);
    centerStack->setVisible(false);
    QPropertyAnimation *a1 = new QPropertyAnimation(topbar, "geometry");
    a1->setDuration(2000);
    a1->setStartValue(QRect(0, -160, 1000, 161));
    a1->setEndValue(QRect(0, 0, 1000, 161));
    a1->setEasingCurve(QEasingCurve::OutExpo);
    a1->start();
    QTimer::singleShot(600, this, SLOT(openUX2()));
}

void BankUI::openUX2()
{
    QPropertyAnimation *a2 = new QPropertyAnimation(navbar, "geometry");
    a2->setDuration(2000);
    a2->setStartValue(QRect(0, 0, 0, 751));
    a2->setEndValue(QRect(0, 0, 260, 751));
    a2->setEasingCurve(QEasingCurve::OutExpo);
    a2->start();
    navbar->setVisible(true);
    QTimer::singleShot(800, this, SLOT(openUX3()));
}

void BankUI::openUX3()
{
    timer = new QTimer(this);
    timer->setInterval(8);
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(openUX5()));
    QTimer::singleShot(2000, timer, SLOT(stop()));
    QTimer::singleShot(20, this, SLOT(openUX4()));
}

void BankUI::openUX4()
{
    logInfoLabel->setVisible(true);
    creditLabel->setVisible(true);
    centerStack->setVisible(true);
}

void BankUI::openUX5()
{
    QGraphicsOpacityEffect *effect1 = new QGraphicsOpacityEffect;
    logInfoLabel->setGraphicsEffect(effect1);
    effect1->setOpacity(openingOpacity);
    QGraphicsOpacityEffect *effect2 = new QGraphicsOpacityEffect;
    creditLabel->setGraphicsEffect(effect2);
    effect2->setOpacity(openingOpacity);
    QGraphicsOpacityEffect *effect3 = new QGraphicsOpacityEffect;
    centerStack->setGraphicsEffect(effect3);
    effect3->setOpacity(openingOpacity);
    openingOpacity += 0.02;
}

bool BankUI::closeWindow()
{
    QPoint pos = this->mapToGlobal(QPoint(0, 0));
    this->setMinimumSize(400, 300);
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
