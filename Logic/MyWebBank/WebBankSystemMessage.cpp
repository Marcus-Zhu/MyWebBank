#include "WebBankSystemMessage.h"
#include "WebBankCurrentUser.h"
#include "WebBankDataBaseManip.h"
#include <QVector>
#include <QString>

WMessage::WMessage()
{
    setMessageNumber();
}

//改变是否已读的状态
bool WMessage::changeMessageStatus()
{
    QString updateInfo = "UPDATE FROM message SET status = 'already_read' WHERE status = 'not_read'";
    DBMessageManip messageManip;
    bool result = messageManip.dbUpdate(updateInfo);
    return result;
}

//设置新消息的数目
void WMessage::setMessageNumber(int n)
{
    DBMessageManip messageManip;
    messageNumber = messageManip.dbSelectMessageAmount();
    setHaveNewMessage();
}

//获取新消息数目
int WMessage::getMessageNumber()
{
    return messageNumber;
}

//设置是否有新消息
void WMessage::setHaveNewMessage()
{
    if(messageNumber == 0)
        haveNewMessage = false;
    else
        haveNewMessage = true;
}

//读取是否有新消息
bool WMessage::getHaveNewMessage()
{
    return haveNewMessage;
}

