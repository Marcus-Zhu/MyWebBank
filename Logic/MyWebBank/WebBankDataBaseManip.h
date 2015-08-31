#ifndef WEBBANKDATABASEMANIP_H
#define WEBBANKDATABASEMANIP_H

#include <QtSql>
#include <QVector>
#include <QSqlQuery>
#include "WebBankUser.h"


class WDBManip{
enum manipTable { user = 1, account = 2, transactionRecord = 3, paymentRecord = 4,
                  message = 5};
private:
    QSqlQuery query;

public:
    virtual bool dbInsert(QVector<QString> insertInfo);
    virtual bool dbUpdate(QString updateInfo);
    //virtual bool dbSelect(QString selectInfo);
    virtual bool dbDelete(QString deleteInfo);
    virtual bool dbTableCreate();
};

class DBUserManip: public WDBManip{
public:
    bool dbInsert(QVector<QString> insertInfo);
    bool dbUpdate(QString updateInfo);
    bool dbSelect(QString userName,QString userPassword);
    static int dbSelect();
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBAccountManip: public WDBManip{
public:
    bool dbInsert(QVector<QString> insertInfo);
    bool dbUpdate(QString updateInfo,QString updateBalance);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBTransactionRecordManip: public WDBManip{
public:
    bool dbInsert(QVector<QString> insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBPaymetnRecordManip: public WDBManip{
public:
    bool dbInsert(QVector<QString> insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBMessageManip: public WDBManip{
public:
    bool dbInsert(QVector<QString> insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
}

#endif // WEBBANKDATABASEMANIP_H
