#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QTextStream>
#include <QDate>
#include "WebBankUser.h"
#include "WebBankAccount.h"
#include "WebBankCreditCard.h"
#include "WebBankDataBaseManip.h"
#include "WebBankPayment.h"
#include "WebBankQuery.h"
#include "WebBankSystemMessage.h"
#include "WebBankTransfer.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("WebBankDatabase.db");
    db.setUserName("txy");
    db.setPassword("494799822");

    QTextStream cin(stdin,QIODevice::ReadOnly);
    QTextStream cout(stdout,QIODevice::WriteOnly);
    QTextStream cerr(stderr,QIODevice::WriteOnly);

    if(!db.open())
        cout<<"failed to open the database"<<endl;

    QSqlQuery query;
    QString str1,str2;
    cin>>str1>>str2;
    int key = WUser::checkIn(str1,str2);
    if(key == 1)
        cout<<"name does not exist"<<endl;
    else if(key == 2)
        cout<<"pass word is wrong"<<endl;
    else
        cout <<"success"<<endl;


    SUserInfo info;
    query.prepare("SELECT * FROM user WHERE name = ?");
    query.addBindValue(str1);
    if(!query.exec())
        qDebug()<<query.lastError();
    else{
        query.next();
        info.name = query.value(1).toString();
        info.password = query.value(2).toString();
        info.id = query.value(3).toString();
        info.createdDate = query.value(4).toString();
        info.tel = query.value(5).toString();
        info.email = query.value(6).toString();
        info.address = query.value(7).toString();
        info.zipCode = query.value(8).toString();
        info.type = query.value(9).toString();
        WCurrentUser::userName = info.name;
        query.prepare("SELECT number FROM account WHERE userKey = ?");
        query.addBindValue(DBUserManip::dbSelectUserKey());
        if(!query.exec())
            qDebug()<<query.lastError();
        else{
            int i = 0;
            while(query.next()&&i<3){
                info.account.push_back(query.value(0).toString());
                i++;
            }
        }
        WMessage message;
        info.messageAmount = message.getMessageNumber();
    }
    WUser user(info);

//    DBPaymentRecordManip paymentManip;
//    paymentManip.dbTableCreate();
//    WNormalAccount norAccount;
//    norAccount.setAccountInfo(user.account[1]);
//    if(norAccount.payment("gas",65))
//        qDebug()<<"pay successfully";
//    else
//        qDebug()<<"fail to pay";

//    if(norAccount.transaction(TransferToOther,"2014011520",5000))
//        qDebug()<<"transfer successfully";
//    else
//        qDebug()<<"fail to transfer";
//    if(norAccount.transaction(TransferToFixed,norAccount.getAccountNumber(),10000))
//        qDebug()<<"transfer successfully";
//    else
//        qDebug()<<"fail to transfer";
//    WQuery que(user.account[0]);
//    QVector<QString> records;
//    QDate date1 = QDate::currentDate().addDays(-3);
//    QDate date2 = QDate::currentDate();
//    records = que.queryBetweenTwoDatesIncome(date1,date2);
//    for(int i = 0;i<records.size();i++)
//        qDebug()<<records[i];



    return a.exec();
}
