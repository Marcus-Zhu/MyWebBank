#ifndef WEBBANKQUERY_H
#define WEBBANKQUERY_H

#include <QVector>
#include <QDate>

class WQuery
{
public:
    QVector<QString> queryInfoRecentTenRecords;
    QVector<QString> queryRecentTenRecords();
    QVector<QString> queryRecentTenRecordsIncome();
    QVector<QString> queryRecentTenRecordsExpense();

    QVector<QString> queryInfoLatestThreeMonths;
    QVector<QString> queryLatestThreeMonths();
    QVector<QString> queryLatestThreeMonthExpense();
    QVector<QString> queryLatestThreeMonthIncome();

    QVector<QString> queryInfoBetweenDates;
    QVector<QString> queryBetweenTwoDates(QDate dateFrom, QDate dateTo);
    QVector<QString> queryBetweenTwoDatesIncome(QDate dateFrom, QDate dateTo);
    QVector<QString> queryBetweenTwoDatesExpense(QDate dateFrom, QDate dateTo);

    WQuery(QString number): number(number) {}
private:
    QString number;
};

#endif // WEBBANKQUERY_H

