#include "wuimanip.h"
#include "wcurrentuser.h"
#include "wDBmanip.h"
#include "wuser.h"
#include "waccount.h"
#include "wcreditcard.h"
#include "wpayment.h"
#include "wquery.h"
#include "wsysmsg.h"
#include "wuser.h"
#include "wnetworkcurrency.h"

#include <QString>
#include <QVector>
#include <QDebug>
#include <QSqlDatabase>

WUIManip::WUIManip()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("WebBankDatabase.db");
    database.setUserName("txy");
    database.setPassword("494799822");
}

bool WUIManip::openDatabase()
{
    database.open();
    return database.isValid() ? true : false;
}

void WUIManip::closeDatabase()
{
    database.close();
}

int WUIManip::login(QString name, QString pwd)
{
    int val = WUser::checkIn(name, pwd);
    if (val == 4)
    {
        DBLogRecordManip manip;
        QVector<QString> logInfo;
        logInfo.push_back("Log In");
        manip.dbInsert(logInfo);
    }
    WUser user(name);
    for (int i = 0; i < user.account.size(); ++i)
    {
        WPayment payment(user.account[i]);
        payment.autoPayment();
    }
    return val;
}

bool WUIManip::logout()
{
    DBLogRecordManip manip;
    QVector<QString> logInfo;
    logInfo.push_back("Log Out");
    return manip.dbInsert(logInfo);
}

bool WUIManip::registration(QVector<QString> userInfo)
{
    DBUserManip userManip;
    WCurrentUser::userName = userInfo[0];
    bool val1 = userManip.dbSelect(userInfo[0]);
    if (val1) return false;
    bool val2 = userManip.dbInsert(userInfo);
    WUser user;
    QString number = userInfo[8];
    QString type;
    if(number.toLong()%2 == 0)
        type = "normalAccount";
    else
        type = "VIP";
    user.addAccount(userInfo[8], type, 0);
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
        delete account;
    }
    else
    {
        WCreditCard *creditCard = new WCreditCard(info[1]);
        QString type = creditCard->getType();
        if (type == "platinumCard")
        {
            WPlatinumCard *card = new WPlatinumCard(info[1]);
            records = card->recentRecords();
            delete card;
        }
        else if (type == "goldCard")
        {
            WGoldCard *card = new WGoldCard(info[1]);
            records = card->recentRecords();
            delete card;
        }
        else if (type == "silverCard")
        {
            WSilverCard *card = new WSilverCard(info[1]);
            records = card->recentRecords();
            delete card;
        }
        else if (type == "normalCard")
        {
            WNormalCreditCard *card = new WNormalCreditCard(info[1]);
            records = card->recentRecords();
            delete card;
        }
        delete creditCard;
    }
    return records;
}

bool WUIManip::transfer(QString account1, QString account2, QString amount)
{
    if (account1 == account2)
    {
        return false;
    }
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
        QString type = creditCard->getType();
        if (type == "platinumCard")
        {
            WPlatinumCard *card = new WPlatinumCard(info[1]);
            val = card->transaction(account2, amount.toFloat());
            delete card;
        }
        else if (type == "goldCard")
        {
            WGoldCard *card = new WGoldCard(info[1]);
            val = card->transaction(account2, amount.toFloat());
            delete card;
        }
        else if (type == "silverCard")
        {
            WSilverCard *card = new WSilverCard(info[1]);
            val = card->transaction(account2, amount.toFloat());
            delete card;
        }
        else if (type == "normalCard")
        {
            WNormalCreditCard *card = new WNormalCreditCard(info[1]);
            val = card->transaction(account2, amount.toFloat());
            delete card;
        }
        delete creditCard;
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
        QString type = creditCard->getType();
        if (type == "platinumCard")
        {
            WPlatinumCard *card = new WPlatinumCard(info[1]);
            val = card->payment(type, amount.toFloat());
            delete card;
        }
        else if (type == "goldCard")
        {
            WGoldCard *card = new WGoldCard(info[1]);
            val = card->payment(type, amount.toFloat());
            delete card;
        }
        else if (type == "silverCard")
        {
            WSilverCard *card = new WSilverCard(info[1]);
            val = card->payment(type, amount.toFloat());
            delete card;
        }
        else if (type == "normalCard")
        {
            WNormalCreditCard *card = new WNormalCreditCard(info[1]);
            val = card->payment(type, amount.toFloat());
            delete card;
        }
        delete creditCard;
    }
    return val;
}

bool WUIManip::setAutopay(QString account, QString type)
{
    QVector<QString> info;
    info.push_back(account);
    info.push_back(type);
    DBAutoPayManip manip;
    if (!manip.dbSelectAutoPayment(type))
    {
        return false;
    }
    return manip.dbInsert(info);
}

bool WUIManip::cancelAutopay(QString account, QString type)
{
    DBAutoPayManip manip;
    if (manip.dbSelectAutoPayment(account, type))
    {
        return false;
    }
    return manip.dbDelete(account, type);
}

QVector<QString> WUIManip::getAutopayRecord()
{
    DBAutoPayManip manip;
    return manip.dbSelect();
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

bool WUIManip::cardApply(int type)
{
    WUser user(WCurrentUser::userName);
    QString account, accountType;
    DBAccountManip manip;
    switch(type)
    {
    case 0:
        accountType = "platinumCard";
        break;
    case 1:
        accountType = "goldCard";
        break;
    case 2:
        accountType = "silverCard";
        break;
    case 3:
        accountType = "normalCard";
        break;
    default:
        break;
    }
    do
    {
        account.clear();
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        for (int i = 0; i < 19; ++i)
        {
            account.append(QString::number(qrand() % 10));
        }
    }
    while(manip.dbSelectAccount(account));
    return user.addAccount(account, accountType);
}

bool WUIManip::cardActivate(QString account)
{
    WCreditCard card(account);
    return card.releaseAccount();
}

bool WUIManip::cardRepay(QString account1, QString account2, QString amount)
{
    QVector<QString> info;
    WCreditCard *creditCard = new WCreditCard(info[1]);
    return creditCard->transaction(account2, amount.toFloat());
}

bool WUIManip::cardLost(QString account)
{
    WCreditCard card(account);
    return card.freezeAccount();
}

QVector<QString> WUIManip::getSysMsg()
{
    DBMessageManip msgManip;
    QVector<QString> msg = msgManip.dbSelect();
    msgManip.dbUpdate("");
    return msg;
}

bool WUIManip::hasSysMsg()
{
    WMessage msg;
    msg.setMessageNumber();
    return msg.getHaveNewMessage();
}

bool WUIManip::changePwd(QString oldPwd, QString newPwd)
{
    WUser user(WCurrentUser::userName);
    return user.setPassword(oldPwd, newPwd);
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

QString *WUIManip::getCurrency()
{
    QString data = WNetworkCurrency::getHtml(QString("http://finance.yahoo.com/webservice/v1/symbols/allcurrencies/quote%E2%80%98") );
    QString *currency = new QString[4];
    currency[0] = "CNY";
    currency[1] = "EUR";
    currency[2] = "KRW";
    currency[3] = "JPY";
    float ratesToFloat[4];
    for(int i = 0; i < 4; i++)
    {
        int indexFrom = data.indexOf(currency[i]);
        for(int j = 0; j < 2; j++)
            indexFrom = data.indexOf('>', indexFrom + 1);
        int indexAfter = data.indexOf('<', indexFrom);
        indexAfter--, indexFrom++;
        QString rate;
        for(int j = indexFrom; j < indexAfter + 1; j++)
            rate.append(data[j]);
        ratesToFloat[i] = rate.toFloat();
    }
    ratesToFloat[0] = 1 / ratesToFloat[0];
    for(int i = 1; i < 4; i++)
        ratesToFloat[i] = ratesToFloat[i] * ratesToFloat[0];
    for(int i = 0; i < 4; i++)
        currency[i].setNum(ratesToFloat[i], 'f', 3);
    return currency;
}
