#ifndef CHAT_H
#define CHAT_H

#include "playerhandler.h"

class Chat
{
public:
    Chat(vector<Message*>* messages, pthread_mutex_t messagesMutex, vector<PlayerHandler*>* playersConnections);
    void serveChat();
private:

    vector<Message*>* messages;
    pthread_mutex_t messagesMutex;
    vector<PlayerHandler*>* playersConnections;
};

#endif // CHAT_H
