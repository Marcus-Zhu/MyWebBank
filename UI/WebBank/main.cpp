#include "bankui.h"
#include "wlogin.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/ui/ui.qss");
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    QString QmName = "chn.ts";
    QTranslator *wTranslator = new QTranslator();
    wTranslator->load(QmName);
    a.installTranslator(wTranslator);

    WLogin v;
    if (v.exec() != QDialog::Accepted) return -1;

    BankUI w;
    w.show();
    w.openUX();

    return a.exec();
}
