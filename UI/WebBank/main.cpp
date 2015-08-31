#include "bankui.h"
#include <QApplication>
#include <QString>
#include <QPalette>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BankUI w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();

    return a.exec();
}
