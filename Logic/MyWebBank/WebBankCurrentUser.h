#ifndef WEBBANKCURRENTUSER_H
#define WEBBANKCURRENTUSER_H

#include <QVector>
#include "WebBankUser.h"

class WCurrentUser{
private:
    SUserInfo userInfo;
public:
    void copy();
    QString getUserName();
    QString getPassword();
    QString getType();
    WCurrentUser();
}


#endif // WEBBANKCURRENTUSER_H
