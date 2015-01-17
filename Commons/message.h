#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <cstring>
#include <iostream>
#include "../Commons/utils.h"

using namespace std;

class Message
{
public:
    Message(short type, string mes, string sender);
    Message(string message);
    short getType();
    string getMessage();
    string getSenderName();
    void debugPrint();
    string toString();

    enum messageType{
        REGISTRATION,
        PLAYER_LIST,
        CHAT,
        MOVE,
        TURN,
        PIECE,
        CONFIRM
    };

private:
    short type;
    string mes;
    string sender;
};

#endif // MESSAGE_H
