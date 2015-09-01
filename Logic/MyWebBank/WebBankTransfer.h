#ifndef WEBBANKTRANSFER_H
#define WEBBANKTRANSFER_H

#include <QVector>
#include "WebBankCurrentUser.h"

class WTransfer{
private:
    QString myAccountNumber;
    QString transferedAccountNumber;
    float sum;
    float myAccountBalance;
public:
    bool transfer();
    WTransfer();
    WTransfer(const QString number,float& balance,const float sum,const QStirng otherAccount);
};

#endif // WEBBANKTRANSFER_H
