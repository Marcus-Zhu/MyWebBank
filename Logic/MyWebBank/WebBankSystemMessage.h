#ifndef WEBBANKSYSTEMMESSAGE_H
#define WEBBANKSYSTEMMESSAGE_H

class WMessage{
private:
    bool haveNewMessage;
    int messageNumber;

public:
    bool changeMessageStatus();
    void setHaveNewMessage();
    bool getHaveNewMessage();
    void setMessageNumber(int n = 0);
    int getMessageNumber();
}

#endif // WEBBANKSYSTEMMESSAGE_H
