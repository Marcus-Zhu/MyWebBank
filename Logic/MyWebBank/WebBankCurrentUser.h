#ifndef WEBBANKCURRENTUSER_H
#define WEBBANKCURRENTUSER_H

#include <QVector>
#include "WebBankUser.h"

class WCurrentUser{
private:
    SUserInfo userInfo;
public:
    void copy();
    static QString getUserName();
    static QString getPassword();
    static QString getType();
    WCurrentUser();
}


#endif // WEBBANKCURRENTUSER_H
