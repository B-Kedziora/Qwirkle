#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

using namespace std;

class Message
{
public:
    Message(short type, string mes, string sender);
    short getType();
    string getMessage();
    string getSenderName();
private:
    short type;
    string mes;
    string sender;
};

#endif // MESSAGE_H
