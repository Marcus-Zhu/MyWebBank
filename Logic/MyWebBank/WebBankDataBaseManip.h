#ifndef WEBBANKDATABASEMANIP_H
#define WEBBANKDATABASEMANIP_H

#include <QtSql>
#include <QVector>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>

class WDBManip{
public:
    virtual bool dbInsert(QVector<QString>& insertInfo) = 0;//插入新信息类
    virtual bool dbUpdate(QString updateInfo) = 0;          //更新数据库中信息
    virtual bool dbDelete(QString deleteInfo) = 0;          //删除信息
    virtual bool dbTableCreate() = 0;                       //创建表时调用
};

//以下继承的函数上面已经说明了含义，新写的函数在cpp文件中会具体说明

class DBUserManip: public WDBManip{
public:
    bool dbInsert(QVector<QString>& insertInfo);
    bool dbUpdate(QString updateInfo);
    bool dbSelect(QString userName,QString userPassword);
    bool dbSelect(QString userName);
    static int dbSelectUserKey();
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBAccountManip: public WDBManip{
public:
    bool dbInsert(QVector<QString>& insertInfo);
    bool dbUpdate(QString updateInfo, float fixedDeposit,float currentDeposit);
    bool dbUpdate(QString updateInfo,float sum);
    bool dbPaymentUpdate(QString number, float currentDeposit);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    static int dbSelectUserKey(QString number);
    static int dbSelectAccountKey(QString accountNumber);
    static QString dbSelectAccountNumber(int key);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBTransactionRecordManip: public WDBManip{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo = "");
    QVector<QString> dbSelect(QString selectInfo);
    QVector<QString> dbSelect(QString selectInfo,int cols);
    bool dbDelete(QString deleteInfo = "");
    bool dbTableCreate();
};

class DBPaymentRecordManip: public WDBManip{
public:
    bool dbInsert(QVector<QString>& insertInfo);
    bool dbUpdate(QString updateInfo = "");
    QVector<QString> dbSelect(QString selectInfo);
    QVector<QString> dbSelect(QString selectInfo,int cols);
    bool dbDelete(QString deleteInfo = "");
    bool dbTableCreate();
};

class DBMessageManip: public WDBManip{
public:
    bool dbInsert(QVector<QString>& insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo = "");
    bool dbTableCreate();
    int dbSelectMessageAmount();
};

class DBLogRecordManip:public WDBManip{
public:
    bool dbInsert(QVector<QString>& insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbTableCreate();
};

class DBAutoPayManip:public WDBManip{
public:
    bool dbInsert(QVector<QString> &insertInfo);
    bool dbUpdate(QString updateInfo);
    QVector<QString> dbSelect(QString selectInfo);
    bool dbDelete(QString deleteInfo);
    bool dbDelete(QString number,QString type);
    bool dbTableCreate();
};

#endif // WEBBANKDATABASEMANIP_H
