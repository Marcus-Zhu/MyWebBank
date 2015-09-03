#ifndef WEBBANKACCOUNT_H
#define WEBBANKACCOUNT_H

#include <QVector>
#include "WebBankDataBaseManip.h"

enum transferType{TransferToOther = 1,TransferToFixed = 2,
                 TransferToCurrent = 3};

class WAccount{
private:
    QString userName;
    QString accountNumber;
    float fixedDeposit;
    float currentDeposit;
    QString status;
    QString type;
public:
    void setAccountInfo(QString number);
    WAccount();
    WAccount(QString number);
    void interestCalculation();           //计算存款
    void freezeAccount();                 //冻结账户
    void releaseAccount();                //解冻账户
    const QString getUserName();
    const QString getAccountNumber();
    float& getFixedDeposit();
    float& getCurrentDeposit();
    const QString getStatus();
    const QString getType();

    //转账
    bool transaction(const transferType Type, const QString otherNumber, const float sum);
    //付款
    bool payment();
    QVector<QString>& transactionRecord();//转账记录
    QVector<QString>& paymentRecord();    //付款记录
};


#endif // WEBBANKACCOUNT_H
