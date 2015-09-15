#include "wmsgbox.h"

#include <QLabel>
#include <QTextEdit>
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
