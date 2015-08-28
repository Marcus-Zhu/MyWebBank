#ifndef WEBBANKDATABASEMANIP_H
#define WEBBANKDATABASEMANIP_H

#include <QtSql>
#include <QVector>
#include <QSqlQuery>

class WDBManip{
enum manipTable { user = 1, account = 2, transactionRecord = 3, paymentRecord = 4,
                  message = 5, fundMarket = 6, fundRecord = 7};

public:
    bool dbInsert(QVector<QString> insertInfo, manipTable type);
    bool dbUpdate(QString updateInfo,manipTable type);
    QString dbSelect(QString selectInfo,manipTable type);
    bool dbDelete(QString deleteInfo, manipTable type);
};
#endif // WEBBANKDATABASEMANIP_H
