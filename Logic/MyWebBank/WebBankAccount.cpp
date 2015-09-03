#include "WebBankAccount.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"
#include "WebBankTransfer.h"
#include <QString>

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
