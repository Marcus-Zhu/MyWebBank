#include "bankui.h"
#include "wlogin.h"
#include "wloading.h"
#include "wuimanip.h"
#include "wmsgbox.h"
#include <QApplication>
#include <QString>
#include <QtSql>
#include <QSqlDatabase>

//QSqlDatabase WUIManip::database = QSqlDatabase::addDatabase("QSQLITE");

int main(int argc, char *argv[])
{
    int exitcode = 0;
    QApplication a(argc, argv);

    do{
        //read qss file for style sheet settings
        QFile qssFile(":/ui/ui_blue.qss");
        qssFile.open(QFile::ReadOnly);
        if(qssFile.isOpen())
        {
            a.setStyleSheet(qssFile.readAll());
            qssFile.close();
        }
        else
        {
            WMsgBox::information(QObject::tr("Unable to open QSS File!"));
            exit(-1);
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
        WUIManip dbmanip;
        if(!dbmanip.openDatabase())
        {
            WMsgBox::information(QObject::tr("Unable to open database!"));
            exit(-2);
        }

        //login window
        WLogin v;
        v.setWindowIcon(QIcon("image/logo.png"));
        if (v.exec() != QDialog::Accepted) return -1;

        //loading window
        WLoading l;
        l.setWindowIcon(QIcon("image/logo.png"));
        l.exec();

        //main window
        BankUI w(0, isChinese);
        w.setWindowIcon(QIcon("image/logo.png"));
        w.show();
        w.openUX();

        exitcode = a.exec();

        dbmanip.database.close();
    }while(exitcode == 2);
}
