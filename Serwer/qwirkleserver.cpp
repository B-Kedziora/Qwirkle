#include "qwirkleserver.h"

QwirkleServer::QwirkleServer(ConnectionData *cd, int players)
{
    gameOngoing = false;
    owner = cd->getName();
    expectedPlayers = players;
    server = new QTcpServer();
    server->listen(QHostAddress::Any, cd->getPort());
    QObject::connect(server, newConnection(), this, newPlayerRegistration());
}

void QwirkleServer::newPlayerRegistration()
{

}
