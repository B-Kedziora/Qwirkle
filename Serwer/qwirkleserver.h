#ifndef QWIRKLESERVER_H
#define QWIRKLESERVER_H

#include "../Commons/connectiondata.h"
#include "../Commons/utils.h"
#include <vector>
#include <QTcpServer>

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
        //players
        //threads

    private slots:
        void newPlayerRegistration();
};

#endif // QWIRKLESERVER_H
