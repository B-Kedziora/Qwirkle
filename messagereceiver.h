#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "Commons/message.h"

class MessageReceiver
{
public:
    virtual void receiveMessage(Message* mes) = 0;
};

#endif // MESSAGERECEIVER_H
