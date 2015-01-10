#ifndef QWIRKLESERVER_H
#define QWIRKLESERVER_H

#include "../Commons/connectiondata.h"
#include "../Commons/utils.h"
#include <vector>
#include <QTcpServer>
#include <pthread.h>
#include "connectionhandler.h"
#include <iostream>
#include <qobject.h>

class QwirkleServer:QObject
{

    Q_OBJECT

    public:
        QwirkleServer(ConnectionData* cd, int players);
        ~QwirkleServer();

    private:
        bool gameOngoing;
        int expectedPlayers;
        std::string owner;
        //Board* board;
        QTcpServer* server;
        std::vector<std::string> messages;
        pthread_mutex_t messagesMutex;
        //players
        std::vector<ConnectionHandler*> connections;


    private slots:
        void newPlayerRegistration();
};

#endif // QWIRKLESERVER_H
