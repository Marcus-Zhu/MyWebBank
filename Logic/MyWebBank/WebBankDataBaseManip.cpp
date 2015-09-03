#include "WebBankDataBaseManip.h"
#include <Qsql>
#include <QVector>
#include <QSqlQuery>
#include "WebBankCurrentUser.h"
#include <QString>
#include <QSqlDatabase>

bool DBUserManip::dbTableCreate(){
    QSqlQuery query;
    if(query.exec("CREATE TABLE user (key INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name VARCHAR(20),password VARCHAR(20),id VARCHAR(20),createdDate VARCHAR(20),tel VARCHAR(20),"
               "email VARCHAR(40),address VARCHAR(50),zipCode VARCHAR(10),type VARCHAR(10))"))
        return true;
    else
        return false;
}

bool DBUserManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO user (name,password,id,createdDate,tel,email,address,zipCode,type)"
                        "VALUES (?,?,?,?,?,?,?,?,?)");
    for(int i = 0;i<9;i++){
        query.addBindValue(insertInfo[i]);
    }
    if(query.exec())
        result = true;
    else
        result = false;
    return result;
}

bool DBUserManip::dbUpdate(QString updateInfo){
    QSqlQuery query;
    bool result;
    result = query.exec(QString("UPDATE user SET password = '%1' WHERE name = '%2'").arg(WCurrentUser::userName).arg(updateInfo));
    return result;
}

bool DBUserManip::dbDelete(QString deleteInfo){
    QSqlQuery query;
    bool result;
    result = query.exec(QString("DELETE FROM user WHERE name = '%1'").arg(deleteInfo));
    return result;
}
//核对用户的输入密码是否正确
bool DBUserManip::dbSelect(QString userName, QString userPassword){
    QSqlQuery query;
    if(!query.exec(QString("SELECT * FROM user WHERE name = '%1'").arg(userName)))
            qDebug()<<query.lastError();
    else{
        if(userPassword == query.value(2).toString())
            return true;
        else
            return false;
    }
}

//核对用户是否存在
bool DBUserManip::dbSelect(QString userName){
    QSqlQuery query;
    bool result;
    query.prepare("SELECT * FROM user WHERE name = :name");
    query.bindValue(":name",userName);
    result = query.exec();
    return result;
}

//返回useKey的值
int DBUserManip::dbSelectUserKey(){
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = :name");
    query.bindValue(":name",WCurrentUser::userName);
    query.exec();
    query.next();
    int userKey = query.value(0).toInt();
    return userKey;
}

bool DBAccountManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE account (key INTEGER PRIMARY KEY AUTOINCREMENT,"
             "userKey INTEGER,type VARCHAR(10),number VARCHAR(20),fixedDeposit REAL,"
             "currentDeposit REAL,status VARCHAR(10),createdTime TIMESTAMP default CURRENT_TIMESTAMP)");
    return result;
}

bool DBAccountManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO user (userKey,type,number,fixedDeposit,currentDeposit,status)"
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

//返回userKey的值
int DBAccountManip::dbSelectUserKey(QString number){
    QSqlQuery query;
    int key;
    query.prepare("SELECT userKey FROM account WHERE number = :number");
    query.bindValue(":number",number);
    query.exec();
    query.next();
    key = query.value(0).toInt();
    return key;
}

int DBAccountManip::dbSelectAccountKey(QString accountNumber){
    QSqlQuery query;
    int key;
    query.exec(QString("SELECT key FROM account WHERE number = '%1'").arg(accountNumber));
    key = query.value(0).toInt();
    return key;
}
//更新账户状态
bool DBAccountManip::dbUpdate(QString updateInfo){
    QSqlQuery query;
    bool result;
    if(query.exec(QString("SELECT FROM account WHERE number = '%1'").arg(updateInfo))){
        QString currentStatus = query.value(3).toString();
        if(currentStatus == "normal")
            result = query.exec(QString("UPDATE account SET status = 'frozen' WHERE number = '%1'").arg(updateInfo));
        else
            result = query.exec(QString("UPDATE account SET status = 'normal' WHERE number = '%1'").arg(updateInfo));
    }
    return result;
}
//更新账户余额
bool DBAccountManip::dbUpdate(QString updateInfo, float fixedDeposit, float currentDeposit){
   QSqlQuery query;
    bool result;
   result = query.exec(QString("UPDATE account SET fixedDeposit = %1, currentDeposit = %2 WHERE number = '%3'")
                       .arg(fixedDeposit).arg(currentDeposit).arg(updateInfo));
   return result;
}

bool DBAccountManip::dbUpdate(QString updateInfo, float sum){
    QSqlQuery query;
    bool result;
    float currentDeposit;
    query.exec(QString("SELECT fixedDeposit,currentDeposit FROM account WHERE number = '%1'").arg(updateInfo));
    query.next();
    currentDeposit = query.value(5).toFloat() + sum;
    query.prepare("UPDATE currentDeposit = :currentDeposit WHERE number = :number");
    query.bindValue(":currentDeposit",currentDeposit);
    query.bindValue(":number",updateInfo);
    result = query.exec();
    return result;
}

QString DBAccountManip::dbSelectAccountNumber(int key){
    QSqlQuery query;
    QString number;
    query.exec(QString("SELECT number FROM account WHERE key = %1").arg(key));
    query.next();
    number = query.value(0).toString();
    return number;
}

QVector<QString>& DBAccountManip::dbSelect(QString selectInfo) {
    QSqlQuery query;
    QVector<QString> accountInfo(6);
    if(query.exec(QString("SELECT * FROM account WHERE number = '%1'").arg(selectInfo)))
    {
        while(query.next()){
            for(int i = 0;i<6;i++)
                accountInfo.push_back(query.value(2 + i).toString());
            return accountInfo;
        }
    }
    else
        return accountInfo;
}

bool DBAccountManip::dbDelete(QString deleteInfo){
    QSqlQuery query;
    bool result;
    result = query.exec(QString("DELETE FROM account WHERE number = '%1'").arg(deleteInfo));
    return result;
}

bool DBTransactionRecordManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE transactionRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "accountKey1 INTEGER,accountKey2 INTEGER,sum REAL,time TIMESTAMP default CURRENT_TIMESTAMP,"
                        "fixedDeposit REAL,currentDeposit REAL,type VARCHAR(30))");
    return result;
}

bool DBTransactionRecordManip::dbInsert(QVector<QString>& insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare(QString("INSERT INTO transactionRecord (accountKey1,accountKey,"
                                "sum,fixedDeposit,currentDeposit,type) VALUES (?,?,?,?,?,?)"));
    query.addBindValue(insertInfo[0].toInt());
    query.addBindValue(insertInfo[1].toInt());
    query.addBindValue(insertInfo[2].toFloat());
    query.addBindValue(insertInfo[3].toFloat());
    query.addBindValue(insertInfo[4].toFloat());
    query.addBindValue(insertInfo[5]);
    result = query.exec();
    return result;
}

bool DBTransactionRecordManip::dbUpdate(QString updateInfo){
    return false;
}

QVector<QString>& DBTransactionRecordManip::dbSelect(QString selectInfo){
    QSqlQuery query;
    QVector<QString> transactionRecordInfo;
    query.exec(selectInfo);
    while(query.next()){
        transactionRecordInfo.push_back(DBAccountManip::dbSelectAccountNumber(query.value(1).toInt()));
        transactionRecordInfo.push_back(DBAccountManip::dbSelectAccountNumber(query.value(2).toInt()));
        transactionRecordInfo.push_back(query.value(3).toString());
        transactionRecordInfo.push_back(query.value(4).toString());
        transactionRecordInfo.push_back(query.value(5).toString());
        transactionRecordInfo.push_back(query.value(6).toString());
    }
    return transactionRecordInfo;
}

bool DBTransactionRecordManip::dbDelete(QString deleteInfo){
    return false;
}

bool DBPaymetnRecordManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE paymentReord (key INTEGER PRIMARY KEY AUTOINCREMENT,accountKey INTEGER,"
                        "sum REAL,time TIMESTAMP default CURRENT_TIMESTAMP,currentDeposit REAL,type VARCHAR[10])");
    return result;
}

bool DBPaymetnRecordManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    int accountKey;
    float balance;
    bool result;
    query.exec(QString("SELECT * FROM account WHERE number = '%1'").arg(insertInfo[0]));
    accountKey = query.value(0).toInt();
    balance = query.value(4).toFloat() - insertInfo[1].toFloat();
    query.prepare("INSERT INTO paymentRecord (accountKey,sum,balance type)"
                  "VALUES (?,?,?,?)");
    query.addBindValue(accountKey);
    query.addBindValue(insertInfo[1].toFloat());
    query.addBindValue(balance);
    query.addBindValue(insertInfo[2]);
    result = query.exec();
    return result;
}

bool DBPaymetnRecordManip::dbUpdate(QString updateInfo){
    return false;
}

QVector<QString>& DBPaymetnRecordManip::dbSelect(QString selectInfo){
    QSqlQuery query;
    QVector<QString> paymentRecordInfo;
    query.exec(selectInfo);
    while(query.next()){
        paymentRecordInfo.push_back(query.value(2).toString());
        paymentRecordInfo.push_back(query.value(3).toString());
        paymentRecordInfo.push_back(query.value(4).toString());
        paymentRecordInfo.push_back(query.value(5).toString());
    }
    return paymentRecordInfo;
}

bool DBPaymetnRecordManip::dbDelete(QString deleteInfo){
    return false;
}

bool DBMessageManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE message (key INTEGER PRIMARY KEY AUTOINCREMENT,userKey INTEGER,"
                        "time TIMESTAMP default CURRENT_TIMESTAMP,content VARCHAR(20),status VARCHAR(15))");
    return result;
}

bool DBMessageManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO message (userKey,content,status) VALUES (?,?,?)");
    query.addBindValue(DBUserManip::dbSelectUserKey());
    query.addBindValue(insertInfo[0]);
    query.addBindValue("not read");
}

bool DBMessageManip::dbUpdate(QString updateInfo){
    QSqlQuery query;
    bool result;
    result = query.exec("UPDATE FROM message SET status = 'already read'");
    return result;
}

QVector<QString>& DBMessageManip::dbSelect(QString selectInfo){
    QSqlQuery query;
    QVector<QString> messageInfo;
    query.exec(selectInfo);
    while(query.next()){
        messageInfo.push_back(WCurrentUser::userName);
        messageInfo.push_back(query.value(2).toString());
        messageInfo.push_back(query.value(3).toString());
        messageInfo.push_back(query.value(4).toString());
    }
    return messageInfo;
}

bool DBMessageManip::dbDelete(QString deleteInfo){
    return false;
}

bool DBLogRecordManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE logRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,userKey INTEGER"
                        "time TIMESTAMP default CURRENT_TIMESTAMP,type VARCHAR(10))");
    return result;
}

bool DBLogRecordManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO logRecord (userKey,type) VALUES (?,?)");
    query.addBindValue(DBUserManip::dbSelectUserKey());
    query.addBindValue(insertInfo[0]);
    result = query.exec();
    return result;
}

bool DBLogRecordManip::dbUpdate(QString updateInfo){
    return false;
}

bool DBLogRecordManip::dbDelete(QString deleteInfo){
    return false;
}

QVector<QString>& DBLogRecordManip::dbSelect(QString selectInfo){
    QSqlQuery query;
    query.exec(selectInfo);
    QVector<QString> logRecord;
    while(query.next()){
        logRecord.push_back(query.value(1).toString());
        logRecord.push_back(query.value(2).toString());
        logRecord.push_back(query.value(3).toString());
    }
    return logRecord;
}



