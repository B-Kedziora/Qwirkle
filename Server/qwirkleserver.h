#ifndef QWIRKLESERVER_H
#define QWIRKLESERVER_H
#include "../Commons/connectiondata.h"
#include "../Commons/player.h"
#include "../Commons/utils.h"
#include "../Commons/message.h"
#include "piecesack.h"
#include <playerhandler.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <vector>
#include <arpa/inet.h>
#include <time.h>
#include <chat.h>
#include <chrono>
#include <thread>

#define REG_TIMEOUT 0.5

class QwirkleServer
{
public:
    QwirkleServer(ConnectionData* cd, int players);
    ~QwirkleServer();

private:
    void awaitPlayers();
    void gameLoop();
    void closeGame();
    bool isNameUnique(string name);
    void awaitPlayerIntroduction();
    void sendPlayerList();
    void sendTurnMessage(int index);
    void givePieces(int index);
    void sendMessageToAll(Message* message);
    void servePieceMessage(Message* message, int player_index);
    void serveMoveMessage(Message* message, int player_index);

    Chat* chat;
    PieceSack* pieceSack;
    bool gameOngoing;
    int expectedPlayers;
    vector<Message*> messages;
    pthread_mutex_t messagesMutex;
    vector<PlayerHandler*> playersConnections;
    struct sockaddr_in serverData;
    int serverSocket;
};

#endif // QWIRKLESERVER_H
