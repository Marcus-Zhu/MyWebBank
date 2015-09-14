#include "wquery.h"
#include "wDBmanip.h"
#include "wcurrentuser.h"
#include <QVector>
#include <QDate>
#include <QDateTime>

QVector<QString> WQuery::queryRecentTenRecords()
{
    QVector<QString> transactionRecord1;
    QVector<QString> transactionRecord2;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;
    DBPaymentRecordManip paymentManip;
    int key = DBAccountManip::dbSelectAccountKey(number);
    QString selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1 ORDER BY key DESC").arg(key);
    QString selectInfo2 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey2 = %1 AND accountKey1 != %1 ORDER BY key DESC").arg(key);
    transactionRecord1 = transferManip.dbSelect(selectInfo1, 3);
    transactionRecord2 = transferManip.dbSelect(selectInfo2, 3);
    QString selectInfo3 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1 ORDER BY key DESC").arg(key);
    paymentRecord = paymentManip.dbSelect(selectInfo3, 3);

    int size1 = (transactionRecord1.size() / 3) < 10 ? (transactionRecord1.size() / 3) : 10;
    int size2 = (transactionRecord2.size() / 3) < 10 ? (transactionRecord2.size() / 7) : 10;
    for(int i = 0; i < size2; i++)
    {
        transactionRecord2[3 * i + 2] = "be transfered into";
    }
    int size3 = paymentRecord.size() / 3;

    QVector<QString> recentRecord;
    for(int i = 0; i < size1 * 3; i++)
        recentRecord.push_back(transactionRecord1[i]);
    for(int i = 0; i < size2 * 3; i++)
        recentRecord.push_back(transactionRecord2[i]);
    for(int i = 0; i < size3 * 3; i++)
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

QVector<QString> WQuery::queryRecentTenRecordsIncome()
{
    DBTransactionRecordManip transferManip;
    QVector<QString> incomeInfo;
    QString selectInfo = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey2 = %1 ORDER BY key DESC")
                         .arg(DBAccountManip::dbSelectAccountKey(number));
    incomeInfo = transferManip.dbSelect(selectInfo, 3);
    while(incomeInfo.size() > 30)
        incomeInfo.remove(30);

    //    int rows = incomeInfo.size()/3;
    //    QDateTime times[rows];
    //    for(int i = 0;i<rows;i++)
    //        times[i] = QDateTime::fromString(incomeInfo[1 + 3*i],"yyyy-MM-dd hh:mm:ss");

    //    for(int i = 0;i<rows -1;i++)
    //        for(int j = 0;j<rows -1;j++){
    //            if(times[j]<times[j + 1]){
    //                QDateTime temp;
    //                temp = times[j];
    //                times[j] = times[j + 1];
    //                times[j + 1] = temp;
    //                QString temps[3];
    //                temps[0] = incomeInfo[3*j];
    //                temps[1] = incomeInfo[3*j + 1];
    //                temps[2] = incomeInfo[3*j + 2];
    //                incomeInfo[3*j] = incomeInfo[3*(j+1)];
    //                incomeInfo[3*j + 1] = incomeInfo[3*(j+1) + 1];
    //                incomeInfo[3*j + 2] = incomeInfo[3*(j+1) + 2];
    //                incomeInfo[3*(j+1)] = temps[0];
    //                incomeInfo[3*(j+1) + 1] = temps[1];
    //                incomeInfo[3*(j+1) + 2] = temps[2];
    //            }
    //        }
    return incomeInfo;
}

QVector<QString> WQuery::queryRecentTenRecordsExpense()
{

    QVector<QString> transactionRecord;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;
    DBPaymentRecordManip paymentManip;
    int key = DBAccountManip::dbSelectAccountKey(number);
    QString selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1 "
                                  "ORDER BY key DESC").arg(key);
    transactionRecord = transferManip.dbSelect(selectInfo1, 3);
    QString selectInfo2 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1 "
                                  "ORDER BY key DESC").arg(key);
    paymentRecord = paymentManip.dbSelect(selectInfo2, 3);

    int size1 = (transactionRecord.size() / 3) < 10 ? (transactionRecord.size() / 3) : 10;
    int size2 = (paymentRecord.size() / 3) < 10 ? (paymentRecord.size() / 3) : 10;

    QVector<QString> expenseInfo;
    for(int i = 0; i < size1 * 3; i++)
        expenseInfo.push_back(transactionRecord[i]);
    for(int i = 0; i < size2 * 3; i++)
        expenseInfo.push_back(paymentRecord[i]);

    //    int rows = size1 + size2;
    //    QDateTime times[rows];
    //    for(int i = 0;i<rows;i++)
    //        times[i] = QDateTime::fromString(expenseInfo[1 + 3*i],"yyyy-MM-dd hh:mm:ss");

    //    for(int i = 0;i<rows -1;i++)
    //        for(int j = 0;j<rows -1;j++){
    //            if(times[j]<times[j + 1]){
    //                QDateTime temp;
    //                temp = times[j];
    //                times[j] = times[j + 1];
    //                times[j + 1] = temp;
    //                QString temps[3];
    //                temps[0] = expenseInfo[3*j];
    //                temps[1] = expenseInfo[3*j + 1];
    //                temps[2] = expenseInfo[3*j + 2];
    //                expenseInfo[3*j] = expenseInfo[3*(j+1)];
    //                expenseInfo[3*j + 1] = expenseInfo[3*(j+1) + 1];
    //                expenseInfo[3*j + 2] = expenseInfo[3*(j+1) + 2];
    //                expenseInfo[3*(j+1)] = temps[0];
    //                expenseInfo[3*(j+1) + 1] = temps[1];
    //                expenseInfo[3*(j+1) + 2] = temps[2];
    //            }
    //        }
    return expenseInfo;
}

QVector<QString> WQuery::queryLatestThreeMonths()
{

    QVector<QString> transactionRecord1;
    QVector<QString> transactionRecord2;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;
    DBPaymentRecordManip paymentManip;
    int key = DBAccountManip::dbSelectAccountKey(number);
    QString selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1 "
                                  "AND time > datetime('now','-3 month') ORDER BY key DESC").arg(key);
    QString selectInfo2 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey2 = %1 AND accountKey1 != %1 "
                                  "AND time > datetime('now','-3 month') ORDER BY key DESC").arg(key);
    transactionRecord1 = transferManip.dbSelect(selectInfo1, 3);
    transactionRecord2 = transferManip.dbSelect(selectInfo2, 3);
    QString selectInfo3 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1"
                                  " AND time > datetime('now','-3 month') ORDER BY key DESC").arg(key);
    paymentRecord = paymentManip.dbSelect(selectInfo3, 3);

    int size1 = (transactionRecord1.size() / 3) < 10 ? (transactionRecord1.size() / 3) : 10;
    int size2 = (transactionRecord2.size() / 3) < 10 ? (transactionRecord2.size() / 7) : 10;
    for(int i = 0; i < size2; i++)
    {
        transactionRecord2[3 * i + 2] = "be transfered into";
    }
    int size3 = (paymentRecord.size() / 3) < 10 ? (paymentRecord.size() / 3) : 10;

    QVector<QString> recentRecord;
    for(int i = 0; i < size1 * 3; i++)
        recentRecord.push_back(transactionRecord1[i]);
    for(int i = 0; i < size2 * 3; i++)
        recentRecord.push_back(transactionRecord2[i]);
    for(int i = 0; i < size3 * 3; i++)
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

QVector<QString> WQuery::queryLatestThreeMonthIncome()
{

    DBTransactionRecordManip transferManip;
    QVector<QString> incomeInfo;
    QString selectInfo = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey2 = %1 "
                                 "AND time > datetime('now','-3 month') ORDER BY key DESC")
                         .arg(DBAccountManip::dbSelectAccountKey(number));
    incomeInfo = transferManip.dbSelect(selectInfo, 3);

    //    int rows = incomeInfo.size()/3;
    //    QDateTime times[rows];
    //    for(int i = 0;i<rows;i++)
    //        times[i] = QDateTime::fromString(incomeInfo[1 + 3*i],"yyyy-MM-dd hh:mm:ss");

    //    for(int i = 0;i<rows -1;i++)
    //        for(int j = 0;j<rows -1;j++){
    //            if(times[j]<times[j + 1]){
    //                QDateTime temp;
    //                temp = times[j];
    //                times[j] = times[j + 1];
    //                times[j + 1] = temp;
    //                QString temps[3];
    //                temps[0] = incomeInfo[3*j];
    //                temps[1] = incomeInfo[3*j + 1];
    //                temps[2] = incomeInfo[3*j + 2];
    //                incomeInfo[3*j] = incomeInfo[3*(j+1)];
    //                incomeInfo[3*j + 1] = incomeInfo[3*(j+1) + 1];
    //                incomeInfo[3*j + 2] = incomeInfo[3*(j+1) + 2];
    //                incomeInfo[3*(j+1)] = temps[0];
    //                incomeInfo[3*(j+1) + 1] = temps[1];
    //                incomeInfo[3*(j+1) + 2] = temps[2];
    //            }
    //        }
    return incomeInfo;
}

QVector<QString> WQuery::queryLatestThreeMonthExpense()
{
    QVector<QString> transactionRecord;
    QVector<QString> paymentRecord;
    DBTransactionRecordManip transferManip;
    DBPaymentRecordManip paymentManip;
    QString selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1 "
                                  "AND time > datetime('now','-3 month') ORDER BY key DESC").arg(DBAccountManip::dbSelectAccountKey(number));
    transactionRecord = transferManip.dbSelect(selectInfo1, 3);
    QString selectInfo2 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1 "
                                  "AND time > datetime('now','-3 month') ORDER BY key DESC").arg(DBAccountManip::dbSelectAccountKey(number));
    paymentRecord = paymentManip.dbSelect(selectInfo2, 3);

    int size1 = (transactionRecord.size() / 3) < 10 ? (transactionRecord.size() / 3) : 10;
    int size2 = (paymentRecord.size() / 3) < 10 ? (paymentRecord.size() / 3) : 10;
    QVector<QString> expenseInfo;
    for(int i = 0; i < size1 * 3; i++)
        expenseInfo.push_back(transactionRecord[i]);
    for(int i = 0; i < size2 * 3; i++)
        expenseInfo.push_back(paymentRecord[i]);

    //    int rows = size1 + size2;
    //    QDateTime times[rows];
    //    for(int i = 0;i<rows;i++)
    //        times[i] = QDateTime::fromString(expenseInfo[1 + 3*i],"yyyy-MM-dd hh:mm:ss");

    //    for(int i = 0;i<rows -1;i++)
    //        for(int j = 0;j<rows -1;j++){
    //            if(times[j]<times[j + 1]){
    //                QDateTime temp;
    //                temp = times[j];
    //                times[j] = times[j + 1];
    //                times[j + 1] = temp;
    //                QString temps[3];
    //                temps[0] = expenseInfo[3*j];
    //                temps[1] = expenseInfo[3*j + 1];
    //                temps[2] = expenseInfo[3*j + 2];
    //                expenseInfo[3*j] = expenseInfo[3*(j+1)];
    //                expenseInfo[3*j + 1] = expenseInfo[3*(j+1) + 1];
    //                expenseInfo[3*j + 2] = expenseInfo[3*(j+1) + 2];
    //                expenseInfo[3*(j+1)] = temps[0];
    //                expenseInfo[3*(j+1) + 1] = temps[1];
    //                expenseInfo[3*(j+1) + 2] = temps[2];
    //            }
    //        }
    return expenseInfo;
}

QVector<QString> WQuery::queryBetweenTwoDates(QDate dateFrom, QDate dateTo)
{

    QDateTime date1(dateFrom), date2(dateTo.addDays(1));
    QString date3 = date1.toString("yyyy-MM-dd hh:mm:ss");
    QString date4 = date2.toString("yyyy-MM-dd hh:mm:ss");

    DBTransactionRecordManip transferManip;
    DBPaymentRecordManip paymentManip;
    QString selectInfo1, selectInfo2, selectInfo3;
    selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1 AND time > datetime('%2') AND time < datetime('%3')")
                  .arg(DBAccountManip::dbSelectAccountKey(number)).arg(date3).arg(date4);
    selectInfo2 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 != %1 AND accountKey2 = %1 AND time > datetime('%2') AND time < datetime('%3')")
                  .arg(DBAccountManip::dbSelectAccountKey(number)).arg(date3).arg(date4);
    selectInfo3 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1 AND time > datetime('%2') AND time < datetime('%3')")
                  .arg(DBAccountManip::dbSelectAccountKey(number)).arg(date3).arg(date4);
    QVector<QString> transactionRecord1, transactionRecord2, paymentRecord;
    transactionRecord1 = transferManip.dbSelect(selectInfo1, 3);
    transactionRecord2 = transferManip.dbSelect(selectInfo2, 3);
    paymentRecord = paymentManip.dbSelect(selectInfo3, 3);

    QVector<QString> infoBetweenTwoDays;
    int size1 = transactionRecord1.size() / 3;
    int size2 = transactionRecord2.size() / 3;
    int size3 = paymentRecord.size() / 3;
    for(int i = 0; i < size1 * 3; i++)
        infoBetweenTwoDays.push_back(transactionRecord1[i]);
    for(int i = 0; i < size2; i++)
    {
        infoBetweenTwoDays.push_back(transactionRecord1[3 * i]);
        infoBetweenTwoDays.push_back(transactionRecord1[3 * i + 1]);
        infoBetweenTwoDays.push_back("be transfered into");
    }
    for(int i = 0; i < size3 * 3; i++)
        infoBetweenTwoDays.push_back(paymentRecord[i]);

    //    int rows = size1 + size2 + size3;
    //    QDateTime times[rows];
    //    for(int i = 0;i<rows;i++)
    //        times[i] = QDateTime::fromString(infoBetweenTwoDays[3*i + 1],"yyyy-MM-dd hh:mm:ss");

    //    for(int i = 0;i<rows -1;i++)
    //        for(int j = 0;j<rows -1;j++){
    //            if(times[j]<times[j + 1]){
    //                QDateTime temp;
    //                temp = times[j];
    //                times[j] = times[j + 1];
    //                times[j + 1] = temp;
    //                QString temps[3];
    //                temps[0] = infoBetweenTwoDays[3*j];
    //                temps[1] = infoBetweenTwoDays[3*j + 1];
    //                temps[2] = infoBetweenTwoDays[3*j + 2];
    //                infoBetweenTwoDays[3*j] = infoBetweenTwoDays[3*(j+1)];
    //                infoBetweenTwoDays[3*j + 1] = infoBetweenTwoDays[3*(j+1) + 1];
    //                infoBetweenTwoDays[3*j + 2] = infoBetweenTwoDays[3*(j+1) + 2];
    //                infoBetweenTwoDays[3*(j+1)] = temps[0];
    //                infoBetweenTwoDays[3*(j+1) + 1] = temps[1];
    //                infoBetweenTwoDays[3*(j+1) + 2] = temps[2];
    //            }
    //        }
    return infoBetweenTwoDays;
}

QVector<QString> WQuery::queryBetweenTwoDatesIncome(QDate dateFrom, QDate dateTo)
{

    QDateTime date1(dateFrom), date2(dateTo.addDays(1));
    QString date3 = date1.toString("yyyy-MM-dd hh:mm:ss");
    QString date4 = date2.toString("yyyy-MM-dd hh:mm:ss");

    DBTransactionRecordManip transferManip;
    QString selectInfo;
    selectInfo = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey2 = %1 AND time > datetime('%2') AND time < datetime('%3')")
                 .arg(DBAccountManip::dbSelectAccountKey(number)).arg(date3).arg(date4);
    QVector<QString> infoBetweenTwoDays;
    infoBetweenTwoDays = transferManip.dbSelect(selectInfo, 3);
    for(int i = 0; i < infoBetweenTwoDays.size() / 3; i++)
        if(infoBetweenTwoDays[3 * i + 2] == "transfer to other")
            infoBetweenTwoDays[3 * i + 2] = "be transfered into";

    //    int rows = infoBetweenTwoDays.size()/3;
    //    QDateTime times[rows];
    //    for(int i = 0;i<rows;i++)
    //        times[i] = QDateTime::fromString(infoBetweenTwoDays[3*i + 1],"yyyy-MM-dd hh:mm:ss");

    //    for(int i = 0;i<rows -1;i++)
    //        for(int j = 0;j<rows -1;j++){
    //            if(times[j]<times[j + 1]){
    //                QDateTime temp;
    //                temp = times[j];
    //                times[j] = times[j + 1];
    //                times[j + 1] = temp;
    //                QString temps[3];
    //                temps[0] = infoBetweenTwoDays[3*j];
    //                temps[1] = infoBetweenTwoDays[3*j + 1];
    //                temps[2] = infoBetweenTwoDays[3*j + 2];
    //                infoBetweenTwoDays[3*j] = infoBetweenTwoDays[3*(j+1)];
    //                infoBetweenTwoDays[3*j + 1] = infoBetweenTwoDays[3*(j+1) + 1];
    //                infoBetweenTwoDays[3*j + 2] = infoBetweenTwoDays[3*(j+1) + 2];
    //                infoBetweenTwoDays[3*(j+1)] = temps[0];
    //                infoBetweenTwoDays[3*(j+1) + 1] = temps[1];
    //                infoBetweenTwoDays[3*(j+1) + 2] = temps[2];
    //            }
    //        }
    return infoBetweenTwoDays;
}

QVector<QString> WQuery::queryBetweenTwoDatesExpense(QDate dateFrom, QDate dateTo)
{

    QDateTime date1(dateFrom), date2(dateTo.addDays(1));
    QString date3 = date1.toString("yyyy-MM-dd hh:mm:ss");
    QString date4 = date2.toString("yyyy-MM-dd hh:mm:ss");

    DBTransactionRecordManip transferManip;
    DBPaymentRecordManip paymentManip;
    QString selectInfo1, selectInfo2;
    selectInfo1 = QString("SELECT sum,time,type FROM transactionRecord WHERE accountKey1 = %1 AND time > datetime('%2') AND time < datetime('%3')")
                  .arg(DBAccountManip::dbSelectAccountKey(number)).arg(date3).arg(date4);
    selectInfo2 = QString("SELECT sum,time,type FROM paymentRecord WHERE accountKey = %1 AND time > datetime('%2') AND time < datetime('%3')")
                  .arg(DBAccountManip::dbSelectAccountKey(number)).arg(date3).arg(date4);
    QVector<QString> transactionRecord;
    QVector<QString> paymentRecord;
    transactionRecord = transferManip.dbSelect(selectInfo1, 3);
    paymentRecord = paymentManip.dbSelect(selectInfo2, 3);

    int size1 = transactionRecord.size() / 3;
    int size2 = paymentRecord.size() / 3;
    QVector<QString> expenseBetweenTwoDates;
    for(int i = 0; i < size1 * 3; i++)
        expenseBetweenTwoDates.push_back(transactionRecord[i]);
    for(int i = 0; i < size2 * 3; i++)
        expenseBetweenTwoDates.push_back(paymentRecord[i]);

    //    int rows = size1 + size2;
    //    QDateTime times[rows];
    //    for(int i = 0;i<rows;i++)
    //        times[i] = QDateTime::fromString(expenseBetweenTwoDates[3*i + 1],"yyyy-MM-dd hh:mm:ss");

    //    for(int i = 0;i<rows -1;i++)
    //        for(int j = 0;j<rows -1;j++){
    //            if(times[j]<times[j + 1]){
    //                QDateTime temp;
    //                temp = times[j];
    //                times[j] = times[j + 1];
    //                times[j + 1] = temp;
    //                QString temps[3];
    //                temps[0] = expenseBetweenTwoDates[3*j];
    //                temps[1] = expenseBetweenTwoDates[3*j + 1];
    //                temps[2] = expenseBetweenTwoDates[3*j + 2];
    //                expenseBetweenTwoDates[3*j] = expenseBetweenTwoDates[3*(j+1)];
    //                expenseBetweenTwoDates[3*j + 1] = expenseBetweenTwoDates[3*(j+1) + 1];
    //                expenseBetweenTwoDates[3*j + 2] = expenseBetweenTwoDates[3*(j+1) + 2];
    //                expenseBetweenTwoDates[3*(j+1)] = temps[0];
    //                expenseBetweenTwoDates[3*(j+1) + 1] = temps[1];
    //                expenseBetweenTwoDates[3*(j+1) + 2] = temps[2];
    //            }
    //        }
    return expenseBetweenTwoDates;
}



