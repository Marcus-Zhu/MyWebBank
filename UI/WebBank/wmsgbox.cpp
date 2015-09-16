#include "wmsgbox.h"

#include <QLabel>
#include <QTextEdit>
#include <QDebug>
#include <QPushButton>

WMsgBox::WMsgBox(QWidget *parent) : QDialog(parent)
{
}

void WMsgBox::information(QString content, QWidget *parent)
{
    WMsgBox *w = new WMsgBox(parent);

    //main widget setup
    w->setWindowFlags(Qt::FramelessWindowHint);
    w->setAttribute( Qt::WA_TranslucentBackground, true);
    w->setObjectName("MsgBox");

    //components new
    w->bgLabel = new QLabel(w);
    w->contentLabel = new QLabel(content, w);
    w->closeBtn = new QPushButton(w);
    w->okBtn = new QPushButton(tr("OK"), w);

    //set object name
    w->bgLabel->setObjectName("MsgBoxBG");
    w->contentLabel->setObjectName("MsgBoxContent");
    w->closeBtn->setObjectName("MsgBoxClose");
    w->okBtn->setObjectName("MsgBoxOK");

    //set position and size
    w->bgLabel->setGeometry(QRect(0, 0, 328, 219));
    w->contentLabel->setGeometry(QRect(0, 102, 328, 48));
    w->closeBtn->setGeometry(QRect(301, 12, 10, 15));
    w->okBtn->setGeometry(QRect(219, 162, 88, 36));

    //set format
    w->contentLabel->setAlignment(Qt::AlignCenter);

    //set connections
    connect(w->okBtn, SIGNAL(clicked(bool)), w, SLOT(accept()));
    connect(w->closeBtn, SIGNAL(clicked(bool)), w, SLOT(reject()));

    w->exec();
}

void WMsgBox::about(QWidget *parent)
{
    WMsgBox *w = new WMsgBox(parent);

    //main widget setup
    w->setWindowFlags(Qt::FramelessWindowHint);
    w->setAttribute( Qt::WA_TranslucentBackground, true);
    w->setObjectName("AboutBox");

    //components new
    w->bgLabel = new QLabel(w);
    w->contentText = new QTextEdit(w);
    w->closeBtn = new QPushButton(w);
    w->okBtn = new QPushButton(tr("OK"), w);
    w->contentText->setText(tr("    This program is designed and developed by "
                               "Tsinghua freshman, Zhu Yilin and Tian Xingyu. "
                               "It serves as the big assignment for C++ course "
                               "taught by Prof. Dong. The develop environment is "
                               "Qt 5.5.0 MSVC2012 with Microsoft Visual C++ "
                               "Compiler 11.0 (x86).\n"
                               "    Here we extend special thanks to the course "
                               "teacher and TA, who lead us into the world of C++. "
                               "We would also like to offer thanks to the open "
                               "source projects that make our program possible."));

    //set object name
    w->bgLabel->setObjectName("AboutBoxBG");
    w->contentText->setObjectName("MsgBoxContent");
    w->closeBtn->setObjectName("MsgBoxClose");
    w->okBtn->setObjectName("MsgBoxOK");

    //set position and size
    w->bgLabel->setGeometry(QRect(0, 0, 550, 420));
    w->contentText->setGeometry(QRect(24, 102, 502, 450));
    w->closeBtn->setGeometry(QRect(529, 12, 10, 15));
    w->okBtn->setGeometry(QRect(441, 363, 88, 36));

    //set format
    w->contentText->setEnabled(false);
    w->contentText->setAlignment(Qt::AlignVCenter);

    //set connections
    connect(w->okBtn, SIGNAL(clicked(bool)), w, SLOT(accept()));
    connect(w->closeBtn, SIGNAL(clicked(bool)), w, SLOT(reject()));

    w->exec();
}

void WMsgBox::color(QWidget *parent)
{
    WMsgBox *w = new WMsgBox(parent);
    w->move(326, 226);

    //main widget setup
    w->setWindowFlags(Qt::FramelessWindowHint);
    w->setAttribute( Qt::WA_TranslucentBackground, true);
    w->setObjectName("ColorBox");

    //components new
    w->bgLabel = new QLabel(w);
    w->contentLabel = new QLabel(tr("Choose a theme"), w);
    w->closeBtn = new QPushButton(w);
    w->blueBtn = new QPushButton(w);
    w->greenBtn = new QPushButton(w);
    w->orangeBtn = new QPushButton(w);
    w->purpleBtn = new QPushButton(w);
    w->redBtn = new QPushButton(w);
    w->yellowBtn = new QPushButton(w);

    //set object name
    w->bgLabel->setObjectName("MsgBoxBG");
    w->contentLabel->setObjectName("MsgBoxContent");
    w->closeBtn->setObjectName("MsgBoxClose");

    //set position and size
    w->bgLabel->setGeometry(QRect(0, 0, 328, 219));
    w->contentLabel->setGeometry(QRect(0, 102, 328, 48));
    w->closeBtn->setGeometry(QRect(301, 12, 10, 15));
    w->blueBtn->setGeometry(QRect(170, 160, 36, 36));
    w->greenBtn->setGeometry(QRect(218, 160, 36, 36));
    w->orangeBtn->setGeometry(QRect(74, 160, 36, 36));
    w->purpleBtn->setGeometry(QRect(266, 160, 36, 36));
    w->redBtn->setGeometry(QRect(26, 160, 36, 36));
    w->yellowBtn->setGeometry(QRect(122, 160, 36, 36));

    //set format
    w->contentLabel->setAlignment(Qt::AlignCenter);
    w->blueBtn->setStyleSheet("background-color: #03a9f4; border-radius: 2px;");
    w->greenBtn->setStyleSheet("background-color: #8bc34a; border-radius: 2px;");
    w->orangeBtn->setStyleSheet("background-color: #ff9800; border-radius: 2px;");
    w->purpleBtn->setStyleSheet("background-color: #673ab7; border-radius: 2px;");
    w->redBtn->setStyleSheet("background-color: #e51c23; border-radius: 2px;");
    w->yellowBtn->setStyleSheet("background-color: #ffeb3b; border-radius: 2px;");

    //set connections
    connect(w->closeBtn, SIGNAL(clicked(bool)), w, SLOT(reject()));
    connect(w->blueBtn, SIGNAL(clicked(bool)), parent, SLOT(changeToBlue()));
    connect(w->greenBtn, SIGNAL(clicked(bool)), parent, SLOT(changeToGreen()));
    connect(w->orangeBtn, SIGNAL(clicked(bool)), parent, SLOT(changeToOrange()));
    connect(w->purpleBtn, SIGNAL(clicked(bool)), parent, SLOT(changeToPurple()));
    connect(w->redBtn, SIGNAL(clicked(bool)), parent, SLOT(changeToRed()));
    connect(w->yellowBtn, SIGNAL(clicked(bool)), parent, SLOT(changeToYellow()));

    w->exec();
}

void WMsgBox::mouseMoveEvent(QMouseEvent *event)
{
    //if mouse click on top bar and drag, move the window
    if (isPressed && movePoint.ry() < 89)
    {
        QPoint point = event->globalPos();
        move(point - movePoint);
    }
}

void WMsgBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        isPressed = true;
    movePoint = event->globalPos() - pos();
}

void WMsgBox::mouseReleaseEvent(QMouseEvent *event)
{
    event;
    isPressed = false;
}
