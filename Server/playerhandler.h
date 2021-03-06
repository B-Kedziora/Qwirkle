#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include <vector>
#include <string>
#include <signal.h> //pthread_kill
#include <../Commons/message.h>
#include <../Commons/player.h>
#include <unistd.h> //close
#include <ConnectionThreadArgs.h>
#include <connectionhandler.h>

class PlayerHandler
{
public:
    PlayerHandler(int socket, std::vector<Message*>* recievedMessages, pthread_mutex_t receiveMutex);
    void sendMessage(Message* mes);
    void givePieces(vector<Piece*> pieces);
    void discardPlayer();
    string getPlayerName();
    Player* getPlayer();
    void setPlayerName(string);

private:
    Player* player;
    vector<Message*>* toSend;
    pthread_t connectionThread;
    pthread_mutex_t sendMutex;
    pthread_mutex_t receiveMutex;
    int socket;
};

#endif // PLAYERHANDLER_H
