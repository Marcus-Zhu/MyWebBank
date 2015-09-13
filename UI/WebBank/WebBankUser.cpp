#include <QCoreApplication>
#include <QVector>
#include <Qsql>
#include <QSqlQuery>
#include <QVariant>

#include "WebBankSystemMessage.h"
#include "WebBankUser.h"
#include "WebBankDataBaseManip.h"

WUser::WUser(SUserInfo userInfo){
    this->name = userInfo.name;
    this->password = userInfo.password;
    this->id = userInfo.id;
    this->createdDate = userInfo.createdDate;
    this->tel = userInfo.tel;
    this->email = userInfo.email;
    this->address = userInfo.address;
    this->zipCode = userInfo.zipCode;
    this->type = userInfo.type;
    for(int i = 0;i<userInfo.account.size();i++)
        this->account.push_back(userInfo.account[i]);
    this->messageAmount = userInfo.messageAmount;
    WCurrentUser::userName = userInfo.name;
    WCurrentUser::password = userInfo.password;
    WCurrentUser::userType = userInfo.type;
}

WUser::WUser(QString userName){
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = ?");
    query.addBindValue(userName);
    query.next();
    name = query.value(1).toString();
    password = query.value(2).toString();
    id = query.value(3).toString();
    createdDate = query.value(4).toString();
    tel = query.value(5).toString();
    email = query.value(6).toString();
    address = query.value(7).toString();
    zipCode = query.value(8).toString();
    type = query.value(9).toString();
    WCurrentUser::userName = name;
    query.prepare("SELECT number FROM account WHERE userKey = ?");
    query.addBindValue(DBUserManip::dbSelectUserKey());
    int i = 0;
    while(query.next()&&i<3){
        account.push_back(query.value(0).toString());
        i++;
    }
    WMessage message;
    messageAmount = message.getMessageNumber();
}

bool WUser::setPassword(QString oldPassword,QString newPassword){
    DBUserManip dbUser;
    if(!dbUser.dbSelect(name,oldPassword))
        return false;
    else
        return dbUser.dbUpdate(newPassword);
}

SUserInfo WUser::getUserInfo(){
    SUserInfo* info = new SUserInfo;
    info->name = name;
    info->password = password;
    info->id = id;
    info->createdDate = createdDate;
    info->tel = tel;
    info->email = email;
    info->address = address;
    info->zipCode = zipCode;
    info->account = account;
    info->messageAmount = messageAmount;
    return *info;
}

int WUser::checkIn(QString Name, QString password){
    DBUserManip dbUser;
    if(!dbUser.dbSelect(Name))
        return 1;
    else if(!dbUser.dbSelect(Name,password))
        return 2;
    else
        return 3;
}

bool WUser::addAccount(QString number,QString type){
    DBAccountManip accountManip;
    QVector<QString> insertInfo;
    insertInfo.push_back(type);
    insertInfo.push_back(number);
    insertInfo.push_back("0");
    insertInfo.push_back("100000");
    insertInfo.push_back("normal");
    bool result = accountManip.dbInsert(insertInfo);
    if(result)
        account.push_back(number);
    return result;
}
