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
    const QString getStatus();            //获取用户账户当前状态（normal，frozen）
    const QString getType();              //获取用户账户类型（normal，VIP）

    bool transaction(const transferType Type, const QString otherNumber, const float sum);
    bool payment(const QString paymentType, float sum);
    QVector<QString>& recentRecords();
};


#endif // WEBBANKACCOUNT_H
