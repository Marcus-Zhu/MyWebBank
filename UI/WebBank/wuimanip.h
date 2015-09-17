#ifndef WUIMANIP_H
#define WUIMANIP_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QSqlDatabase>

class WUIManip
{
public:
    WUIManip();
    bool openDatabase();
    void closeDatabase();

    static int login(QString name, QString pwd);
    static bool logout();
    static bool registration(QVector<QString> userInfo);
    static int getAccountNum();
    static QVector<QString> getAccountInfo(int num);
    static QVector<QString> getAccountRecord(int accountNum);
    static bool transfer(QString account1, QString account2, QString amount);
    static bool currentFix(int type, QString account1, QString account2, QString amount);
    static bool payment(QString type, QString account, QString amount);
    static bool setAutopay(QString account, QString type);
    static bool cancelAutopay(QString account, QString type);
    static QVector<QString> getAutopayRecord();
    static QVector<QString> query(int type, QString account);
    static QVector<QString> dateQuery(int type, QString account, QDate dateFrom, QDate dateTo);
    static bool cardApply(int type);
    static bool cardActivate(QString account);
    static bool cardRepay(QString account1, QString account2, QString amount);
    static bool cardLost(QString account);
    static QVector<QString> getSysMsg();
    static bool hasSysMsg();
    static bool changePwd(QString oldPwd, QString newPwd);
    static QVector<QString> userInfo();

    QSqlDatabase database;
};

#endif // WUIMANIP_H
