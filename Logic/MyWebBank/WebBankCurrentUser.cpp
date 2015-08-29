#include <QVector>
#include "WebBankCurrentUser.h"

WCurrentUser::WCurrentUser(){
    userInfo = *(WUser::getUserInfo());
}

void WCurrentUser::copy(){
    userInfo = *(WUser::getUserInfo());
}

QString WCurrentUser::getUserName(){
    return userInfo.name;
}

QString WCurrentUser::getPassword(){
    return userInfo.password;
}

QString WCurrentUser::getType(){
    return userInfo.type;
}
