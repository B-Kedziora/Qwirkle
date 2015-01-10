#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <vector>
#include <string>
#include <pthread.h>
#include <QTcpServer>
#include <iostream>

class ConnectionHandler
{
public:
    ConnectionHandler(QTcpServer* server, std::vector<std::string>* recievedMessages);
    void sendMessage(std::string);
    void discardPlayer();
    std::string getPlayerName();

    struct ThreadArgs{
        QTcpSocket* socket;
        std::vector<std::string>* toSend;
        std::vector<std::string>* receivedMessages;
        std::string* playerName;
    };

private:
    std::string* playerName;
    std::vector<std::string>* toSend;
    pthread_t* connectionThread;
};


#endif // CONNECTIONHANDLER_H
