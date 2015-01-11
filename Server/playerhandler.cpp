#include "playerhandler.h"


void* connect(void* args){
    ConnectionThreadArgs* ta = (ConnectionThreadArgs*) args;
    new ConnectionHandler(ta);
    return NULL;
}

PlayerHandler::PlayerHandler(int socket, std::vector<Message*> *recievedMessages, pthread_mutex_t receiveMutex)
{
    //Collecting data to initialize thread
     struct ConnectionThreadArgs* ta = new ConnectionThreadArgs();
     ta->socket = socket;
     ta->toSend = new std::vector<Message*>();
     ta->receivedMessages = recievedMessages;
     ta->player = new Player();
     ta->sendMutex = PTHREAD_MUTEX_INITIALIZER;;
     ta->receiveMutex = receiveMutex;

     //Keeping references for communication with main thread
     toSend = ta->toSend;
     player = ta->player;
     sendMutex = ta->sendMutex;
     this->receiveMutex = receiveMutex;
     this->socket = socket;

     pthread_create(&connectionThread, NULL, connect, (void*)ta);
}

void PlayerHandler::sendMessage(Message *mes)
{
    pthread_mutex_lock(&sendMutex);
    toSend->push_back(mes);
    pthread_mutex_unlock(&sendMutex);
}

void PlayerHandler::discardPlayer()
{
    pthread_kill(connectionThread, SIGTERM);
    pthread_join(connectionThread, NULL);
    delete player;
    close(socket);
}

string PlayerHandler::getPlayerName()
{
    return player->getName();
}

void PlayerHandler::setPlayerName(string name)
{
    player->setName(name);
}

