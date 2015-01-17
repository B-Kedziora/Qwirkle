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

void Message::debugPrint()
{
    switch(type){
        case messageType::REGISTRATION:
            cout<<"Type:REGISTRATION\n";
            break;
        case messageType::PLAYER_LIST:
            cout<<"Type:PLAYER_LIST\n";
            break;
        case messageType::CHAT:
            cout<<"Type:CHAT\n";
            break;
        case messageType::CONFIRM:
            cout<<"Type:CONFIRM\n";
            break;
        case messageType::MOVE:
            cout<<"Type:MOVE\n";
            break;
        case messageType::PIECE:
            cout<<"Type:PIECE\n";
            break;
        case messageType::TURN:
            cout<<"Type:TURN\n";
            break;
        default:
            cout<<"Type:OTHER\n";
    }
    cout<<"Sender:"<<sender<<"\n"<<"Message:"<<mes<<endl;
}

string Message::toString()
{
    string rawMessage(to_string(type) + string(".") + sender + string(".") + mes);
    return rawMessage;
}
