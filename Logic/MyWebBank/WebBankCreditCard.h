#ifndef WEBBANKCREDITCARD_H
#define WEBBANKCREDITCARD_H

#include "WebBankAccount.h"

class WCreditCard: public WAccount
{
private:
    float deposit;
    float creditLimit;
public:
    void setAccountInfo(QString number);
    WCreditCard() {};
    WCreditCard(QString number);

    void interestCaculation();
    float &getDeposit();
    float getCreditLimit();
    void setCreditLimit(float limit);

    bool transaction(const QString otherNumber, const float sum);
    bool payment(const QString paymentType, float sum);
};

#endif // WEBBANKCREDITCARD_H
