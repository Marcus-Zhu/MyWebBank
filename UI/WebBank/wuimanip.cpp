#include "wuimanip.h"
#include "WebBankCurrentUser.h"
#include "WebBankDataBaseManip.h"
#include "WebBankUser.h"

#include <QString>
#include <QVector>

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
    bool val = userManip.dbInsert(userInfo);
    WUser user;
    user.addAccount(userInfo[8],"normalAccount");
    return val;
}
