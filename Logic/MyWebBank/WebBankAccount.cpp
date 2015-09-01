#include "WebBankAccount.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"

#define NORMALINTERESTRATE 0.0000096
#define VIPINTERESTRATE 0.0000120

void WAccount::interestCalculation(){
    QDate currentDate = QDate::currentDate();
    QString tableTime;
    DBLogRecordManip dbLogRecord;
    tableTime = (dbLogRecord.dbSelect(QString("SELECT MAX(time) WHERE number = '%1'").arg(accountNumber)))[0];
    QDateTime TableTime  = QDateTime::fromString(tableTime,"yyyy-MM-dd hh:mm:ss");
    int days = -currentDate.daysTo(TableTime.date());
    if(status == "frozen" ){}
    else{
        if(type == "normal"){
            accountBalance = accountBalance +accountBalance*days*NORMALINTERESTRATE;
        }
        else
            accountBalance = accountBalance +accountBalance*days*VIPINTERESTRATE;
    }

    if(!dbAccount.dbUpdate(accountNumber,accountBalance))
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
    userName = WCurrentUser::getUserName();
    accountNumber = "";
    accountBalance = 0.0f;
    status = "";
    type = "";
}

WAccount::WAccount(QString number){
    setAccountInfo(number);
}

void WAccount::setAccountInfo(QString number){
    DBAccountManip dbAccout;
    QVector<QString> accountInfo = dbAccout.dbSelect(number);
    userName = WCurrentUser::getUserName();
    accountNumber = number;
    accountBalance = accountInfo[2].toFloat();
    status = accountInfo[3];
    type = accountInfo[0];
}

