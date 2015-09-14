#include "WebBankTransfer.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"
#include <QVector>

#define NORMALPOUNDAGE 0.005
#define VIPPOUNDAGE 0.002

WTransfer::WTransfer(const QString number, float &fixedDeposit,float &currentDeposit,
                     const QString type, const float sum, const QString otherAccount)
                     :fixedDeposit(fixedDeposit),currentDeposit(currentDeposit){
    myAccountNumber = number;
    this->type = type;
    this->sum = sum;
    transferedAccountNumber = otherAccount;
}

bool WTransfer::transferToOther(){
    int poundage;
    if(WCurrentUser::userType == "normal")
        poundage = NORMALPOUNDAGE*sum;
    else
        poundage = VIPPOUNDAGE*sum;
    if((sum > currentDeposit - poundage&&type == "normalAccount")
            ||(sum > currentDeposit + fixedDeposit - poundage&&type == "creditCard"))
        return false;
    else{
        bool result;
        DBTransactionRecordManip db;
        QVector<QString> transferInfo(6);
        transferInfo[0] = myAccountNumber;
        transferInfo[1] = transferedAccountNumber;
        transferInfo[2].setNum(sum);
        currentDeposit = currentDeposit -sum - poundage;
        transferInfo[3].setNum(fixedDeposit);
        transferInfo[4].setNum(currentDeposit);
        transferInfo[5] = "transfer to other";
        result = db.dbInsert(transferInfo);
        return result;
    }
}

bool WTransfer::transferToFixed(){
    if(sum > currentDeposit)
        return false;
    else{
        bool result;
        DBTransactionRecordManip db;
        QVector<QString> transferInfo(6);
        transferInfo[0] = myAccountNumber;
        transferInfo[1] = myAccountNumber;
        transferInfo[2].setNum(sum);
        currentDeposit = currentDeposit - sum;
        fixedDeposit = fixedDeposit + sum;
        transferInfo[3].setNum(fixedDeposit);
        transferInfo[4].setNum(currentDeposit);
        transferInfo[5] = "transfer to fixed";
        result = db.dbInsert(transferInfo);
        return result;
    }
}

bool WTransfer::transferToCurrent(){
    if(sum > fixedDeposit)
        return false;
    else{
        bool result;
        DBTransactionRecordManip db;
        QVector<QString> transferInfo(6);
        transferInfo[0] = myAccountNumber;
        transferInfo[1] = myAccountNumber;
        transferInfo[2].setNum(sum);
        currentDeposit = currentDeposit + sum;
        fixedDeposit = fixedDeposit - sum;
        transferInfo[3].setNum(fixedDeposit);
        transferInfo[4].setNum(currentDeposit);
        transferInfo[5] = "transfer to current";
        result = db.dbInsert(transferInfo);
        return result;
    }
}

