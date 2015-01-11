#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "../Commons/utils.h"
#include "ConnectionThreadArgs.h"
#include <unistd.h> //usleep
#include <fcntl.h>

#define REC_BUFFER 1000

using namespace std;

class ConnectionHandler
{
public:
    ConnectionHandler(ConnectionThreadArgs* ta);

private:
    void awaitAcceptation();
    void sendMessages();
    void readMessages();
    void clearBuffer();
    vector<string>* readSocket();
    void mainLoop();

    int socket;
    vector<Message*>* toSend;
    vector<Message*>* receivedMessages;
    Player* player;
    pthread_mutex_t sendMutex;
    pthread_mutex_t receiveMutex;
    char buffer[REC_BUFFER];
};

#endif // CONNECTIONHANDLER_H
