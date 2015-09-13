#include "WebBankDataBaseManip.h"
#include <Qsql>
#include <QVector>
#include <QSqlQuery>
#include "WebBankCurrentUser.h"
#include <QString>
#include <QSqlDatabase>
#include <QDate>

//创建user表
bool DBUserManip::dbTableCreate(){
    QSqlQuery query;
    if(query.exec("CREATE TABLE user (key INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name VARCHAR(20),password VARCHAR(128),id VARCHAR(20),createdDate VARCHAR(20),tel VARCHAR(20),"
               "email VARCHAR(40),address VARCHAR(50),zipCode VARCHAR(10),type VARCHAR(10))"))
        return true;
    else
        return false;
}

//注册时向user表中插入一条新信息
bool DBUserManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO user (name,password,id,createdDate,tel,email,address,zipCode,type)"
                        "VALUES (?,?,?,?,?,?,?,?,?)");
    QDate date = QDate::currentDate();
    QString createdDate = date.toString();
    insertInfo.insert(3,createdDate);
    for(int i = 0;i<8;i++)
        query.addBindValue(insertInfo[i]);
    long a = insertInfo[4].toLong();
    if(a%2 == 0)
        query.addBindValue("normal");
    else
        query.addBindValue("VIP");
    if(query.exec())
        result = true;
    else
        result = false;
    return result;
}

//更新用户密码
bool DBUserManip::dbUpdate(QString updateInfo){
    QSqlQuery query;
    bool result;
    query.prepare("UPDATE user SET password = :password WHERE name = :name");
    query.bindValue(":password",updateInfo);
    query.bindValue(":name",WCurrentUser::userName);
    result = query.exec();
    return result;
}

//删除用户信息，不过貌似不需要，但是继承来必须实现
bool DBUserManip::dbDelete(QString deleteInfo){
    QSqlQuery query;
    bool result;
    query.prepare("DELETE FROM user WHERE name = :name");
    query.bindValue(":name",deleteInfo);
    result = query.exec();
    return result;
}
//核对用户的输入密码是否正确
bool DBUserManip::dbSelect(QString userName, QString userPassword){
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = :name");
    query.bindValue(":name",userName);
    if(!query.exec())
            qDebug()<<query.lastError();
    else{
        query.next();
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

//创建account表
bool DBAccountManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE account (key INTEGER PRIMARY KEY AUTOINCREMENT,"
             "userKey INTEGER,type VARCHAR(10),number VARCHAR(20),fixedDeposit REAL,"
             "currentDeposit REAL,status VARCHAR(10),createdTime TIMESTAMP NOT NULL default CURRENT_TIMESTAMP)");
    return result;
}

//向account表插入一条数据
bool DBAccountManip::dbInsert(QVector<QString> &insertInfo){
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

//通过number获取accountKey的值
int DBAccountManip::dbSelectAccountKey(QString accountNumber){
    QSqlQuery query;
    int key;
    query.prepare("SELECT * FROM account WHERE number = :number");
    query.bindValue(":number",accountNumber);
    query.exec();
    query.next();
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

//更新现在正在操作的账户的余额
bool DBAccountManip::dbUpdate(QString updateInfo, float fixedDeposit, float currentDeposit){
   QSqlQuery query;
   bool result;
   query.prepare("UPDATE account SET fixedDeposit = :fixedDeposit,currentDeposit = :currentDeposit WHERE number = :number");
   query.bindValue(":fixedDeposit",fixedDeposit);
   query.bindValue(":currentDeposit",currentDeposit);
   query.bindValue(":number",updateInfo);
   result = query.exec();
   return result;
}

//更新被转账的账户的余额
bool DBAccountManip::dbUpdate(QString updateInfo, float sum){
    QSqlQuery query;
    bool result;
    float currentDeposit;
    query.prepare("SELECT fixedDeposit,currentDeposit FROM account WHERE number = :number");
    query.bindValue(":number",updateInfo);
    query.exec();
    query.next();
    currentDeposit = query.value(1).toFloat() + sum;
    query.prepare("UPDATE currentDeposit = :currentDeposit WHERE number = :number");
    query.bindValue(":currentDeposit",currentDeposit);
    query.bindValue(":number",updateInfo);
    result = query.exec();
    return result;
}

//缴费后更新account的余额
bool DBAccountManip::dbPaymentUpdate(QString number, float currentDeposit){
    QSqlQuery query;
    query.prepare("UPDATE account SET currentDeposit = :currentDeposit WHERE number = :number");
    query.bindValue(":currentDeposit",currentDeposit);
    query.bindValue(":number",number);
    bool result = query.exec();
    return result;
}

//通过accountKey获取number
QString DBAccountManip::dbSelectAccountNumber(int key){
    QSqlQuery query;
    QString number;
    query.prepare("SELECT number FROM account WHERE key = :key");
    query.bindValue(":key",key);
    query.exec();
    query.next();
    number = query.value(0).toString();
    return number;
}

//查询某一number对应account的所有信息
QVector<QString> DBAccountManip::dbSelect(QString selectInfo) {
    QSqlQuery query;
    QVector<QString> accountInfo;
    query.prepare("SELECT * FROM account WHERE number = :number");
    query.bindValue(":number",selectInfo);
    if(query.exec())
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

//删除某一account
bool DBAccountManip::dbDelete(QString deleteInfo){
    QSqlQuery query;
    bool result;
    query.prepare("DELETE FROM account WHERE number = :number");
    query.bindValue(":number",deleteInfo);
    result = query.exec();
    return result;
}

//创建表
bool DBTransactionRecordManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE transactionRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "accountKey1 INTEGER,accountKey2 INTEGER,sum REAL,time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,"
                        "fixedDeposit REAL,currentDeposit REAL,type VARCHAR(30))");
    return result;
}

//插入信息
bool DBTransactionRecordManip::dbInsert(QVector<QString>& insertInfo){
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

//更新transaction表的信息，不可用
bool DBTransactionRecordManip::dbUpdate(QString updateInfo){
    return false;
}

//查询某个number对应account的所有交易记录
QVector<QString> DBTransactionRecordManip::dbSelect(QString selectInfo){
    QSqlQuery query;
    QVector<QString> transactionRecordInfo;
    if(!query.exec(selectInfo))
        qDebug()<<query.lastError();
    else{
        while(query.next()){
            QString content[7];
            QString number1 = DBAccountManip::dbSelectAccountNumber(query.value(1).toInt());
            QString number2 = DBAccountManip::dbSelectAccountNumber(query.value(2).toInt());
            content[0] = number1;
            content[1] = number2;
            for(int i = 2;i<7;i++)
                content[i] = query.value(i+1).toString();
            for(int i = 0;i<7;i++)
                transactionRecordInfo.push_back(content[i]);
        }
    }
    return transactionRecordInfo;
}

//输入第一个参数代表SQL语句，第二个是表示select了cols列的信息
QVector<QString> DBTransactionRecordManip::dbSelect(QString selectInfo, int cols){
    QSqlQuery query;
    QVector<QString> transactionRecords;
    if(!query.exec(selectInfo))
        qDebug()<<query.lastError();
    else
    {
        while(query.next()){
            QString content[cols];
            for(int i = 0;i<cols;i++)
                content[i] = query.value(i).toString();
            for(int i = 0;i<cols;i++)
                transactionRecords.push_back(content[i]);
        }
    }
    return transactionRecords;
}

//删除交易信息，不可用
bool DBTransactionRecordManip::dbDelete(QString deleteInfo){
    return false;
}

//创建表
bool DBPaymentRecordManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE paymentRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,accountKey INTEGER,"
                        "sum REAL,time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,currentDeposit REAL,type VARCHAR[10])");
    return result;
}

//插入信息
bool DBPaymentRecordManip::dbInsert(QVector<QString> &insertInfo){
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

//更新信息，不可用
bool DBPaymentRecordManip::dbUpdate(QString updateInfo){
    return false;
}

//查询信息，查询某个信息所在行的所有列的信息，除key外全部返回，accountKey转为了number
QVector<QString> DBPaymentRecordManip::dbSelect(QString selectInfo){
    QSqlQuery query;
    QVector<QString> paymentRecordInfo;
    if(!query.exec(selectInfo))
        qDebug()<<query.lastError();
    else{
        while(query.next()){
            int key = query.value(1).toInt();
            QString number = DBAccountManip::dbSelectAccountNumber(key);
            QString content[4];
            paymentRecordInfo.push_back(number);
            for(int i = 0;i<4;i++)
                content[i] = query.value(i + 2).toString();
            for(int i = 0;i<4;i++)
                paymentRecordInfo.push_back(content[i]);
        }
    }
    return paymentRecordInfo;
}

//查询cols列的信息并返回
QVector<QString> DBPaymentRecordManip::dbSelect(QString selectInfo, int cols){
    QSqlQuery query;
    QVector<QString> paymentRecords;
    if(!query.exec(selectInfo))
        qDebug()<<query.lastError();
    else{
        while(query.next()){
            QString content[cols];
            for(int i = 0; i<cols;i++)
                content[i] = query.value(i).toString();
            for(int i = 0;i<cols;i++)
                paymentRecords.push_back(content[i]);
        }
    }
    return paymentRecords;
}

//删除信息，不可用
bool DBPaymentRecordManip::dbDelete(QString deleteInfo){
    return false;
}

//创建表
bool DBMessageManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE message (key INTEGER PRIMARY KEY AUTOINCREMENT,userKey INTEGER,"
                        "time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,content VARCHAR(20),status VARCHAR(15) default not_read)");
    return result;
}

//插入信息
bool DBMessageManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO message (userKey,content,status) VALUES (?,?,?)");
    query.addBindValue(insertInfo[0].toInt());
    query.addBindValue(insertInfo[1]);
    query.addBindValue("not read");
    result = query.exec();
    return result;
}

//更新信息的状态
bool DBMessageManip::dbUpdate(QString updateInfo){
    QSqlQuery query;
    bool result;
    result = query.exec(updateInfo);
    return result;
}

//选择信息
QVector<QString> DBMessageManip::dbSelect(QString selectInfo){
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

//删除信息记录，不可用
bool DBMessageManip::dbDelete(QString deleteInfo){
    return false;
}

//返回未读信息条数
int DBMessageManip::dbSelectMessageAmount(){
    QSqlQuery query;
    query.exec("SELECT FROM message WHERE status = 'not_read'");
    int amount = 0;
    while(query.next()){
        amount++;
    }
    return amount;
}

//创建表
bool DBLogRecordManip::dbTableCreate(){
    QSqlQuery query;
    bool result;
    result = query.exec("CREATE TABLE logRecord (key INTEGER PRIMARY KEY AUTOINCREMENT,userKey INTEGER"
                        "time TIMESTAMP NOT NULL default CURRENT_TIMESTAMP,type VARCHAR(10))");
    return result;
}

//插入信息
bool DBLogRecordManip::dbInsert(QVector<QString> &insertInfo){
    QSqlQuery query;
    bool result;
    query.prepare("INSERT INTO logRecord (userKey,type) VALUES (?,?)");
    query.addBindValue(DBUserManip::dbSelectUserKey());
    query.addBindValue(insertInfo[0]);
    result = query.exec();
    return result;
}

//更新信息，不可用
bool DBLogRecordManip::dbUpdate(QString updateInfo){
    return false;
}

//删除信息，不可用
bool DBLogRecordManip::dbDelete(QString deleteInfo){
    return false;
}

//查询信息
QVector<QString> DBLogRecordManip::dbSelect(QString selectInfo){
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

//创建表
bool DBAutoPayManip::dbTableCreate(){
    bool result;
    QSqlQuery query;
    result = query.exec("CREATE TABLE autoPay (key INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "accountKey INTEGER, type VARCHAR(15),lastPayDate VARCHAR(20))");
    return result;
}

//插入信息
bool DBAutoPayManip::dbInsert(QVector<QString> &insertInfo){
    bool result;
    QSqlQuery query;
    QString date;
    query.prepare("INSERT INTO autoPay (accountKey,type,lastPayDate) VALUES (?,?,?)");
    int accountKey = DBAccountManip::dbSelectAccountKey(insertInfo[0]);
    query.addBindValue(accountKey);
    query.addBindValue(insertInfo[1]);
    query.addBindValue((QDate::currentDate()).toString());
    result = query.exec();
    return result;
}

//查询信息
QVector<QString> DBAutoPayManip::dbSelect(QString selectInfo){
    QSqlQuery query;
    QVector<QString> info;
    query.exec(selectInfo);
    while(query.next()){
        info.push_back(query.value(1).toString());
        info.push_back(query.value(2).toString());
        info.push_back(query.value(3).toString());
    }
    return info;
}

//更新自动付款信息
bool DBAutoPayManip::dbUpdate(QString updateInfo){
    return false;
}

//删除信息，不可用
bool DBAutoPayManip::dbDelete(QString deleteInfo){
    return false;
}

//删除信息，逐项删除
bool DBAutoPayManip::dbDelete(QString number,QString type){
    bool result;
    QSqlQuery query;
    int accountKey = DBAccountManip::dbSelectAccountKey(number);
    query.prepare("DELETE FROM autoPay WHERE accountKey = ? AND type = ?");
    query.addBindValue(accountKey);
    query.addBindValue(type);
    result = query.exec();
    return result;
}

