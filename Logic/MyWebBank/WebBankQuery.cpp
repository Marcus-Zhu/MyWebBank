#include "WebBankQuery.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"
#include <QVector>
#include <QDate>
#include <QDateTime>

QVector<QString> WQuery::queryRecentTenRecords(){
    QVector<QString> transactionRecord1;
    QVector<QString> transactionRecord2;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;

    DBPaymentRecordManip paymentManip;
    int key = DBAccountManip::dbSelectAccountKey(number);

    QString selectInfo1 = QString("SELECT * FROM transactionRecord WHERE accountKey1 = %1").arg(key);
    QString selectInfo2 = QString("SELECT * FROM transactionRecord WHERE accountKey2 = %1 AND accoutKey1 != %1").arg(key);

    transactionRecord1 = transferManip.dbSelect(selectInfo1);
    transactionRecord2 = transferManip.dbSelect(selectInfo2);

    QString selectInfo3 = QString("SELECT * FROM paymentRecord WHERE accountKey = %1").arg(key);

    paymentRecord = paymentManip.dbSelect(selectInfo3);

    //删除无用信息
    int size1 = (transactionRecord1.size()/7)>10?(transactionRecord1.size()/7):10;
    for(int i = 0;i<size1;i++){
        transactionRecord1.remove(7*(size1 - i - 1) + 5);
        transactionRecord1.remove(7*(size1 - i - 1) + 4);
        transactionRecord1.remove(7*(size1 - i - 1) + 1);
        transactionRecord1.remove(7*(size1 - i - 1) );
    }
    int size2 = (transactionRecord2.size()/7)>10?(transactionRecord2.size()/7):10;
    for(int i = 0;i<size2;i++){
        transactionRecord2[7*(size2 - i - 1) + 6] = "be transfered into";//转入信息，修改type对应项的值
        transactionRecord2.remove(7*(size2 - i - 1) + 5);
        transactionRecord2.remove(7*(size2 - i - 1) + 4);
        transactionRecord2.remove(7*(size2 - i - 1) + 1);
        transactionRecord2.remove(7*(size2 - i - 1) );
    }
    int size3 = paymentRecord.size()/5;
    for(int i = 0;i<size3;i++){
        paymentRecord.remove(5*(size3 - 1 - i) + 3);
        paymentRecord.remove(5*(size3 - 1 - i));
    }
    //构造传回去的QVector
    QVector<QString> recentRecord;
    for(int i = 0;i<size1;i++)
        recentRecord.push_back(transactionRecord1[i]);
    for(int i = 0;i<size2;i++)
        recentRecord.push_back(transactionRecord2[i]);
    for(int i = 0;i<size3;i++)
        recentRecord.push_back(paymentRecord[i]);
    //转时间为QDateTime对象
    int rows = recentRecord.size()/3;
    QDateTime times[rows];
    for(int i = 0;i<rows;i++,j++)
        times[i].fromString(recentRecord[1 + 3*i],"yyyy-MM-dd hh:mm:ss");
    //排序
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
                recentRecord[3*(j+1)] = temps[0];
                recentRecord[3*(j+1) + 1] = temps[1];
                recentRecord[3*(j+1) + 2] = temps[2];
            }
        }
}

QVector<QString> WQuery::queryRecentTenRecordsIncome(){
    DBTransactionRecordManip transferManip;
}
