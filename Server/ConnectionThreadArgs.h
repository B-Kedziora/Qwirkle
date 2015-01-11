#ifndef CONNECTIONTHREADARGS_H
#define CONNECTIONTHREADARGS_H

#include "../Commons/player.h"
#include "../Commons/message.h"

struct ConnectionThreadArgs{
    int socket;
    std::vector<Message*>* toSend;
    std::vector<Message*>* receivedMessages;
    Player* player;
    pthread_mutex_t sendMutex;
    pthread_mutex_t receiveMutex;
};

#endif // CONNECTIONTHREADARGS_H
