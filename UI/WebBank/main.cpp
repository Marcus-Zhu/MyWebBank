#include "bankui.h"
#include <QApplication>
#include <QString>
#include <QPalette>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BankUI w;

    QTranslator wTranslator;
    qDebug() << wTranslator.load("my.qm");
    qApp->installTranslator(&wTranslator);

    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();

    return a.exec();
}
