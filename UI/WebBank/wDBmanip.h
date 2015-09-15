#ifndef WEBBANKDATABASEMANIP_H
#define WEBBANKDATABASEMANIP_H

#include <QtSql/QSqlDatabase>
#include <QVector>
#include <QString>

class WDBManip
{
public:
    virtual bool dbInsert(QVector<QString> &insertInfo) = 0;
    virtual bool dbUpdate(QString updateInfo) = 0;
    virtual bool dbDelete(QString deleteInfo) = 0;
    virtual bool dbTableCreate() = 0;
};


class DBUserManip: public WDBManip
{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo);
    bool dbSelect(QString userName, QString userPassword);
    bool dbSelect(QString userName);
    static int dbSelectUserKey();
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBAccountManip: public WDBManip
{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo, float fixedDeposit, float currentDeposit);
    bool dbUpdate(QString updateInfo, float sum);
    bool dbPaymentUpdate(QString number, float currentDeposit);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    QVector<QString> dbSelect(int num);
    bool dbSelectAccount(QString number);
    static int dbSelectUserKey(QString number);
    static int dbSelectAccountKey(QString accountNumber);
    static QString dbSelectAccountNumber(int key);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBTransactionRecordManip: public WDBManip
{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo = "");
    QVector<QString> dbSelect(QString selectInfo);
    QVector<QString> dbSelect(QString selectInfo, int cols);
    bool dbDelete(QString deleteInfo = "");
    bool dbTableCreate();
};

class DBPaymentRecordManip: public WDBManip
{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo = "");
    QVector<QString> dbSelect(QString selectInfo);
    QVector<QString> dbSelect(QString selectInfo, int cols);
    bool dbDelete(QString deleteInfo = "");
    bool dbTableCreate();
    static int dbSelectMaxKey();
};

class DBMessageManip: public WDBManip
{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect();
    bool dbDelete(QString deleteInfo = "");
    bool dbTableCreate();
    int dbSelectMessageAmount();
};

class DBLogRecordManip: public WDBManip
{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBAutoPayManip: public WDBManip
{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbDelete(QString number, QString type);
    bool dbTableCreate();
    bool dbSelectAutoPayment(QString number, QString type);
};

#endif // WEBBANKDATABASEMANIP_H
