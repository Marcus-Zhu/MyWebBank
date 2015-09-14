#include "bankui.h"
#include "wlogin.h"
#include "wloading.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QtSql>
#include <QSqlDatabase>

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
    int isChinese = QmName == "trans/chn.qm" ? 1 : 0;
    a.installTranslator(wTranslator);
    transFile.close();

    //open database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("WebBankDatabase.db");
    db.setUserName("txy");
    db.setPassword("494799822");
    qDebug() << db.open();

    //login window
    WLogin v;
    v.setWindowIcon(QIcon("image/logo.png"));
    if (v.exec() != QDialog::Accepted) return -1;

    //loading window
    WLoading l;
    l.setWindowIcon(QIcon("image/logo.png"));
    l.exec();

    //main window
    BankUI w(0,isChinese);
    w.setWindowIcon(QIcon("image/logo.png"));
    w.show();
    w.openUX();

//    db.close();
    return a.exec();
}
