#ifndef WEBBANKACCOUNT_H
#define WEBBANKACCOUNT_H

#include <QVector>
#include "WebBankDataBaseManip.h"

class WAccount{
private:
    QString userName;
    QString accountNumber;
    float accountBalance;
    QString status;
    QString type;
public:
    void setAccountInfo(QString number);
    WAccount();
    WAccount(QString number);
    void interestCalculation();           //计算存款
    void freezeAccount();                 //冻结账户
    void releaseAccount();                //解冻账户

    //转账
    bool transaction(const QString number = accountNumber,float& balance = accountBalance);
    bool payment();                       //付款
    QVector<QString>& transactionRecord();//转账记录
    QVector<QString>& paymentRecord();    //付款记录
};


#endif // WEBBANKACCOUNT_H
