#ifndef WEBBANK_H
#define WEBBANK_H

#include <QString>
#include <QSql>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <vector>

struct SUserInfo{
    QString name;
    QString id;
    QString createDate;
    QString tel;
    QString email;
    QString address;
    QString zipCode;
    QString type;
    vector <WAccount> account;
    vector <WSysMsg> message;
};

class WAccount;
class WSysMsg;

class WUser{
private:
    QString name;
    QString id;
    QString createDate;
    QString tel;
    QString email;
    QString address;
    QString zipCode;
    QString type;
    vector <WAccount> account;
    vector <WSysMsg> message;
public:
    bool setEmail(QString newEmail);
    bool setAddress(QString newAddress);
    bool setZipCode(QString newZipCode);
    bool setPassword(QString newPassword);
    int getAccountNumber(){return account.size();}
    SUserInfo getUserInfo();
    WUser(SUserInfo user);
    ~WUser();
};

class WDBManip{
public:
    bool dbInsert(QString insertInfo);
    bool dbUpdate(QString updateInfo);
    QString dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
};

#endif // WEBBANK_H
