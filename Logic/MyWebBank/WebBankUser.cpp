#include <QString>
#include <QSql>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QVector>
#include "WebBankUser.h"

WUser::WUser(SUserInfo userInfo){
    name = userInfo.name;
    password = userInfo.password;
    id = userInfo.id;
    createdDate = userInfo.createdDate;
    tel = userInfo.tel;
    email = userInfo.email;
    address = userInfo.address;
    zipCode = userInfo.zipCode;
    type = userInfo.type;
    account = userInfo.account;
    message = userInfo.message;
}

bool WUser::setPassword(QString newPassword);

SUserInfo *WUser::getUserInfo(){
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
    info->message = message;
    return info;
}

