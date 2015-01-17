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
            Utils::printDate();
            cout<< "Player: " << player->getName() << " is accepted by server"<<endl;
            write(socket, "0.SERVER.A", 11);
            break;
        }
        usleep(10000);
    }

    mainLoop();
}

void ConnectionHandler::mainLoop()
{
    while(1) {
        readMessages();
        sendMessages();
        usleep(10000);
    }
}

void ConnectionHandler::sendMessages()
{
    for(int i = toSend->size() - 1; i >= 0; i--) {
        Message* message = toSend->at(i);
        string mes = message->toString();
        write(socket, mes.c_str(), mes.length());

        pthread_mutex_lock(&sendMutex);
        toSend->erase(toSend->begin() + i);
        pthread_mutex_unlock(&sendMutex);

        Utils::printDate();
        cout<< "Sended message to: "<< player->getName() << "\nMessage: " << mes <<endl;
    }
}

void ConnectionHandler::readMessages()
{
    vector<string>* rawMessages = readSocket();
    if(rawMessages != nullptr) {
        for(string mes : *rawMessages){
            pthread_mutex_lock(&receiveMutex);
            Message* message = new Message(mes);
            receivedMessages->push_back(message);
            pthread_mutex_unlock(&receiveMutex);

            Utils::printDate();
            cout<< "Received: \n";
            message->debugPrint();
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
