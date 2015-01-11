#include "connectionhandler.h"

ConnectionHandler::ConnectionHandler(ConnectionThreadArgs *ta)
{

    socket = ta->socket;
    toSend = ta->toSend;
    receivedMessages = ta->receivedMessages;
    player = ta->player;
    sendMutex = ta->sendMutex;
    receiveMutex = ta->receiveMutex;

    //Setting socket to non-blocking read
    int flags = fcntl(socket, F_GETFL, 0);
    fcntl(socket, F_SETFL, flags | O_NONBLOCK);

    awaitAcceptation();
}

void ConnectionHandler::awaitAcceptation()
{
    cout<<"Waiting for a player's name"<<endl;
    while(42){
        readMessages();
        if(player->getName().compare("UNKNOWN") != 0){
            cout<< "Player: " << player->getName() << " is accepted by server"<<endl;
            //SEND MESSAGE
            break;
        }
        usleep(10000);
    }
    mainLoop();
}

void ConnectionHandler::mainLoop()
{

}

void ConnectionHandler::sendMessages()
{

}

void ConnectionHandler::readMessages()
{
    vector<string>* rawMessages = readSocket();
    if(rawMessages != nullptr) {
        for(string mes : *rawMessages){
            pthread_mutex_lock(&receiveMutex);
            receivedMessages->push_back(new Message(mes));
            pthread_mutex_unlock(&receiveMutex);
        }
    }
}

void ConnectionHandler::clearBuffer()
{
    for(int i=0; i < REC_BUFFER; i++)
        buffer[i] = 0;
}

vector<string>* ConnectionHandler::readSocket()
{
    clearBuffer();
    int receivedBytes = read(socket, buffer, REC_BUFFER);
    if(receivedBytes != -1 && receivedBytes != 0){  //Messages end with "\n". Seperates into token
        vector<string>* rawMessages = new vector<string>();
        char* mes = strtok(buffer, "\n");
        while (mes) {
            rawMessages->push_back(mes);
            mes = strtok(NULL, "\n");
        }
        return rawMessages;
    } else {
        return nullptr;
    }
}