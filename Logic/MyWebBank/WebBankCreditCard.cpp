#include "WebBankCreditCard.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"
#include "WebBankTransfer.h"
#include "WebBankPayment.h"
#include <QVector>
#include <math.h>

#define NORMALINTERESTRATE 0.0000096
#define VIPINTERESTRATE 0.0000120
#define NORMALFIXEDRATE 0.0000150
#define VIPFIXEDRATE 0.0000180

void WCreditCard::setAccountInfo(QString number)
{
    QVector<QString> info;
    DBAccountManip dbAccount;
    info = dbAccount.dbSelect(number);
    setType(info[0]);
    setAccountNumber(number);
    deposit = info[2].toFloat();
    creditLimit = info[3].toFloat();
    setStatus(info[4]);
    setUserName(WCurrentUser::userName);
}

WCreditCard::WCreditCard(QString number)
{
    setAccountInfo(number);
}

void WCreditCard::interestCaculation()
{
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    DBAccountManip dbAccount;

    //计算距离上次结算的天数（实际使用上次登出天数代替）
    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'")
                                      .arg(getAccountNumber())))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime, "yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(getStatus() == "frozen" ) {} //如果frozen了就不结算
    else
    {
        if(WCurrentUser::userType == "normal")
        {
            deposit = deposit - deposit * days * NORMALFIXEDRATE;
        }
        else
            deposit = deposit + deposit * days * VIPFIXEDRATE;
    }

    if(!dbAccount.dbUpdate(getAccountNumber(), creditLimit, deposit))
        qDebug() << "fail to update";
}

float &WCreditCard::getDeposit()
{
    return deposit;
}

float WCreditCard::getCreditLimit()
{
    return creditLimit;
}

void WCreditCard::setCreditLimit(float limit)
{
    creditLimit = limit;
}

bool WCreditCard::transaction(const QString otherNumber, const float sum)
{
    WTransfer tran(getAccountNumber(), creditLimit, deposit, getType(), sum, otherNumber);
    DBAccountManip dbAcount;
    bool result;

    result = tran.transferToOther();
    if(!result)
        return result;
    dbAcount.dbUpdate(otherNumber, sum);
    DBMessageManip dbMessage;
    QVector<QString> insertInfo;
    int userKey = DBAccountManip::dbSelectUserKey(otherNumber);
    insertInfo[0].setNum(userKey);
    insertInfo[1] = "tranfered into";
    dbMessage.dbInsert(insertInfo);

    dbAcount.dbUpdate(getAccountNumber(), creditLimit, deposit);
    return result;
}



bool WCreditCard::payment(const QString paymentType, float sum)
{
    WPayment pay(getAccountNumber(), sum, paymentType);
    bool result = pay.pay();
    return result;
}
