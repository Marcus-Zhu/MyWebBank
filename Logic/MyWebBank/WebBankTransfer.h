#ifndef WEBBANKTRANSFER_H
#define WEBBANKTRANSFER_H

#include <QVector>
#include <QString>


class WTransfer
{
private:
    QString myAccountNumber;
    QString transferedAccountNumber;
    QString type;
    float sum;
    float &fixedDeposit;
    float &currentDeposit;
public:
    bool transferToOther();
    bool transferToFixed();
    \
    bool transferToCurrent();
    WTransfer(const QString number, float &fixedDeposit, float &currentDeposit,
              const QString type, const float sum, const QString otherAccount);
};

#endif // WEBBANKTRANSFER_H
