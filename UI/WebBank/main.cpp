#include "bankui.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString QmName = "chn.ts";
    QTranslator *wTranslator = new QTranslator();
    wTranslator->load(QmName);
    a.installTranslator(wTranslator);

    BankUI w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
    w.openUX();

    return a.exec();
}
