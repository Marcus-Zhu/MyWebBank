#ifndef WUIMANIP_H
#define WUIMANIP_H

#include <QString>
#include <QVector>

class WUIManip
{
public:
    WUIManip();
    static int login(QString name, QString pwd);
    static bool registration(QVector<QString> userInfo);
};

#endif // WUIMANIP_H
