#ifndef WEBBANKCREDITCARD_H
#define WEBBANKCREDITCARD_H

#include "waccount.h"

#define PLATINUMCARDRATE 0.25
#define GOLDCARDRATE 0.5
#define SILVERCARDRATE 0.75
#define NORMALCREDITCARDRATE 1

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

class WPlatinumCard: public WCreditCard
{
public:
    WPlatinumCard() {}
    WPlatinumCard(QString number);

    void interestCaculation(const float poundage = PLATINUMCARDRATE);
};

class WGoldCard: public WCreditCard
{
public:
    WGoldCard() {}
    WGoldCard(QString number);

    void interestCaculation(const float poundage = GOLDCARDRATE);
};

class WSilverCard: public WCreditCard
{
public:
    WSilverCard() {}
    WSilverCard(QString number);

    void interestCaculation(const float poundage = SILVERCARDRATE);
};

class WNormalCreditCard: public WCreditCard
{
public:
    WNormalCreditCard() {}
    WNormalCreditCard(QString number);

    void interestCaculation(const float poundage = NORMALCREDITCARDRATE);
};
#endif // WEBBANKCREDITCARD_H
