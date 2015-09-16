#include "bankui.h"
#include "wlogin.h"
#include "wloading.h"
#include "wuimanip.h"
#include "wmsgbox.h"
#include <QApplication>
#include <QString>
#include <QSettings>
#include <QtSql>
#include <QSqlDatabase>

//QSqlDatabase WUIManip::database = QSqlDatabase::addDatabase("QSQLITE");

int main(int argc, char *argv[])
{
    int exitcode = 0;
    QApplication a(argc, argv);

    do
    {
        //read qss file for style sheet settings
        QSettings config("config.ini", QSettings::IniFormat);
        QString colorName = config.value("QSS").toString();
        QString logoName = config.value("LOGO").toString();
        QFile qssFile(colorName);
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
        QString transName = config.value("TRANS").toString();
        QTranslator *wTranslator = new QTranslator();
        wTranslator->load(transName);
        int isChinese = transName == "trans/chn.qm" ? 1 : 0;
        a.installTranslator(wTranslator);

        //open database
        WUIManip dbmanip;
        if(!dbmanip.openDatabase())
        {
            WMsgBox::information(QObject::tr("Unable to open database!"));
            exit(-2);
        }

        if(exitcode != 3)
        {
            //login window
            WLogin v;
            v.setWindowIcon(QIcon(logoName));
            if (v.exec() != QDialog::Accepted) return -1;

            //loading window
            WLoading l;
            l.setWindowIcon(QIcon(logoName));
            l.exec();
        }

        //main window
        BankUI w(0, isChinese);
        w.setWindowIcon(QIcon(logoName));
        w.show();
        w.openUX();

        exitcode = a.exec();

        dbmanip.database.close();
    }
    while(exitcode == 2 || exitcode == 3);
}
