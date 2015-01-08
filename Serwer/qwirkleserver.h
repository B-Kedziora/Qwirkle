#ifndef QWIRKLESERVER_H
#define QWIRKLESERVER_H

#include "../Commons/connectiondata.h"
#include "../Commons/utils.h"
#include <vector>
#include <QTcpServer>
#include <pthread.h>
#include <connection.h>

class QwirkleServer
{
    public:
        QwirkleServer(ConnectionData* cd, int players);

    private:
        bool gameOngoing;
        int expectedPlayers;
        std::string owner;
        Board* board;
        QTcpServer* server;
        std::vector<std::string> messages;
        pthread_mutex_t messagesMutex;
        //players
        std::vector<Connection*> connections;


    private slots:
        void newPlayerRegistration();
};

#endif // QWIRKLESERVER_H
