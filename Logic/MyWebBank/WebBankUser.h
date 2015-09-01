#ifndef WEBBANKUSER_H
#define WEBBANKUSER_H

#include <QString>
#include <QSql>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QVector>

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
    QVector <WAccount> account;
    QVector <WSysMsg> message;
};

class WAccount;
class WSysMsg;

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
    QVector<WAccount> account;
    QVector<WSysMsg> message;

public:
    bool setPassword(QString newPassword);
    int getAccountNumber(){return account.size();}
    SUserInfo* getUserInfo();
    WUser(SUserInfo userInfo);
    ~WUser();
};


#endif // WEBBANKUSER_H
