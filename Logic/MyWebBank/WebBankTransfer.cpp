#include "WebBankTransfer.h"
#include "WebBankTransfer.h"
#include <QVector>

#define NORMALPOUNDAGE 10
#define VIPPOUNDAGE 5

WTransfer::WTransfer(){
    myAccountNumber = "";
    transferedAccountNumber = "";
    sum = 0.0f;
    myAccountBalance = 0.0f;
}

WTransfer::WTransfer(const QString number, float &balance, const float sum, const QStirng otherAccount){
    myAccountNumber = number;
    myAccountBalance = balance;
    this->sum = sum;
    transferedAccountNumber = otherAccount;
}

bool WTransfer::transfer(){
    if()
}
