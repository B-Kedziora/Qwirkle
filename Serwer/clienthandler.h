#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <qobject.h>
#include <connectionhandler.h>
#include <qtcpsocket.h>
#include "../Commons/utils.h"

class ClientHandler:QObject
{
    Q_OBJECT
public:
    ClientHandler(ConnectionHandler::ThreadArgs* args);
private:
    enum clientState{
        NEW,
        AWAITING_ACCEPT,
        IN_GAME,
    };

    void mainLoop();
    void sendMessages();
    void receiveMessage();

    clientState state;
    QTcpSocket* socket;
    std::vector<std::string>* toSend;
    std::vector<std::string>* receivedMessages;
    std::string* playerName;
};

#endif // CLIENTHANDLER_H
