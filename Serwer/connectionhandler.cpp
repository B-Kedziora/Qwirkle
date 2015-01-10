#include "connectionhandler.h"


void* servePlayer(void* threadArgs){
    std::cout<<"Thread is running"<<std::endl;
    struct ConnectionHandler::ThreadArgs* args = (ConnectionHandler::ThreadArgs*) threadArgs;


    return NULL;
}

ConnectionHandler::ConnectionHandler(QTcpServer* server, std::vector<std::string>* receivedMessages)
{
    //Collecting data to initialize thread
    struct ConnectionHandler::ThreadArgs* ta;
    ta->socket = server->nextPendingConnection();
    ta->toSend = new std::vector<std::string>();
    ta->receivedMessages = receivedMessages;
    ta->playerName = new std::string();

    //Keeping references for communication with main thread
    toSend = ta->toSend;
    playerName = ta->playerName;

    pthread_create(connectionThread, NULL, servePlayer, (void*)ta);
}

void ConnectionHandler::sendMessage(std::string)
{

}

void ConnectionHandler::discardPlayer()
{

}

std::string ConnectionHandler::getPlayerName()
{
    if(*playerName == ""){
        return "NOT YET REGISTERED";
    } else {
        return *playerName;
    }
}

