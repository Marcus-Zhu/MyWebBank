#ifndef WEBBANKUSER_H
#define WEBBANKUSER_H

#include <QSql>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include "WebBankCurrentUser.h"

struct SUserInfo
{
    QString name;
    QString password;
    QString id;
    QString createdDate;
    QString tel;
    QString email;
    QString address;
    QString zipCode;
    QString type;
    QVector <QString> account;
    int messageAmount;
};

class WUser
{
private:
    QString name;
    QString password;
    QString id;
    QString createdDate;
    QString tel;
    QString email;
    QString address;
    QString zipCode;
    QString type;
    int messageAmount;
public:
    QVector<QString> account;
    bool setPassword(QString oldPassword, QString newPassword);
    bool addAccount(QString number, QString type);
    int getAccountAmount()
    {
        return account.size();
    }
    static int checkIn(QString Name, QString password);
    SUserInfo getUserInfo();
    WUser(SUserInfo userInfo);
    WUser() {}
    ~WUser() {};
};


#endif // WEBBANKUSER_H
