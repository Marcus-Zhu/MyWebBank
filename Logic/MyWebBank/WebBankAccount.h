#ifndef WEBBANKACCOUNT_H
#define WEBBANKACCOUNT_H

#include <QVector>
#include <QString>

enum transferType{TransferToOther = 1,TransferToFixed = 2,
                 TransferToCurrent = 3};

class WAccount{
private:
    QString userName;
    QString accountNumber;
    QString type;
    QString status;

public:
    QString getUserName();
    QString getAccountNumber();
    QString getType();
    QString getStatus();
    void setUserName(QString name);
    void setAccountNumber(QString number);
    void setType(QString type);
    void setStatus();
    void setStatus(QString Status);
    void changeStatus();
    void freezeAccount();
    void releaseAccount();
    QVector<QString> recentRecords();
};


class WNormalAccount:public WAccount{
private:
    float fixedDeposit;
    float currentDeposit;
public:
    void setAccountInfo(QString number);
    WNormalAccount();
    WNormalAccount(QString number);
    void interestCalculation();           //计算存款
    float& getFixedDeposit();
    float& getCurrentDeposit();
    bool transaction(const transferType Type, const QString otherNumber, const float sum);
    bool payment(const QString paymentType, float sum);
};


#endif // WEBBANKACCOUNT_H
