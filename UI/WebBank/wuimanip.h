#ifndef WUIMANIP_H
#define WUIMANIP_H

#include <QString>
#include <QVector>
#include <QDate>

class WUIManip
{
public:
    WUIManip();
    static int login(QString name, QString pwd);
    static bool registration(QVector<QString> userInfo);
    static int getAccountNum();
    static QVector<QString> getAccountInfo(int num);
    static QVector<QString> getAccountRecord(int accountNum);
    static bool transfer(QString account1, QString account2, QString amount);
    static bool currentFix(int type, QString account1, QString account2, QString amount);
    static bool payment(QString type, QString account, QString amount);
    static QVector<QString> query(int type, QString account);
    static QVector<QString> dateQuery(int type, QString account, QDate dateFrom, QDate dateTo);

    static QVector<QString> getSysMsg();
    static bool changePwd(QString oldPwd, QString newPwd);
    static QVector<QString> userInfo();
};

#endif // WUIMANIP_H
