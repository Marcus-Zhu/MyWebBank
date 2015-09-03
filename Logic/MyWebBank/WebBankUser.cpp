#include <QCoreApplication>
#include <QVector>
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
    this->account = userInfo.account;
    this->messageAmount = userInfo.messageAmount;
    WCurrentUser::userName = userInfo.name;
    WCurrentUser::password = userInfo.password;
    WCurrentUser::userType = userInfo.type;
}

bool WUser::setPassword(QString oldPassword,QString newPassword){
    DBUserManip dbUser;
    if(!dbUser.dbSelect(name,oldPassword))
        return false;
    else
        return dbUser.dbUpdate(newPassword);
}

bool WUser::addAccount(QString number){

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

int WUser::checkIn(QString name, QString password){
    DBUserManip dbUser;
    if(!dbUser.dbSelect(name))
        return 1;//用户名不存在
    else if(!dbUser.dbSelect(name,password))
        return 2;//密码不正确
    else
        return 3;//成功登录
}
