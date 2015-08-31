#include "WebBankDataBaseManip.h"
#include <Qsql>
#include <QVector>
#include <QSqlQuery>
#include "WebBankCurrentUser.h"

bool DBUserManip::dbTableCreate(){
    if(query.exec("CREATE TABLE user (key INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name VARCHAR(20),password VARCHAR(20),id VARCHAR(20),createdDate VARCHAR(20),tel VARCHAR(20),"
               "email VARCHAR(40),address VARCHAR(50),zipCode VARCHAR(10),type VARCHAR(10))"))
        return true;
    else
        return false;
}

bool DBUserManip::dbInsert(QVector<QString> insertInfo){
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
    bool result;
    result = query.exec(QString("UPDATE user SET password = %1 WHERE name = %2").arg(WCurrentUser::getUserName()).arg(userInfo));
    return result;
}

bool DBUserManip::dbDelete(QString deleteInfo){
    bool result;
    result = query.exec(QString("DELETE FROM user WHERE name = %1").arg(deleteInfo));
    return result;
}
//核对用户的输入密码是否正确
bool DBUserManip::dbSelect(QString userName, QString userPassword){
    if(!query.exec(QString("SELECT * FROM user WHERE name = %1").arg(userName)))
            qDebug()<<query.lastError();
    else{
        if(userPassword == query.value(2).toString())
            return true;
        else
            return false;
    }
}
//返回useKey的值
int DBUserManip::dbSelect(){
    query.exec(QString("SELECT * FROM user WHERE name = %1").arg(WCurrentUser::getUserName()));
    int userKey = query.value(0).toInt();
    return userKey;
}

bool DBAccountManip::dbTableCreate(){
    bool result;
    result = query.exec("CREATE TABLE account (key INTEGER PRIMARY KEY AUTOINCREMENT,"
             "userKey INTEGER,type VARCHAR(10),number VARCHAR(20),"
             "balance REAL,status VARCHAR(10),createdTime TIMESTAMP default CURRENT_TIMESTAMP)");
    return result;
}

bool DBAccountManip::dbInsert(QVector<QString> insertInfo){
    bool result;
    query.prepare("INSERT INTO user (userKey,type,number,balance,status)"
                        "VALUES (?,?,?,?,?)");
    query.addBindValue(DBUserManip::dbSelect());
    query.addBindValue(insertInfo[0]);
    query.addBindValue(insertInfo[1]);
    query.addBindValue(insertInfo[2].toFloat());
    query.addBindValue(insertInfo[3]);
    result = query.exec();
    return result;
}
//更新账户状态
bool DBAccountManip::dbUpdate(QString updateInfo){
    bool result;
    if(query.exec(QString("SELECT FROM account WHERE number = %1").arg(updateInfo))){
        QString currentStatus = query.value(3).toString();
        if(currentStatus == "normal")
            result = query.exec(QString("UPDATE account SET status = frozen WHERE number = %1").arg(updateInfo));
        else
            result = query.exec(QString("UPDATE account SET status = normal WHERE number = %1").arg(updateInfo));
    }
    return result;
}
//更新账户余额
bool DBAccountManip::dbUpdate(QString updateInfo,QString updateBalance){
   bool result;
   result = query.exec(QString("UPDATE account SET balance = %1 WHERE number = %2").arg(updateBalance.toFloat()).arg(updateInfo));
   return result;
}

QVector<QString> DBAccountManip::dbSelect(QString selectInfo) {
    QVector<QString> accountInfo = new QVector<QString>(7);
    if(query.exec(QString("SELECT * FROM account WHERE number = %1").arg(selectInfo)))
    {
        for(int i = 0;i<5;i++)
            accountInfo[i] = query.value(2 + i).toString();
        return accountInfo;
    }
    else
        return NULL;
}

bool DBAccountManip::dbDelete(QString deleteInfo){
    bool result;
    result = query.exec(QString("DELETE FROM account WHERE number = %1").arg(deleteInfo));
    return result;
}

bool DBTransactionRecordManip::dbTableCreate(){
    bool result;
    result = query.exec("CREATE TABLE transactionRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "accountKey1 INTEGER,accountKey2 INTEGER,sum REAL,"
                        "time TIMESTAMP default CURRENT_TIMESTAMP,balance REAL)");
    return result;
}

bool DBTransactionRecordManip::dbInsert(QVector<QString> insertInfo){
    bool result;
    query.prepare(QString("INSERT INTO transactionRecord (accountKey1,accountKey,"
                                "sum,balance,type) VALUES (?,?,?,?,?)"));
    query.addBindValue(insertInfo[0].toInt());
    query.addBindValue(insertInfo[1].toInt());
    query.addBindValue(insertInfo[2].toFloat());
    query.addBindValue(insertInfo[3].toFloat());
    query.addBindValue(insertInfo[4]);
    result = query.exec();
    return result;
}

bool DBTransactionRecordManip::dbUpdate(QString updateInfo){
    return false;
}

QVector<QString> DBTransactionRecordManip::dbSelect(QString selectInfo){
    QVector<QString> transactionRecordInfo = new QVector<QString>;
    query.exec(selectInfo);
    while(query.next()){
        transactionRecordInfo.push_back(query.value(3).toString());
        transactionRecordInfo.push_back(query.value(4).toString());
        transactionRecordInfo.push_back(query.value(5).toString());
    }
    return transactionRecordInfo;
}

bool DBTransactionRecordManip::dbDelete(QString deleteInfo){
    bool result;
    result = query.exec(QString("DELETE FROM transactionRecord WHERE number = %1").arg(deleteInfo));
    return result;
}

bool DBPaymetnRecordManip::dbTableCreate(){
    bool result;
    result = query.exec("CREATE TABLE paymentReord (key INTEGER PRIMARY KEY AUTOINCREMENT,accountKey INTEGER,"
                        "sum REAL,time TIMESTAMP default CURRENT_TIMESTAMP,balance REAL,type VARCHAR[10])");
    return result;
}

bool DBPaymetnRecordManip::dbInsert(QVector<QString> insertInfo){
    int accountKey;
    float balance;
    bool result;
    query.exec(QString("SELECT * FROM account WHERE number = %1").arg(insertInfo[0]));
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

QVector<QString> DBPaymetnRecordManip::dbSelect(QString selectInfo){
    QVector<QString> paymentRecordInfo = new QVector<QString>;
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
    bool result;
    result = query.exec("CREATE TABLE message (key INTEGER PRIMARY KEY AUTOINCREMENT,userKey INTEGER,"
                        "time TIMESTAMP default CURRENT_TIMESTAMP,content VARCHAR(20),status VARCHAR(15))");
    return result;
}

bool DBMessageManip::dbInsert(QVector<QString> insertInfo){
    bool result;
    query.prepare("INSERT INTO message (userKey,content,status) VALUES (?,?,?)");
    query.addBindValue(DBUserManip::dbSelect());
    query.addBindValue(insertInfo[0]);
    query.addBindValue("not read");
}

bool DBMessageManip::dbUpdate(QString updateInfo){
    bool result;
    result = query.exec("UPDATE FROM message SET status = 'already read'");
    return result;
}

QVector<QString> DBMessageManip::dbSelect(QString selectInfo){
    QVector<QString> messageInfo = new QVector<QString>;
    query.exec(selectInfo);
    while(query.next()){
        messageInfo.push_back(WCurrentUser::getUserName());
        messageInfo.push_back(query.value(2).toString());
        messageInfo.push_back(query.value(3).toString());
        messageInfo.push_back(query.value(4).toString());
    }
    return messageInfo;
}

bool DBMessageManip::dbDelete(QString deleteInfo){
    return false;
}






