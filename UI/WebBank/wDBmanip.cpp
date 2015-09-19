#include "wDBmanip.h"
#include "wcurrentuser.h"

#include <Qsql>
#include <QVector>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QSqlDatabase>
#include <QDate>
#include <QDebug>

bool DBUserManip::dbTableCreate()
{
    QSqlQuery query;
    if(query.exec("CREATE TABLE user (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name VARCHAR(20),password VARCHAR(128),id VARCHAR(20),createdDate VARCHAR(20),tel VARCHAR(20),"
                  "email VARCHAR(40),address VARCHAR(50),zipCode VARCHAR(10),type VARCHAR(10))"))
        return true;
    else
        return false;
}

bool DBUserManip::dbInsert(QVector<QString> &insertInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO user (name,password,id,createdDate,tel,email,address,zipCode,type)"
                  "VALUES (?,?,?,?,?,?,?,?,?)");
    QDate date = QDate::currentDate();
    QString createdDate = date.toString("yyyy-MM-dd");
    insertInfo.insert(3, createdDate);
    for(int i = 0; i < 8; i++)
        query.addBindValue(QVariant(insertInfo[i]));
    long a = insertInfo[4].toLong();
    if(a % 2 == 0)
        query.addBindValue("normal");
    else
        query.addBindValue("VIP");
    if(query.exec())
        result = true;
    else
        result = false;
    return result;
}

bool DBUserManip::dbUpdate(QString updateInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("UPDATE user SET password = :password WHERE name = :name");
    query.bindValue(":password", updateInfo);
    query.bindValue(":name", WCurrentUser::userName);
    result = query.exec();
    return result;
}

bool DBUserManip::dbDelete(QString deleteInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("DELETE FROM user WHERE name = :name");
    query.bindValue(":name", deleteInfo);
    result = query.exec();
    return result;
}

bool DBUserManip::dbSelect(QString userName, QString userPassword)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = :name");
    query.bindValue(":name", userName);
    if(!query.exec())
        return false;
    else
    {
        query.next();
        if(userPassword == query.value(2).toString())
            return true;
        else
            return false;
    }
}

bool DBUserManip::dbSelect(QString userName)
{
    QSqlQuery query;
    bool result;
    query.prepare("SELECT * FROM user WHERE name = :name");
    query.bindValue(":name", userName);
    query.exec();
    result = false;
    while(query.next())
        result = true;
    return result;
}

int DBUserManip::dbSelectUserKey()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = :name");
    query.bindValue(":name", WCurrentUser::userName);
    query.exec();
    query.next();
    int userKey = query.value(0).toInt();
    return userKey;
}

bool DBAccountManip::dbTableCreate()
{
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE account (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "userKey INTEGER,type VARCHAR(10),number VARCHAR(20),fixedDeposit REAL,"
                        "currentDeposit REAL,status VARCHAR(10),createdTime TIMESTAMP NOT NULL default CURRENT_TIMESTAMP)");
    return result;
}

bool DBAccountManip::dbInsert(QVector<QString> &insertInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO account (userKey,type,number,fixedDeposit,currentDeposit,status)"
                  "VALUES (?,?,?,?,?,?)");
    query.addBindValue(DBUserManip::dbSelectUserKey());
    query.addBindValue(insertInfo[0]);
    query.addBindValue(insertInfo[1]);
    query.addBindValue(insertInfo[2].toFloat());
    query.addBindValue(insertInfo[3].toFloat());
    query.addBindValue(insertInfo[4]);
    result = query.exec();
    return result;
}

int DBAccountManip::dbSelectUserKey(QString number)
{
    QSqlQuery query;
    int key;
    query.prepare("SELECT userKey FROM account WHERE number = :number");
    query.bindValue(":number", number);
    query.exec();
    query.next();
    key = query.value(0).toInt();
    return key;
}

int DBAccountManip::dbSelectAccountKey(QString accountNumber)
{
    QSqlQuery query;
    int key;
    query.prepare("SELECT * FROM account WHERE number = :number");
    query.bindValue(":number", accountNumber);
    query.exec();
    query.next();
    key = query.value(0).toInt();
    return key;
}

bool DBAccountManip::dbUpdate(QString updateInfo)
{
    QSqlQuery query;
    bool result;
    if(query.exec(QString("SELECT * FROM account WHERE number = '%1'").arg(updateInfo)))
    {
        QString currentStatus = query.value(6).toString();
        if(currentStatus == "normal")
            result = query.exec(QString("UPDATE account SET status = 'frozen' WHERE number = '%1'").arg(updateInfo));
        else
            result = query.exec(QString("UPDATE account SET status = 'normal' WHERE number = '%1'").arg(updateInfo));
    }
    return result;
}

bool DBAccountManip::dbUpdate(QString updateInfo, float fixedDeposit, float currentDeposit)
{
    QSqlQuery query;
    bool result;
    query.prepare("UPDATE account SET fixedDeposit = :fixedDeposit,currentDeposit = :currentDeposit WHERE number = :number");
    query.bindValue(":fixedDeposit", fixedDeposit);
    query.bindValue(":currentDeposit", currentDeposit);
    query.bindValue(":number", updateInfo);
    result = query.exec();
    return result;
}

bool DBAccountManip::dbUpdate(QString updateInfo, float sum)
{
    QSqlQuery query;
    bool result;
    float currentDeposit;
    query.prepare("SELECT fixedDeposit,currentDeposit FROM account WHERE number = :number");
    query.bindValue(":number", updateInfo);
    query.exec();
    query.next();
    currentDeposit = query.value(1).toFloat() + sum;
    query.prepare("UPDATE currentDeposit = :currentDeposit WHERE number = :number");
    query.bindValue(":currentDeposit", currentDeposit);
    query.bindValue(":number", updateInfo);
    result = query.exec();
    return result;
}

bool DBAccountManip::dbPaymentUpdate(QString number, float currentDeposit)
{
    QSqlQuery query;
    query.prepare("UPDATE account SET currentDeposit = :currentDeposit WHERE number = :number");
    query.bindValue(":currentDeposit", currentDeposit);
    query.bindValue(":number", number);
    bool result = query.exec();
    return result;
}

QString DBAccountManip::dbSelectAccountNumber(int key)
{
    QSqlQuery query;
    QString number;
    query.prepare("SELECT number FROM account WHERE key = :key");
    query.bindValue(":key", key);
    query.exec();
    query.next();
    number = query.value(0).toString();
    return number;
}

QVector<QString> DBAccountManip::dbSelect(QString selectInfo)
{
    QSqlQuery query;
    QVector<QString> accountInfo;
    query.prepare("SELECT * FROM account WHERE number = :number");
    query.bindValue(":number", selectInfo);
    if(query.exec())
    {
        while(query.next())
        {
            for(int i = 0; i < 6; i++)
            {
                if(i == 2 || i == 3)
                {
                    float f = query.value(2 + i).toFloat();
                    accountInfo.push_back(QString::number(f, 'f', 2));
                }
                else
                    accountInfo.push_back(query.value(2 + i).toString());
            }
            return accountInfo;
        }
    }
    return accountInfo;
}

QVector<QString> DBAccountManip::dbSelect(int num)
{
    QVector<QString> info;
    QSqlQuery query;
    query.prepare("SELECT * FROM account WHERE userKey = ?");
    query.addBindValue(DBUserManip::dbSelectUserKey());
    query.exec();
    for(int i = 0; i <= num; i++)
        query.next();
    for(int i = 0; i < 5; i++)
    {
        if(i == 2 || i == 3)
        {
            float f = query.value(2 + i).toFloat();
            info.push_back(QString::number(f, 'f', 2));
        }
        else
            info.push_back(query.value(2 + i).toString());
    }
    return info;
}

bool DBAccountManip::dbSelectAccount(QString number)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM account WHERE number = ?");
    query.addBindValue(number);
    while(query.next())
        return true;
    return false;
}

bool DBAccountManip::dbDelete(QString deleteInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("DELETE FROM account WHERE number = :number");
    query.bindValue(":number", deleteInfo);
    result = query.exec();
    return result;
}

bool DBTransactionRecordManip::dbTableCreate()
{
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE transactionRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "accountKey1 INTEGER,accountKey2 INTEGER,sum REAL,time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,"
                        "fixedDeposit REAL,currentDeposit REAL,type VARCHAR(30))");
    return result;
}

bool DBTransactionRecordManip::dbInsert(QVector<QString> &insertInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO transactionRecord (accountKey1,accountKey2,"
                  "sum,fixedDeposit,currentDeposit,type) VALUES (?,?,?,?,?,?)");

    int key = DBAccountManip::dbSelectAccountKey(insertInfo[0]);
    query.addBindValue(key);
    key = DBAccountManip::dbSelectAccountKey(insertInfo[1]);
    query.addBindValue(key);
    query.addBindValue(insertInfo[2].toFloat());
    query.addBindValue(insertInfo[3].toFloat());
    query.addBindValue(insertInfo[4].toFloat());
    query.addBindValue(insertInfo[5]);
    result = query.exec();
    return result;
}

bool DBTransactionRecordManip::dbUpdate(QString updateInfo)
{
    return false;
}

QVector<QString> DBTransactionRecordManip::dbSelect(QString selectInfo)
{
    QSqlQuery query;
    QVector<QString> transactionRecordInfo;
    if(!query.exec(selectInfo))
        qDebug() << query.lastError();
    else
    {
        while(query.next())
        {
            QString content[7];
            QString number1 = DBAccountManip::dbSelectAccountNumber(query.value(1).toInt());
            QString number2 = DBAccountManip::dbSelectAccountNumber(query.value(2).toInt());
            content[0] = number1;
            content[1] = number2;
            for(int i = 2; i < 7; i++)
            {
                if(i == 2 || i == 4 || i == 5)
                {
                    float f = query.value(i + 1).toFloat();
                    content[i] = QString::number(f, 'f', 2);
                }
                else
                    content[i] = query.value(1 + i).toString();
            }
            for(int i = 0; i < 7; i++)
                transactionRecordInfo.push_back(content[i]);
        }
    }
    return transactionRecordInfo;
}

QVector<QString> DBTransactionRecordManip::dbSelect(QString selectInfo, int cols)
{
    QSqlQuery query;
    QVector<QString> transactionRecords;
    if(!query.exec(selectInfo))
        qDebug() << query.lastError();
    else
    {
        while(query.next())
        {
            QString content[3];
            for(int i = 0; i < cols; i++)
            {
                if(i == 0)
                {
                    float f = query.value(0).toFloat();
                    content[i] = QString::number(f, 'f', 2);
                }
                else
                    content[i] = query.value(i).toString();
            }
            for(int i = 0; i < cols; i++)
                transactionRecords.push_back(content[i]);
        }
    }
    return transactionRecords;
}

bool DBTransactionRecordManip::dbDelete(QString deleteInfo)
{
    return false;
}

bool DBPaymentRecordManip::dbTableCreate()
{
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE paymentRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,accountKey INTEGER,"
                        "sum REAL,time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,currentDeposit REAL,type VARCHAR[10])");
    return result;
}

bool DBPaymentRecordManip::dbInsert(QVector<QString> &insertInfo)
{
    //0--accountNumber,1--sum,2--type,3--currentDeposit
    QSqlQuery query;
    int accountKey;
    bool result;
    accountKey = DBAccountManip::dbSelectAccountKey(insertInfo[0]);
    query.prepare("INSERT INTO paymentRecord (accountKey,sum,currentDeposit,type) "
                  "VALUES (?,?,?,?)");
    query.addBindValue(accountKey);
    query.addBindValue(insertInfo[1].toFloat());
    query.addBindValue(insertInfo[3].toFloat());
    query.addBindValue(insertInfo[2]);
    result = query.exec();
    return result;
}

bool DBPaymentRecordManip::dbUpdate(QString updateInfo)
{
    bool result;
    QSqlQuery query;
    result = query.exec(updateInfo);
    return result;
}

QVector<QString> DBPaymentRecordManip::dbSelect(QString selectInfo)
{
    QSqlQuery query;
    QVector<QString> paymentRecordInfo;
    if(!query.exec(selectInfo))
        qDebug() << query.lastError();
    else
    {
        while(query.next())
        {
            int key = query.value(1).toInt();
            QString number = DBAccountManip::dbSelectAccountNumber(key);
            QString content[4];
            paymentRecordInfo.push_back(number);
            for(int i = 0; i < 4; i++)
            {
                if(i == 0 || i == 2)
                {
                    float f = query.value(i).toFloat();
                    content[i] = QString::number(f, 'f', 2);
                }
                else
                    content[i] = query.value(i + 2).toString();
            }
            for(int i = 0; i < 4; i++)
                paymentRecordInfo.push_back(content[i]);
        }
    }
    return paymentRecordInfo;
}

QVector<QString> DBPaymentRecordManip::dbSelect(QString selectInfo, int cols)
{
    QSqlQuery query;
    QVector<QString> paymentRecords;
    if(!query.exec(selectInfo))
        qDebug() << query.lastError();
    else
    {
        while(query.next())
        {
            QString content[3];
            for(int i = 0; i < cols; i++)
            {
                if(i == 0)
                {
                    float f = query.value(0).toFloat();
                    content[i] = QString::number(f, 'f', 2);
                }
                else
                    content[i] = query.value(i).toString();
            }
            for(int i = 0; i < cols; i++)
                paymentRecords.push_back(content[i]);
        }
    }
    return paymentRecords;
}

bool DBPaymentRecordManip::dbDelete(QString deleteInfo)
{
    return false;
}

int DBPaymentRecordManip::dbSelectMaxKey()
{
    int key;
    QSqlQuery query;
    query.exec("SELECT max(key) FROM paymentRecord");
    query.next();
    key = query.value(0).toInt();
    return key;
}

bool DBMessageManip::dbTableCreate()
{
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE message (key INTEGER PRIMARY KEY AUTOINCREMENT,userKey INTEGER,"
                        "time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,content VARCHAR(20),status VARCHAR(15) default not_read)");
    return result;
}

bool DBMessageManip::dbInsert(QVector<QString> &insertInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO message (userKey,content,status) VALUES (?,?,?)");
    if(insertInfo.size() == 3)
    {
        query.addBindValue(insertInfo[0].toInt());
        query.addBindValue(insertInfo[2]);
        query.addBindValue("not read");
        result = query.exec();
        if(result)
        {
            int key;
            query.exec("SELECT max(key) FROM message");
            query.next();
            key = query.value(0).toInt();
            QString str = QString("datetime('now','-%1 month')").arg(insertInfo[1]);
            QString updateInfo = QString("UPDATE message SET time = %1 WHERE key = %2").arg(str).arg(key);
            result = query.exec(updateInfo);
        }
    }
    else
    {
        query.addBindValue(insertInfo[0].toInt());
        query.addBindValue(insertInfo[1]);
        query.addBindValue("not read");
        result = query.exec();
    }
    return result;
}

bool DBMessageManip::dbUpdate(QString updateInfo)
{
    updateInfo;
    QSqlQuery query;
    bool result;
    int key = DBUserManip::dbSelectUserKey();
    query.prepare("UPDATE message SET status = 'read' WHERE userKey = ? ");
    query.addBindValue(key);
    result = query.exec();
    return result;
}

QVector<QString> DBMessageManip::dbSelect()
{
    QSqlQuery query;
    QVector<QString> messageInfo;
    int key = DBUserManip::dbSelectUserKey();
    query.prepare("SELECT * FROM message WHERE userKey = ?");
    query.addBindValue(key);
    query.exec();
    while(query.next())
    {
        messageInfo.push_back(query.value(2).toString());
        messageInfo.push_back(query.value(3).toString());
    }
    return messageInfo;
}

bool DBMessageManip::dbDelete(QString deleteInfo)
{
    return false;
}

int DBMessageManip::dbSelectMessageAmount()
{
    QSqlQuery query;
    int key = DBUserManip::dbSelectUserKey();
    query.prepare("SELECT key FROM message WHERE status = 'not read' AND userKey = ?");
    query.addBindValue(key);
    query.exec();
    int amount = 0;
    while(query.next())
    {
        amount++;
    }
    return amount;
}

bool DBLogRecordManip::dbTableCreate()
{
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE logRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,userKey INTEGER,"
                        "time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,type VARCHAR(10))");
    return result;
}

bool DBLogRecordManip::dbInsert(QVector<QString> &insertInfo)
{
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO logRecord (userKey,type) VALUES (?,?)");
    query.addBindValue(DBUserManip::dbSelectUserKey());
    query.addBindValue(insertInfo[0]);
    result = query.exec();
    return result;
}

bool DBLogRecordManip::dbUpdate(QString updateInfo)
{
    return false;
}

bool DBLogRecordManip::dbDelete(QString deleteInfo)
{
    return false;
}

QVector<QString> DBLogRecordManip::dbSelect(QString selectInfo)
{
    QSqlQuery query;
    query.exec(selectInfo);
    QVector<QString> logRecord;
    while(query.next())
    {
        logRecord.push_back(query.value(1).toString());
        logRecord.push_back(query.value(2).toString());
        logRecord.push_back(query.value(3).toString());
    }
    return logRecord;
}

bool DBAutoPayManip::dbTableCreate()
{
    bool result;
    QSqlQuery query;
    result = query.exec("CREATE TABLE autoPay (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "accountKey INTEGER, type VARCHAR(15),lastPayDate VARCHAR(20))");
    return result;
}

bool DBAutoPayManip::dbInsert(QVector<QString> &insertInfo)
{
    bool result;
    QSqlQuery query;
    QString date;
    query.prepare("INSERT INTO autoPay (accountKey,type,lastPayDate) VALUES (?,?,?)");
    int accountKey = DBAccountManip::dbSelectAccountKey(insertInfo[0]);
    query.addBindValue(accountKey);
    query.addBindValue(insertInfo[1]);
    date = QDate::currentDate().toString("yyyy-MM-dd");
    query.addBindValue(date);
    result = query.exec();
    return result;
}

QVector<QString> DBAutoPayManip::dbSelect()
{
    QSqlQuery query;
    QVector<QString> info;
    QString number;
    int key = DBUserManip::dbSelectUserKey();
    query.prepare("SELECT number FROM account WHERE userKey = ?");
    query.addBindValue(key);
    query.exec();
    while(query.next())
    {
        number = query.value(0).toString();
        key = DBAccountManip::dbSelectAccountKey(number);
        QSqlQuery query1;
        query1.prepare("SELECT * FROM autoPay WHERE accountKey = ?");
        query1.addBindValue(key);
        query1.exec();
        while(query1.next())
        {
            info.push_back(number);
            info.push_back(query1.value(2).toString());
            info.push_back(query1.value(3).toString());
        }
    }
    return info;
}

QVector<QString> DBAutoPayManip::dbSelect(QString selectInfo)
{
    QVector<QString> autoPayInfo;
    QSqlQuery query;
    query.exec(selectInfo);
    while(query.next())
    {
        int key = query.value(1).toInt();
        autoPayInfo.push_back(DBAccountManip::dbSelectAccountNumber(key));
        autoPayInfo.push_back(query.value(2).toString());
        autoPayInfo.push_back(query.value(3).toString());
    }
    return autoPayInfo;
}

bool DBAutoPayManip::dbUpdate(QString updateInfo)
{
    bool result;
    QSqlQuery query;
    result = query.exec(updateInfo);
    return result;
}

bool DBAutoPayManip::dbDelete(QString deleteInfo)
{
    return false;
}

bool DBAutoPayManip::dbDelete(QString number, QString type)
{
    bool result;
    QSqlQuery query;
    int accountKey = DBAccountManip::dbSelectAccountKey(number);
    query.prepare("DELETE FROM autoPay WHERE accountKey = ? AND type = ?");
    query.addBindValue(accountKey);
    query.addBindValue(type);
    result = query.exec();
    return result;
}

bool DBAutoPayManip::dbSelectAutoPayment(QString number, QString type)
{
    QSqlQuery query;
    query.prepare("SELECT type FROM autoPay WHERE accountKey = ?");
    int accountKey = DBAccountManip::dbSelectAccountKey(number);
    query.addBindValue(accountKey);
    bool result = query.exec();
    if(result)
    {
        while(query.next())
        {
            if(type == query.value(0).toString())
                return false;
        }
    }
    return result;
}

bool DBAutoPayManip::dbSelectAutoPayment(QString type)
{
    QSqlQuery query1;
    int userKey = DBUserManip::dbSelectUserKey();
    QVector<QString> numbers;
    query1.prepare("SELECT number FROM account WHERE userKey = ?");
    query1.addBindValue(userKey);
    query1.exec();
    if(!query1.next())
        return true;
    else
        numbers.push_back(query1.value(0).toString());
    while(query1.next())
        numbers.push_back(query1.value(0).toString());
    for(int i = 0; i < numbers.size(); i++)
    {
        int accountKey = DBAccountManip::dbSelectAccountKey(numbers[i]);
        QSqlQuery query2;
        query2.prepare("SELECT type FROM autoPay WHERE accountKey = ?");
        query2.addBindValue(accountKey);
        query2.exec();
        while(query2.next())
        {
            if(query2.value(0).toString() == type)
                return false;
        }
    }
    return true;
}
