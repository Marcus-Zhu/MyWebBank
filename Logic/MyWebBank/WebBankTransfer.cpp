#include "WebBankTransfer.h"
#include "WebBankDataBaseManip.h"
#include <QVector>

#define NORMALPOUNDAGE 10
#define VIPPOUNDAGE 5

//默认构造函数
WTransfer::WTransfer(){
    myAccountNumber = "";
    transferedAccountNumber = "";
    type = "";
    sum = 0.0f;
    fixedDeposit = 0.0f;
    currentDeposit = 0.0f;
}

//构造函数
WTransfer::WTransfer(const QString number, float &fixDeposit,float &currentDeposit,
                     const QString type, const float sum, const QString otherAccount){
    myAccountNumber = number;
    this->fixedDeposit = fixDeposit;
    this->currentDeposit = currentDeposit;
    this->type = type;
    this->sum = sum;
    transferedAccountNumber = otherAccount;
}

//转账给别人
bool WTransfer::transferToOther(){
    int poundage;
    if(type == "normal")
        poundage = NORMALPOUNDAGE;
    else
        poundage = VIPPOUNDAGE;
    if(sum > currentDeposit - poundage)
        return false;
    else{
        bool result;
        DBTransactionRecordManip db;
        QVector<QString> transferInfo(5);
        transferInfo[0].setNum(DBAccountManip::dbSelectAccountKey(myAccountNumber));
        transferInfo[1].setNum(DBAccountManip::dbSelectAccountKey(transferedAccountNumber));
        transferInfo[2].setNum(sum);
        currentDeposit = currentDeposit -sum -poundage;
        transferInfo[3].setNum(currentDeposit);
        transferInfo[4].setNum(fixedDeposit);
        transferInfo[5] = "transfer to other";
        result = db.dbInsert(transferInfo);
        return result;
    }
}

//活期转定期
bool WTransfer::transferToFixed(){
    if(sum > currentDeposit)
        return false;
    else{
        bool result;
        DBTransactionRecordManip db;
        QVector<QString> transferInfo(5);
        transferInfo[0].setNum(DBAccountManip::dbSelectAccountKey(myAccountNumber));
        transferInfo[1].setNum(DBAccountManip::dbSelectAccountKey(myAccountNumber));
        transferInfo[2].setNum(sum);
        currentDeposit = currentDeposit - sum;
        fixedDeposit = fixedDeposit + sum;
        transferInfo[3].setNum(currentDeposit);
        transferInfo[4].setNum(fixedDeposit);
        transferInfo[5] = "transfer to fixed";
        result = db.dbInsert(transferInfo);
        return result;
    }
}

//定期转活期
bool WTransfer::transferToCurrent(){
    if(sum > fixedDeposit)
        return false;
    else{
        bool result;
        DBTransactionRecordManip db;
        QVector<QString> transferInfo;
        transferInfo[0].setNum(DBAccountManip::dbSelectAccountKey(myAccountNumber));
        transferInfo[1].setNum(DBAccountManip::dbSelectAccountKey(myAccountNumber));
        transferInfo[2].setNum(sum);
        currentDeposit = currentDeposit + sum;
        fixedDeposit = fixedDeposit - sum;
        transferInfo[3].setNum(currentDeposit);
        transferInfo[4].setNum(fixedDeposit);
        transferInfo[5] = "transfer to fixed";
        result = db.dbInsert(transferInfo);
        return result;
    }
}

