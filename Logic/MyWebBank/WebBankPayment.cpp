#include "WebBankPayment.h"
#include "WebBankDataBaseManip.h"

WPayment::WPayment(){}

WPayment::WPayment(QString accountNumber, float sum, QString paymentType){
    number = accountNumber;
    sum = sum;
    type = paymentType;
    DBAccountManip dbAccount;
    QVector<QString> accountInfo = dbAccount.dbSelect(number);
    currentDeposit = (accountInfo[4].toFloat());
}

void WPayment::setAutoPayment(bool ifChoose[]){
    for(int i = 0;i<3;i++)
        haveAutoPayment[i] = ifChoose[i];
}

bool WPayment::isAutoPaymentEmpty(){
    for(int i = 0;i<3;i++){
        if(haveAutoPayment[i] == true)
            return false;//有自动缴费项目
    }
    return true;//无自动缴费项目
}

bool WPayment::pay(){
    if(currentDeposit<sum)
        return false;
    else{
        currentDeposit -= sum;
        DBAccountManip dbAccount;
        bool result = dbAccount.dbPaymentUpdate(number,currentDeposit);
        return result;
    }
}
