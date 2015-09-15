#include "wlogin.h"
#include "wuimanip.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QCryptographicHash>

WLogin::WLogin(QWidget *parent) : QDialog(parent)
{
    //main widget setup
    installEventFilter(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute( Qt::WA_TranslucentBackground, true);
    this->setObjectName("LoginWindow");

    //components new
    loginBgLabel = new QLabel(this);
    regBgLabel = new QLabel(this);
    userName = new QLineEdit(this);
    password = new QLineEdit(this);
    passwordConfirm = new QLineEdit(this);
    idCard = new QLineEdit(this);
    cardNum = new QLineEdit(this);
    mobile = new QLineEdit(this);
    email = new QLineEdit(this);
    address = new QLineEdit(this);
    zipcode = new QLineEdit(this);
    notice = new QLabel(this);
    closeBtn = new QPushButton(this);
    regBtn = new QPushButton(tr("Register"), this);
    loginBtn = new QPushButton(tr("Login"), this);
    registerBtn = new QPushButton(tr("Register"), this);
    backBtn = new QPushButton(tr("Go Back"), this);

    //set object name
    loginBgLabel->setObjectName("LogInBG");
    regBgLabel->setObjectName("RegBG");
    userName->setObjectName("LogInUser");
    password->setObjectName("LogInPW");
    passwordConfirm->setObjectName("RegPWConfirm");
    idCard->setObjectName("RegIDCard");
    cardNum->setObjectName("RegCardNum");
    mobile->setObjectName("RegMobile");
    email->setObjectName("RegEmail");
    address->setObjectName("RegAddress");
    zipcode->setObjectName("RegZipcode");
    notice->setObjectName("LogInNotice");
    closeBtn->setObjectName("LogInClose");
    regBtn->setObjectName("LogInReg");
    loginBtn->setObjectName("LogInLogIn");
    registerBtn->setObjectName("RegRegister");
    backBtn->setObjectName("RegBack");

    //set position and size
    loginBgLabel->setGeometry(QRect(0, 0, 400, 678));
    regBgLabel->setGeometry(QRect(0, 0, 400, 678));
    userName->setGeometry(QRect(41, 198, 200, 36));
    password->setGeometry(QRect(41, 246, 200, 36));
    passwordConfirm->setGeometry(QRect(41, 286, 318, 36));
    idCard->setGeometry(QRect(41, 334, 318, 36));
    cardNum->setGeometry(QRect(41, 384, 318, 36));
    mobile->setGeometry(QRect(41, 430, 318, 36));
    email->setGeometry(QRect(41, 478, 318, 36));
    address->setGeometry(QRect(41, 526, 318, 36));
    zipcode->setGeometry(QRect(41, 574, 318, 36));

    notice->setGeometry(QRect(41, 182, 294, 16));
    closeBtn->setGeometry(QRect(375, 12, 10, 15));
    regBtn->setGeometry(QRect(263, 202, 96, 36));
    loginBtn->setGeometry(QRect(263, 244, 96, 36));
    registerBtn->setGeometry(QRect(263, 626, 96, 36));
    backBtn->setGeometry(QRect(167, 626, 96, 36));

    //hide the registration buttons
    loginBgLabel->setVisible(true);
    regBgLabel->setVisible(false);
    regBtn->setVisible(true);
    loginBtn->setVisible(true);
    passwordConfirm->setVisible(false);
    idCard->setVisible(false);
    cardNum->setVisible(false);
    mobile->setVisible(false);
    email->setVisible(false);
    address->setVisible(false);
    zipcode->setVisible(false);
    registerBtn->setVisible(false);
    backBtn->setVisible(false);

    //set place holder text
    userName->setPlaceholderText(tr("Username"));
    password->setPlaceholderText(tr("Password"));
    idCard->setPlaceholderText(tr("ID Number"));
    passwordConfirm->setPlaceholderText(tr("Confirm Password"));
    cardNum->setPlaceholderText(tr("Card Number"));
    mobile->setPlaceholderText(tr("Mobile"));
    email->setPlaceholderText(tr("E-mail"));
    address->setPlaceholderText(tr("Address"));
    zipcode->setPlaceholderText(tr("Zipcode"));

    //set format
    notice->setAlignment(Qt::AlignCenter);
    password->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    passwordConfirm->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    userName->setFocus();

    //set connections
    connect(password, SIGNAL(returnPressed()), this, SLOT(checkLogin()));
    connect(zipcode, SIGNAL(returnPressed()), this, SLOT(checkReg()));
    connect(registerBtn, SIGNAL(clicked(bool)), this, SLOT(checkReg()));
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(regBtn, SIGNAL(clicked(bool)), this, SLOT(changeToReg()));
    connect(loginBtn, SIGNAL(clicked(bool)), this, SLOT(checkLogin()));
    connect(backBtn, SIGNAL(clicked(bool)), this, SLOT(changeToLogin()));

    //start opening animation
    openWindow();
}

void WLogin::checkLogin()
{
    //after login button clicked, check validation
    QString encrypted;
    QByteArray bin;
    bin = QCryptographicHash::hash(password->text().toLatin1(), QCryptographicHash::Sha3_256);
    encrypted.append(bin.toHex());
    int val = WUIManip::login(userName->text(), encrypted);
    switch(val)
    {
    case 1:
        notice->setText(tr("Username not exist!"));
        break;
    case 2:
        notice->setText(tr("Password incorrect!"));
        break;
    case 4:
        accept();
        break;
    }
}

void WLogin::checkReg()
{
    //after registration button clicked, check validation
    if(password->text().length() < 6)
    {
        notice->setText(tr("Password too short!"));
        return;
    }
    if(password->text() != passwordConfirm->text())
    {
        notice->setText(tr("Password inconform!"));
        return;
    }
    if(cardNum->text().length() != 19)
    {
        notice->setText(tr("Card number invalid!"));
        return;
    }
    QString encrypted;
    QByteArray bin;
    bin = QCryptographicHash::hash(password->text().toLatin1(), QCryptographicHash::Sha3_256);
    encrypted.append(bin.toHex());
    QVector<QString> userinfo;
    userinfo.push_back(userName->text());//0
    userinfo.push_back(encrypted);//1
    userinfo.push_back(idCard->text());//2
    userinfo.push_back(mobile->text());//3
    userinfo.push_back(email->text());//4
    userinfo.push_back(address->text());//5
    userinfo.push_back(zipcode->text());//6
    userinfo.push_back(cardNum->text());//7
    bool val = WUIManip::registration(userinfo);
    if (val)
    {
        accept();
    }
    else
    {
        notice->setText(tr("Registration failed!"));
    }
}

void WLogin::openWindow()
{
    //get screen size
    QRect pos = QApplication::desktop()->screenGeometry();
    int height = pos.height();
    int width = pos.width();
    this->setMinimumSize(0, 0);

    //set geometry animation, window appear from middle
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(250);
    animation1->setStartValue(QRect((width - 100) / 2, (height - 75) / 2 + 50, 100, 75));
    animation1->setEndValue(QRect((width - 400) / 2, (height - 300) / 2, 400, 300));
    animation1->setEasingCurve(QEasingCurve::OutExpo);

    //set opacity animation
    QPropertyAnimation *animation2 = new QPropertyAnimation(this, "windowOpacity");
    animation2->setDuration(500);
    animation2->setStartValue(0);
    animation2->setEndValue(1);
    animation2->setEasingCurve(QEasingCurve::OutExpo);

    //start animation
    animation1->start();
    animation2->start();
}

void WLogin::changeToReg()
{
    //change from login window to reg window

    //change widget settings
    loginBgLabel->setVisible(false);
    regBgLabel->setVisible(true);
    notice->setText("");
    regBtn->setVisible(false);
    loginBtn->setVisible(false);
    passwordConfirm->setVisible(true);
    idCard->setVisible(true);
    cardNum->setVisible(true);
    mobile->setVisible(true);
    email->setVisible(true);
    address->setVisible(true);
    zipcode->setVisible(true);
    registerBtn->setVisible(true);
    backBtn->setVisible(true);

    //reset widgets position and size
    notice->setGeometry(QRect(41, 178, 294, 16));
    userName->setGeometry(QRect(41, 190, 318, 36));
    password->setGeometry(QRect(41, 238, 318, 36));

    //set the animation
    QPoint pos = this->mapToGlobal(QPoint(0, 0));
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(pos.rx(), pos.ry(), 400, 300));
    animation1->setEndValue(QRect(pos.rx(), pos.ry() - 200, 400, 678));
    animation1->setEasingCurve(QEasingCurve::InOutCubic);

    //start animation
    animation1->start();
}

void WLogin::changeToLogin()
{
    //change from reg window to login window

    //change widget settings
    loginBgLabel->setVisible(true);
    regBgLabel->setVisible(false);
    notice->setText("");
    regBtn->setVisible(true);
    loginBtn->setVisible(true);
    passwordConfirm->setVisible(false);
    idCard->setVisible(false);
    cardNum->setVisible(false);
    mobile->setVisible(false);
    email->setVisible(false);
    address->setVisible(false);
    zipcode->setVisible(false);
    registerBtn->setVisible(false);
    backBtn->setVisible(false);

    //reset widgets position and size
    notice->setGeometry(QRect(41, 182, 294, 16));
    userName->setGeometry(QRect(41, 190, 200, 36));
    password->setGeometry(QRect(41, 238, 200, 36));

    //set animation
    QPoint pos = this->mapToGlobal(QPoint(0, 0));
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(pos.rx(), pos.ry(), 400, 678));
    animation1->setEndValue(QRect(pos.rx(), pos.ry() + 200, 400, 300));
    animation1->setEasingCurve(QEasingCurve::InOutCubic);

    //start animation
    animation1->start();
}

void WLogin::mouseMoveEvent(QMouseEvent *event)
{
    //if mouse click on top bar and drag, move the window
    if (isPressed && movePoint.ry() < 173)
    {
        QPoint point = event->globalPos();
        move(point - movePoint);
    }
}

void WLogin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        isPressed = true;
    movePoint = event->globalPos() - pos();
}

void WLogin::mouseReleaseEvent(QMouseEvent *event)
{
    event;
    isPressed = false;
}

bool WLogin::eventFilter(QObject *obj, QEvent *event)
{
    //prevent the window from closing on clicking return button
    if ( event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
            return true;
    }
    return QObject::eventFilter(obj, event);
}
