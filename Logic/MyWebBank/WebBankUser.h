#ifndef WEBBANKUSER_H
#define WEBBANKUSER_H

#include <QSql>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include "WebBankCurrentUser.h"

struct SUserInfo{
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

class WUser{
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
    QVector<QString> account;
    int messageAmount;
public:
    bool setPassword(QString oldPassword, QString newPassword);
    bool addAccount(QString number);
    int getAccountAmount(){return account.size();}
    static int checkIn(QString name,QString password);
    SUserInfo getUserInfo();
    WUser(SUserInfo userInfo);
    ~WUser();
};


#endif // WEBBANKUSER_H
