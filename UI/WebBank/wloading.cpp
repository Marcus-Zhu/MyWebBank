#include "wloading.h"
#include <QTimer>
#include <QDebug>

WLoading::WLoading(QDialog *parent) : QDialog(parent)
{
    //main widget setup
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(300, 150);
    this->setMinimumSize(300, 150);
    this->setObjectName("MainWindow");

    //components new
    label1 = new QLabel(this);
    label2 = new QLabel(this);
    movie = new QMovie(":/image/image/loading.gif");

    //set position and size
    label1->setGeometry(QRect(-50, -75, 400, 300));
    label2->setGeometry(QRect(0, 0, 300, 150));
    movie->setScaledSize(QSize(400, 300));

    //set gif
    label1->setMovie(movie);
    label2->setObjectName("LoadingLabel");

    //start gif after delay
    label2->setVisible(false);
    QTimer::singleShot(400, this, SLOT(showLabel()));
    QTimer::singleShot(300, movie, SLOT(start()));
    QTimer::singleShot(6000, this, SLOT(close()));
}

void WLoading::showLabel()
{
    label2->setVisible(true);
}
