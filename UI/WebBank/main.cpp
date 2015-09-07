#include "bankui.h"
#include "wlogin.h"
#include "wloading.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //read qss file for style sheet settings
    QFile qssFile(":/ui/ui.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        a.setStyleSheet(qssFile.readAll());
        qssFile.close();
    }

    //read translation files for window setup
    QFile transFile("trans/trans.ini");
    transFile.open(QFile::ReadOnly);
    QString QmName = transFile.readAll();
    QTranslator *wTranslator = new QTranslator();
    wTranslator->load(QmName);
    a.installTranslator(wTranslator);
    transFile.close();

    //login window
    WLogin v;
    if (v.exec() != QDialog::Accepted) return -1;

    //loading window
    WLoading l;
    l.exec();

    //main window
    BankUI w;
    w.show();
    w.openUX();

    return a.exec();
}
