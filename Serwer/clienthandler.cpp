#include "clienthandler.h"

ClientHandler::ClientHandler(ConnectionHandler::ThreadArgs* args) : QObject(nullptr)
{
    socket = args->socket;
    toSend = args->toSend;
    receivedMessages = args->receivedMessages;
    playerName = args->playerName;

    if(socket->bytesAvailable() != 0){
        receiveMessage();
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));

}

void ClientHandler::receiveMessage()
{
    std::string message(socket->readAll().data());
    std::cout<<Utils::getDate()<<std::endl;
    std::cout<<"Received message: "<< message <<std::endl;

    receivedMessages->push_back(message);
}
