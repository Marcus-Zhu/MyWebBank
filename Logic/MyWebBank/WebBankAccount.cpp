#include "WebBankAccount.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"
#include "WebBankTransfer.h"
#include "WebBankPayment.h"
#include <QString>
#include <QDateTime>

#define NORMALINTERESTRATE 0.0000096
#define VIPINTERESTRATE 0.0000120
#define NORMALFIXEDRATE 0.0000150
#define VIPFIXEDRATE 0.0000180

//WAccount类
QString WAccount::getUserName()
{
    return userName;
}

QString WAccount::getAccountNumber()
{
    return accountNumber;
}

QString WAccount::getStatus()
{
    return status;
}

QString WAccount::getType()
{
    return type;
}

void WAccount::setUserName(QString name)
{
    userName = name;
}

void WAccount::setAccountNumber(QString number)
{
    accountNumber = number;
}

void WAccount::setType(QString type)
{
    this->type = type;
}

void WAccount::setStatus()
{
    status = "normal";
}

void WAccount::setStatus(QString Status)
{
    status = Status;
}

void WAccount::changeStatus()
{
    if(status == "normal")
        status = "frozen";
    else
        status = "normal";
}

void WAccount::freezeAccount()
{
    if(getStatus() == "freeze")
        return;
    DBAccountManip dbAccount;
    dbAccount.dbUpdate(accountNumber);
}

void WAccount::releaseAccount()
{
    if(getStatus() == "normal")
        return;
    DBAccountManip dbAccount;
    dbAccount.dbUpdate(accountNumber);
}

//最近十条记录，返回的columes依次是sum，time，type
QVector<QString> WAccount::recentRecords()
{
    QVector<QString> transactionRecord1;
    QVector<QString> transactionRecord2;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;

    DBPaymentRecordManip paymentManip;
    int key = DBAccountManip::dbSelectAccountKey(getAccountNumber());

    QString selectInfo1 = QString("SELECT * FROM transactionRecord WHERE accountKey1 = %1").arg(key);
    QString selectInfo2 = QString("SELECT * FROM transactionRecord WHERE accountKey2 = %1 AND accoutKey1 != %1").arg(key);

    transactionRecord1 = transferManip.dbSelect(selectInfo1);
    transactionRecord2 = transferManip.dbSelect(selectInfo2);

    QString selectInfo3 = QString("SELECT * FROM paymentRecord WHERE accountKey = %1").arg(key);

    paymentRecord = paymentManip.dbSelect(selectInfo3);

    //删除无用信息
    int size1 = transactionRecord1.size() / 7;
    for(int i = 0; i < size1; i++)
    {
        transactionRecord1.remove(7 * (size1 - i - 1) + 5);
        transactionRecord1.remove(7 * (size1 - i - 1) + 4);
        transactionRecord1.remove(7 * (size1 - i - 1) + 1);
        transactionRecord1.remove(7 * (size1 - i - 1) );
    }
    int size2 = transactionRecord2.size() / 7;
    for(int i = 0; i < size2; i++)
    {
        transactionRecord2.remove(7 * (size1 - i - 1) + 5);
        transactionRecord2.remove(7 * (size1 - i - 1) + 4);
        transactionRecord2.remove(7 * (size1 - i - 1) + 1);
        transactionRecord2.remove(7 * (size1 - i - 1) );
    }
    int size3 = paymentRecord.size() / 5;
    for(int i = 0; i < size3; i++)
    {
        paymentRecord.remove(5 * (size3 - 1 - i) + 3);
        paymentRecord.remove(5 * (size3 - 1 - i));
    }
    //构造传回去的QVector
    QVector<QString> recentRecord;
    for(int i = 0; i < transactionRecord1.size(); i++)
        recentRecord.push_back(transactionRecord1[i]);
    for(int i = 0; i < transactionRecord2.size(); i++)
        recentRecord.push_back(transactionRecord2[i]);
    for(int i = 0; i < paymentRecord.size(); i++)
        recentRecord.push_back(paymentRecord[i]);
    if(recentRecord.size() > 30)
    {
        int size = recentRecord.size();
        for(int i = 1; i < size - 31; i++)
            recentRecord.remove(size - i);
    }
    //转时间为QDateTime对象
    int rows = recentRecord.size() / 3;
    QDateTime times[rows];
    for(int i = 0; i < rows; i++)
        times[i].fromString(recentRecord[1 + 3 * i], "yyyy-MM-dd hh:mm:ss");
    //排序
    for(int i = 0; i < rows - 1; i++)
        for(int j = 0; j < rows - 1; j++)
        {
            if(times[j] < times[j + 1])
            {
                QDateTime temp;
                temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;
                QString temps[3];
                temps[0] = recentRecord[3 * j];
                temps[1] = recentRecord[3 * j + 1];
                temps[2] = recentRecord[3 * j + 2];
                recentRecord[3 * j] = recentRecord[3 * (j + 1)];
                recentRecord[3 * j + 1] = recentRecord[3 * (j + 1) + 1];
                recentRecord[3 * j + 2] = recentRecord[3 * (j + 1) + 2];
                recentRecord[3 * (j + 1)] = temps[0];
                recentRecord[3 * (j + 1) + 1] = temps[1];
                recentRecord[3 * (j + 1) + 2] = temps[2];
            }
        }
    return recentRecord;
}

//WNormalAccount 类
WNormalAccount::WNormalAccount()
{
    setUserName(WCurrentUser::userName);
    setAccountNumber("");
    fixedDeposit = 0.0f;
    currentDeposit = 0.0f;
    setType("");
    setStatus();
}

WNormalAccount::WNormalAccount(QString number)
{
    setAccountInfo(number);
}
//计算存款的获得利息的函数
void WNormalAccount::interestCalculation()
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
        if(getType() == "normal")
        {
            fixedDeposit = fixedDeposit + fixedDeposit * days * NORMALFIXEDRATE;
            currentDeposit = currentDeposit + currentDeposit * days * NORMALINTERESTRATE;

        }
        else
            fixedDeposit = fixedDeposit + fixedDeposit * days * VIPFIXEDRATE;
        currentDeposit = currentDeposit + currentDeposit * days * VIPINTERESTRATE;
    }

    if(!dbAccount.dbUpdate(getAccountNumber(), fixedDeposit, currentDeposit))
        qDebug() << "fail to update";
}

void WNormalAccount::setAccountInfo(QString number)
{
    DBAccountManip dbAccout;
    QVector<QString> accountInfo = dbAccout.dbSelect(number);
    setUserName(WCurrentUser::userName);
    setAccountNumber(number);
    fixedDeposit = accountInfo[2].toFloat();
    currentDeposit = accountInfo[3].toFloat();
    setStatus(accountInfo[4]);
    setType(accountInfo[0]);
}



float &WNormalAccount::getFixedDeposit()
{
    return fixedDeposit;
}

float &WNormalAccount::getCurrentDeposit()
{
    return currentDeposit;
}



//转账，返回是否操作成功
bool WNormalAccount::transaction(const transferType Type, const QString otherNumber, const float sum)
{
    WTransfer tran(getAccountNumber(), fixedDeposit, currentDeposit, getType(), sum, otherNumber);
    DBAccountManip dbAcount;
    bool result;
    if(Type == TransferToOther)
    {
        result = tran.transferToOther();
        dbAcount.dbUpdate(otherNumber, sum);
        DBMessageManip dbMessage;
        QVector<QString> insertInfo(2);
        int userKey = DBAccountManip::dbSelectUserKey(otherNumber);
        insertInfo[0].setNum(userKey);
        insertInfo[1] = "tranfered into";
        dbMessage.dbInsert(insertInfo);
    }
    else if(Type == TransferToFixed)
    {
        result = tran.transferToFixed();
    }
    else
        result = tran.transferToCurrent();
    dbAcount.dbUpdate(getAccountNumber(), fixedDeposit, currentDeposit);
    return result;
}

//付款，返回是否操作成功
bool WNormalAccount::payment(const QString paymentType, float sum)
{
    WPayment pay(getAccountNumber(), sum, paymentType);
    bool result = pay.pay();
    return result;
}

