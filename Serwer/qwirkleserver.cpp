#include "qwirkleserver.h"

QwirkleServer::QwirkleServer(ConnectionData *cd, int players) : QObject(nullptr)
{
    gameOngoing = false;
    owner = cd->getName();
    expectedPlayers = players;
    server = new QTcpServer();
    if(!server->listen(QHostAddress::Any, cd->getPort())) {             //Start listening
        std::cout<<"Server cannot start listening on port:"<<cd->getPort()<<" aborting"<<std::endl;
        return;
    }

    QObject::connect(server, SIGNAL(​newConnection()), this, SLOT(newPlayerRegistration()));
}

QwirkleServer::~QwirkleServer()
{
    server->close();
    for(ConnectionHandler* con : connections){
        con->discardPlayer();
    }
}

void QwirkleServer::newPlayerRegistration()
{
    cout<<"New player connected"<<endl;
    connections.push_back(new ConnectionHandler(server, &messages));
}
