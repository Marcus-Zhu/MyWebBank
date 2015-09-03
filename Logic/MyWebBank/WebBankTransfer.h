#ifndef WEBBANKTRANSFER_H
#define WEBBANKTRANSFER_H

#include <QVector>
#include "WebBankCurrentUser.h"


class WTransfer{
private:
    QString myAccountNumber;
    QString transferedAccountNumber;
    QString type;
    float sum;
    float fixedDeposit;
    float currentDeposit;
public:
    bool transferToOther();
    bool transferToFixed();\
    bool transferToCurrent();
    WTransfer();
    WTransfer(const QString number,float& fixedDeposit, float& currentDeposit,
              const QString type,const float sum,const QString otherAccount);
};

#endif // WEBBANKTRANSFER_H
