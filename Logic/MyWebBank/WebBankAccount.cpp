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

void WAccount::interestCalculation(){
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    DBAccountManip dbAccount;
    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'").arg(accountNumber)))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime,"yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(status == "frozen" ){}
    else{
        if(type == "normal"){
            fixedDeposit = fixedDeposit + fixedDeposit*days*NORMALFIXEDRATE;
            currentDeposit = currentDeposit + currentDeposit*days*NORMALINTERESTRATE;

        }
        else
            fixedDeposit = fixedDeposit + fixedDeposit*days*VIPFIXEDRATE;
            currentDeposit = currentDeposit + currentDeposit*days*VIPINTERESTRATE;
    }

    if(!dbAccount.dbUpdate(accountNumber,fixedDeposit,currentDeposit))
        qDebug()<<"fail to update";
}

void WAccount::freezeAccount(){
    DBAccountManip dbAccount;
    dbAccount.dbUpdate(accountNumber);
}

void WAccount::releaseAccount(){
    DBAccountManip dbAccount;
    dbAccount.dbUpdate(accountNumber);
}

WAccount::WAccount(){
    userName = WCurrentUser::userName;
    accountNumber = "";
    fixedDeposit = 0.0f;
    currentDeposit = 0.0f;
    status = "";
    type = "";
}

WAccount::WAccount(QString number){
    setAccountInfo(number);
}

void WAccount::setAccountInfo(QString number){
    DBAccountManip dbAccout;
    QVector<QString> accountInfo = dbAccout.dbSelect(number);
    userName = WCurrentUser::userName;
    accountNumber = number;
    fixedDeposit = accountInfo[2].toFloat();
    currentDeposit = accountInfo[3].toFloat();
    status = accountInfo[4];
    type = accountInfo[0];
}

const QString WAccount::getUserName(){
    return userName;
}

const QString WAccount::getAccountNumber(){
    return accountNumber;
}

float& WAccount::getFixedDeposit(){
    return fixedDeposit;
}

float& WAccount::getCurrentDeposit(){
    return currentDeposit;
}

const QString WAccount::getStatus(){
    return status;
}

const QString WAccount::getType(){
    return type;
}

bool WAccount::transaction(const transferType Type, const QString otherNumber,const float sum){
    WTransfer tran(accountNumber,fixedDeposit,currentDeposit,type,sum,otherNumber);
    DBAccountManip dbAcount;
    bool result;
    if(Type == TransferToOther){
        result = tran.transferToOther();
        dbAcount.dbUpdate(otherNumber,sum);
        DBMessageManip dbMessage;
        QVector<QString> insertInfo;
        int userKey = DBAccountManip::dbSelectUserKey(otherNumber);
        insertInfo[0].setNum(userKey);
        insertInfo[1] = "tranfered into";
        dbMessage.dbInsert(insertInfo);
    }
    else if(Type == TransferToFixed){
        result = tran.transferToFixed();
    }
    else
        result = tran.transferToCurrent();

    dbAcount.dbUpdate(accountNumber,fixedDeposit,currentDeposit);
    return result;
}

bool WAccount::payment(const QString paymentType,float sum){
    WPayment pay(accountNumber,sum,paymentType);
    bool result = pay.pay();
    return result;
}

QVector<QString>& WAccount::recentRecords(){
    QVector<QString> transactionRecord1;
    QVector<QString> transactionRecord2;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;
    DBPaymetnRecordManip paymentManip;
    int key = DBAccountManip::dbSelectAccountKey(accountNumber);
    QString selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1").arg(key);
    QString selectInfo2 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey2 = %1").arg(key);
    transactionRecord1 = transferManip.dbSelect(selectInfo1);
    transactionRecord2 = transferManip.dbSelect(selectInfo2);
    QString selectInfo3 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1").arg(key);
    paymentRecord = paymentManip.dbSelect(selectInfo3);
    int rows = (transactionRecord1.size()+transactionRecord2.size()
                +paymentRecord.size())/3;
    QDateTime times[rows];
    int j = 0;
    for(int i = 0;i<transactionRecord1.size();i++,j++)
        times[j].fromString(transactionRecord1[1 + 3*i],"yyyy-MM-dd hh:mm:ss");
    for(int i = 0;i<transactionRecord2.size();i++,j++)
        times[j].fromString(transactionRecord2[1 + 3*i],"yyyy-MM-dd hh:mm:ss");
    for(int i = 0;i<transactionRecord3.size();i++,j++)
        times[j].fromString(transactionRecord3[1 + 3*i],"yyyy-MM-dd hh:mm:ss");
    QVector<QString> recentRecord;
    for(int i = 0;i<transactionRecord1.size();i++)
        recentRecord.push_back(transactionRecord1[i]);
    for(int i = 0;i<transactionRecord2.size();i++)
        recentRecord.push_back(transactionRecord2[i]);
    for(int i = 0;i<paymentRecord.size();i++)
        recentRecord.push_back(paymentRecord[i]);
    for(int i = 0;i<rows -1;i++)
        for(int j = 0;j<rows -1;j++){
            if(times[j]<times[j + 1]){
                QDateTime temp;
                temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;
                QString temps[3];
                temps[0] = recentRecord[3*j];
                temps[1] = recentRecord[3*j + 1];
                temps[2] = recentRecord[3*j + 2];
                recentRecord[3*j] = recentRecord[3*(j+1)];
                recentRecord[3*j + 1] = recentRecord[3*(j+1) + 1];
                recentRecord[3*j + 2] = recentRecord[3*(j+1) + 2];
                recentRecord[3*(j+1)] = temp[0];
                recentRecord[3*(j+1) + 1] = temp[1];
                recentRecord[3*(j+1) + 2] = temp[2];
            }
        }
    return recentRecord;
}
