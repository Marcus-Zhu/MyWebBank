#include "WebBankSystemMessage.h"
#include "WebBankCurrentUser.h"
#include "WebBankDataBaseManip.h"
#include <QVector>
#include <QString>

WMessage::WMessage(){
    setMessageNumber();
}

bool WMessage::changeMessageStatus(){
    QString updateInfo = "UPDATE FROM message SET status = 'already_read' WHERE status = 'not_read'";
    DBMessageManip messageManip;
    bool result = messageManip.dbUpdate(updateInfo);
    return result;
}

void WMessage::setMessageNumber(int n){
    DBMessageManip messageManip;
    messageNumber = messageManip.dbSelectMessageAmount();
    setHaveNewMessage();
}

int WMessage::getMessageNumber(){
    return messageNumber;
}

void WMessage::setHaveNewMessage(){
    if(messageNumber == 0)
        haveNewMessage = false;
    else
        haveNewMessage = true;
}

bool WMessage::getHaveNewMessage(){
    return haveNewMessage;
}

