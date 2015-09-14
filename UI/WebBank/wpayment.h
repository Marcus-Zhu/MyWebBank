#ifndef WEBBANKPAYMENT_H
#define WEBBANKPAYMENT_H

#include <QVector>
#include <QString>
#include <QDate>

class WPayment
{
public:
    WPayment();
    WPayment(QString accountNumber, float sum = 0.0, QString paymentType = "");
    void setAutoPayment(bool ifChoose[3]);
    bool isAutoPaymentEmpty();
    bool pay();
    bool autoPayment();
    bool deleteAutoPayment(QString paymentType[3]);
private:
    QString number;
    QString type;
    float currentDeposit;
    float fixedDeposit;
    float sum;
    bool haveAutoPayment[3];
    QDate autoPayDate[3];
    QString autoPayType[3];
};

#endif // WEBBANKPAYMENT_H
