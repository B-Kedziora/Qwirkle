#ifndef GAME_H
#define GAME_H

#include "messagereceiver.h"
#include "Commons/message.h"

class Game : public MessageReceiver
{
public:
    Game();
    void receiveMessage(Message* mes);
};

#endif // GAME_H
