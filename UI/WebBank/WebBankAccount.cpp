#include "WebBankAccount.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"
#include "WebBankTransfer.h"
#include "WebBankPayment.h"
#include <QString>
#include <QDateTime>
#include <QDebug>

#define NORMALINTERESTRATE 0.0000096
#define VIPINTERESTRATE 0.0000120
#define NORMALFIXEDRATE 0.0000150
#define VIPFIXEDRATE 0.0000180

QString WAccount::getUserName(){
    return userName;
}

QString WAccount::getAccountNumber(){
    return accountNumber;
}

QString WAccount::getStatus(){
    return status;
}

QString WAccount::getType(){
    return type;
}

void WAccount::setUserName(QString name){
    userName = name;
}

void WAccount::setAccountNumber(QString number){
    accountNumber = number;
}

void WAccount::setType(QString type){
    this->type = type;
}

void WAccount::setStatus(){
    status = "normal";
}

void WAccount::setStatus(QString Status){
    status = Status;
}

void WAccount::changeStatus(){
    if(status == "normal")
        status = "frozen";
    else
        status = "normal";
}

void WAccount::freezeAccount(){
    if(getStatus() == "freeze")
        return;
    DBAccountManip dbAccount;
    dbAccount.dbUpdate(accountNumber);
}

void WAccount::releaseAccount(){
    if(getStatus() == "normal")
        return;
    DBAccountManip dbAccount;
    dbAccount.dbUpdate(accountNumber);
}

QVector<QString> WAccount::recentRecords(){
    QVector<QString> transactionRecord1;
    QVector<QString> transactionRecord2;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;

    DBPaymentRecordManip paymentManip;
    int key = DBAccountManip::dbSelectAccountKey(getAccountNumber());
    QString selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1 ORDER BY key DESC").arg(key);
    QString selectInfo2 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey2 = %1 AND accountKey1 != %1 ORDER BY key DESC").arg(key);
    transactionRecord1 = transferManip.dbSelect(selectInfo1,3);
    transactionRecord2 = transferManip.dbSelect(selectInfo2,3);
    QString selectInfo3 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1 ORDER BY key DESC").arg(key);
    paymentRecord = paymentManip.dbSelect(selectInfo3,3);

    int size1 = (transactionRecord1.size()/3)<10?(transactionRecord1.size()/3):10;
    int size2 = (transactionRecord2.size()/3)<10?(transactionRecord2.size()/7):10;
    for(int i = 0;i<size2;i++){
        transactionRecord2[3*i + 2] = "be transfered into";
    }
    int size3 = paymentRecord.size()/3;

    QVector<QString> recentRecord;
    for(int i = 0;i<size1*3;i++)
        recentRecord.push_back(transactionRecord1[i]);
    for(int i = 0;i<size2*3;i++)
        recentRecord.push_back(transactionRecord2[i]);
    for(int i = 0;i<size3*3;i++)
        recentRecord.push_back(paymentRecord[i]);

//    int rows = recentRecord.size()/3;
//    QDateTime times[rows];
//    for(int i = 0;i<rows;i++)
//        times[i] = QDateTime::fromString(recentRecord[1 + 3*i],"yyyy-MM-dd hh:mm:ss");

//    for(int i = 0;i<rows -1;i++)
//        for(int j = 0;j<rows -1;j++){
//            if(times[j]<times[j + 1]){
//                QDateTime temp;
//                temp = times[j];
//                times[j] = times[j + 1];
//                times[j + 1] = temp;
//                QString temps[3];
//                temps[0] = recentRecord[3*j];
//                temps[1] = recentRecord[3*j + 1];
//                temps[2] = recentRecord[3*j + 2];
//                recentRecord[3*j] = recentRecord[3*(j+1)];
//                recentRecord[3*j + 1] = recentRecord[3*(j+1) + 1];
//                recentRecord[3*j + 2] = recentRecord[3*(j+1) + 2];
//                recentRecord[3*(j+1)] = temps[0];
//                recentRecord[3*(j+1) + 1] = temps[1];
//                recentRecord[3*(j+1) + 2] = temps[2];
//            }
//        }
    return recentRecord;
}

WNormalAccount::WNormalAccount(){
    setUserName(WCurrentUser::userName);
    setAccountNumber("");
    fixedDeposit = 0.0f;
    currentDeposit = 0.0f;
    setType("");
    setStatus();
}

WNormalAccount::WNormalAccount(QString number){
    setAccountInfo(number);
}

void WNormalAccount::interestCalculation(){
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    DBAccountManip dbAccount;

    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'")
                                      .arg(getAccountNumber())))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime,"yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(getStatus() == "frozen" ){}
    else{
        if(getType() == "normal"){
            fixedDeposit = fixedDeposit + fixedDeposit*days*NORMALFIXEDRATE;
            currentDeposit = currentDeposit + currentDeposit*days*NORMALINTERESTRATE;

        }
        else
            fixedDeposit = fixedDeposit + fixedDeposit*days*VIPFIXEDRATE;
            currentDeposit = currentDeposit + currentDeposit*days*VIPINTERESTRATE;
    }

    if(!dbAccount.dbUpdate(getAccountNumber(),fixedDeposit,currentDeposit))
        qDebug()<<"fail to update";
}

void WNormalAccount::setAccountInfo(QString number){
    DBAccountManip dbAccout;
    QVector<QString> accountInfo = dbAccout.dbSelect(number);
    setUserName(WCurrentUser::userName);
    setAccountNumber(number);
    fixedDeposit = accountInfo[2].toFloat();
    currentDeposit = accountInfo[3].toFloat();
    setStatus(accountInfo[4]);
    setType(accountInfo[0]);
}



float& WNormalAccount::getFixedDeposit(){
    return fixedDeposit;
}

float& WNormalAccount::getCurrentDeposit(){
    return currentDeposit;
}

bool WNormalAccount::transaction(const transferType Type, const QString otherNumber,const float sum){
    WTransfer tran(getAccountNumber(),fixedDeposit,currentDeposit,getType(),sum,otherNumber);
    DBAccountManip dbAcount;
    bool result;
    if(Type == TransferToOther){
        result = tran.transferToOther();
        dbAcount.dbUpdate(otherNumber,sum);
        DBMessageManip dbMessage;
        QVector<QString> insertInfo(2);
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
    dbAcount.dbUpdate(getAccountNumber(),fixedDeposit,currentDeposit);
    return result;
}

bool WNormalAccount::payment(const QString paymentType,float sum){
    WPayment pay(getAccountNumber(),sum,paymentType);
    bool result = pay.pay();
    return result;
}

