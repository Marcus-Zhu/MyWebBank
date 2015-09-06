#ifndef WEBBANKPAYMENT_H
#define WEBBANKPAYMENT_H

#include <QVector>
#include <QString>

class WPayment{
public:
    WPayment();
    WPayment(QString accountNumber,float sum,QString paymentType);
    void setAutoPayment(bool ifChoose[3]);
    bool isAutoPaymentEmpty();
    bool pay();
    bool autoPayment();
private:
    QString number;
    QString type;
    float currentDeposit;
    float sum;
    bool haveAutoPayment[3];
};

#endif // WEBBANKPAYMENT_H
