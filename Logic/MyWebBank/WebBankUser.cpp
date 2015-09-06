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

bool WUser::addAccount(QString number, QString type){

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




//理想与事业
//多做学生工作对我们的人生发展和事业都有好处
//现在发展后条件比以前好了很多，爱国奉献
//国家发展，民族自豪感，从事到国家的大事业中去
//这样才能获得成就感
//明确我们的目标，坚守道德的底线














