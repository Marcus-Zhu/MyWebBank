#include "wuimanip.h"
#include "wcurrentuser.h"
#include "wDBmanip.h"
#include "wuser.h"
#include "waccount.h"
#include "wcreditcard.h"
#include "wquery.h"
#include "wuser.h"

#include <QString>
#include <QVector>
#include <QDebug>

WUIManip::WUIManip()
{
}

int WUIManip::login(QString name, QString pwd)
{
    return WUser::checkIn(name, pwd);
}

bool WUIManip::registration(QVector<QString> userInfo)
{
    DBUserManip userManip;
    WCurrentUser::userName = userInfo[0];
    bool val1 = userManip.dbSelect(userInfo[0]);
    if (val1) return false;
    bool val2 = userManip.dbInsert(userInfo);
    WUser user;
    user.addAccount(userInfo[8], "normalAccount");
    return val2;
}

int WUIManip::getAccountNum()
{
    WUser *user = new WUser(WCurrentUser::userName);
    int val = user->account.size();
    delete user;
    return val;
}

QVector<QString> WUIManip::getAccountInfo(int num)
{
    QVector<QString> info;
    DBAccountManip accountmanip;
    info = accountmanip.dbSelect(num);
    return info;
}

QVector<QString> WUIManip::getAccountRecord(int accountNum)
{
    QVector<QString> info;
    DBAccountManip accountManip;
    QVector<QString> records;
    info = accountManip.dbSelect(accountNum);
    if(info[0] == "normalAccount")
    {
        WNormalAccount *account = new WNormalAccount(info[1]);
        records = account->recentRecords();
    }
    else
    {
        WCreditCard *creditCard = new WCreditCard(info[1]);
        records = creditCard->recentRecords();
    }
    return records;
}

bool WUIManip::transfer(QString account1, QString account2, QString amount)
{
    QVector<QString> info;
    DBAccountManip accountManip;
    info = accountManip.dbSelect(account1);
    if (info.size() == 0) return false;
    bool val = false;
    if(info[0] == "normalAccount")
    {
        WNormalAccount *account = new WNormalAccount(info[1]);
        val = account->transaction(TransferToOther, account2, amount.toFloat());
    }
    else
    {
        WCreditCard *creditCard = new WCreditCard(info[1]);
        val = creditCard->transaction(account2, amount.toFloat());
    }
    return val;
}

bool WUIManip::currentFix(int type, QString account1, QString account2, QString amount)
{
    QVector<QString> info;
    DBAccountManip accountManip;
    info = accountManip.dbSelect(account1);
    if (info.size() == 0) return false;
    bool val = false;
    if(info[0] == "normalAccount")
    {
        WNormalAccount *account = new WNormalAccount(info[1]);
        switch (type)
        {
        case 0:
            val = account->transaction(TransferToCurrent, account2, amount.toFloat());
            break;
        case 1:
            val = account->transaction(TransferToFixed, account2, amount.toFloat());
            break;
        default:
            return false;
        }
    }
    else
    {
        return false;
    }
    return val;
}

bool WUIManip::payment(QString type, QString account, QString amount)
{
    QVector<QString> info;
    DBAccountManip accountManip;
    info = accountManip.dbSelect(account);
    if (info.size() == 0) return false;
    bool val = false;
    if(info[0] == "normalAccount")
    {
        WNormalAccount *account = new WNormalAccount(info[1]);
        val = account->payment(type, amount.toFloat());
    }
    else
    {
        WCreditCard *creditCard = new WCreditCard(info[1]);
        val = creditCard->payment(type, amount.toFloat());
    }
    return val;
}

QVector<QString> WUIManip::query(int type, QString account)
{
    QVector<QString> records;
    WQuery query(account);
    switch(type)
    {
    case 0:
        records = query.queryRecentTenRecords();
        break;
    case 1:
        records = query.queryRecentTenRecordsIncome();
        break;
    case 2:
        records = query.queryRecentTenRecordsExpense();
        break;
    case 4:
        records = query.queryLatestThreeMonths();
        break;
    case 8:
        records = query.queryLatestThreeMonthIncome();
        break;
    case 16:
        records = query.queryLatestThreeMonthExpense();
        break;
    }
    return records;
}

QVector<QString> WUIManip::dateQuery(int type, QString account, QDate dateFrom, QDate dateTo)
{
    qDebug() << dateFrom << dateTo;
    QVector<QString> records;
    WQuery query(account);
    switch(type)
    {
    case 0:
        records = query.queryBetweenTwoDates(dateFrom, dateTo);
        break;
    case 1:
        records = query.queryBetweenTwoDatesIncome(dateFrom, dateTo);
        break;
    case 2:
        records = query.queryBetweenTwoDatesExpense(dateFrom, dateTo);
        break;
    }
    return records;
}



QVector<QString> WUIManip::getSysMsg()
{
    DBMessageManip msgManip;
    QVector<QString> msg = msgManip.dbSelect();
    msgManip.dbUpdate("");
    return msg;
}

bool WUIManip::changePwd(QString oldPwd, QString newPwd)
{
    WUser user(WCurrentUser::userName);
    bool val = user.setPassword(oldPwd, newPwd);
    return val;
}

QVector<QString> WUIManip::userInfo()
{
    WUser user(WCurrentUser::userName);
    QVector<QString> vec;
    SUserInfo info = user.getUserInfo();
    vec.push_back(info.name);
    vec.push_back(info.id);
    vec.push_back(info.createdDate);
    vec.push_back(info.tel);
    vec.push_back(info.email);
    vec.push_back(info.address);
    vec.push_back(info.zipCode);
    return vec;
}
