#include "wmsgbox.h"

#include <QLabel>
#include <QPushButton>

WMsgBox::WMsgBox(QWidget *parent) : QDialog(parent)
{
}

void WMsgBox::information(QString content)
{
    WMsgBox *w = new WMsgBox;

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

    w->show();
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
