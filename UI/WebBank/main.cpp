#include "bankui.h"
#include "wlogin.h"
#include "wloading.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qssFile(":/ui/ui.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        a.setStyleSheet(qssFile.readAll());
        qssFile.close();
    }

    QFile transFile("trans/trans.ini");
    transFile.open(QFile::ReadOnly);
    QString QmName = transFile.readAll();
    qDebug() << QmName;
    QTranslator *wTranslator = new QTranslator();
    wTranslator->load(QmName);
    a.installTranslator(wTranslator);
    transFile.close();

    WLogin v;
    if (v.exec() != QDialog::Accepted) return -1;

    WLoading l;
    l.exec();

    BankUI w;
    w.show();
    w.openUX();

    return a.exec();
}
