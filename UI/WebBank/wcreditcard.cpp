#include "wcreditcard.h"
#include "wDBmanip.h"
#include "wcurrentuser.h"
#include "wtransfer.h"
#include "wpayment.h"
#include <QVector>
#include <math.h>
#include <QDebug>

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

    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'")
                                      .arg(getAccountNumber())))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime, "yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(getStatus() == "frozen" ) {}
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

WPlatinumCard::WPlatinumCard(QString number)
{
    setAccountInfo(number);
    setCreditLimit(100000);
    DBAccountManip accountManip;
    accountManip.dbUpdate(number, getCreditLimit(), getDeposit());
}

void WPlatinumCard::interestCaculation(const float poundage)
{
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    DBAccountManip dbAccount;

    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'")
                                      .arg(getAccountNumber())))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime, "yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(getStatus() != "frozen" )
    {
        float deposit = getDeposit();
        if(WCurrentUser::userType == "normal")
        {
            deposit = deposit - deposit * days * NORMALFIXEDRATE * poundage;
        }
        else
            deposit = deposit + deposit * days * VIPFIXEDRATE * poundage;
    }

    dbAccount.dbUpdate(getAccountNumber(), getCreditLimit(), getDeposit());
}

WGoldCard::WGoldCard(QString number)
{
    setAccountInfo(number);
    setCreditLimit(50000);
    DBAccountManip accountManip;
    accountManip.dbUpdate(number, getCreditLimit(), getDeposit());
}

void WGoldCard::interestCaculation(const float poundage)
{
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    DBAccountManip dbAccount;

    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'")
                                      .arg(getAccountNumber())))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime, "yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(getStatus() != "frozen" )
    {
        float deposit = getDeposit();
        if(WCurrentUser::userType == "normal")
        {
            deposit = deposit - deposit * days * NORMALFIXEDRATE * poundage;
        }
        else
            deposit = deposit + deposit * days * VIPFIXEDRATE * poundage;
    }

    dbAccount.dbUpdate(getAccountNumber(), getCreditLimit(), getDeposit());
}

WSilverCard::WSilverCard(QString number)
{
    setAccountInfo(number);
    setCreditLimit(30000);
    DBAccountManip accountManip;
    accountManip.dbUpdate(number, getCreditLimit(), getDeposit());
}

void WSilverCard::interestCaculation(const float poundage)
{
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    DBAccountManip dbAccount;

    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'")
                                      .arg(getAccountNumber())))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime, "yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(getStatus() != "frozen" )
    {
        float deposit = getDeposit();
        if(WCurrentUser::userType == "normal")
        {
            deposit = deposit - deposit * days * NORMALFIXEDRATE * poundage;
        }
        else
            deposit = deposit + deposit * days * VIPFIXEDRATE * poundage;
    }

    dbAccount.dbUpdate(getAccountNumber(), getCreditLimit(), getDeposit());
}

WNormalCreditCard::WNormalCreditCard(QString number)
{
    setAccountInfo(number);
    setCreditLimit(10000);
    DBAccountManip accountManip;
    accountManip.dbUpdate(number, getCreditLimit(), getDeposit());
}

void WNormalCreditCard::interestCaculation(const float poundage)
{
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    DBAccountManip dbAccount;

    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'")
                                      .arg(getAccountNumber())))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime, "yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(getStatus() != "frozen" )
    {
        float deposit = getDeposit();
        if(WCurrentUser::userType == "normal")
        {
            deposit = deposit - deposit * days * NORMALFIXEDRATE * poundage;
        }
        else
            deposit = deposit + deposit * days * VIPFIXEDRATE * poundage;
    }

    dbAccount.dbUpdate(getAccountNumber(), getCreditLimit(), getDeposit());
}

