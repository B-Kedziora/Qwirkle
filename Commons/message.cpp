#include "message.h"


Message::Message(short type, string mes, string sender)
{
    this->type = type;
    this->mes = mes;
    this->sender = sender;
}

Message::Message(string message)
{
    char *tokens = strtok(const_cast<char*>(message.c_str()), ".");
    try{

        type = stoi(string(tokens));
        tokens = strtok(NULL, ".");
        sender = string(tokens);
        tokens = strtok(NULL, ".");
        mes = "";
        while(tokens) {
            mes += string(tokens);
            tokens = strtok(NULL, ".");
        }

    } catch(exception e) {
        Utils::printDate();
        cout<<"Server received invalid message"<<endl;
        cout<<e.what()<<endl;
    }
}

short Message::getType()
{
    return type;
}

string Message::getMessage()
{
    return mes;
}

string Message::getSenderName()
{
    return sender;
}
