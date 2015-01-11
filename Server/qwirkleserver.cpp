#include "qwirkleserver.h"

QwirkleServer::QwirkleServer(ConnectionData* cd, int players)
{ 
    messagesMutex = PTHREAD_MUTEX_INITIALIZER;

    gameOngoing = false;
    expectedPlayers = players;
    registeredPlayers = 0;

    bzero(&serverData, sizeof serverData);          // Zeroing structure
    serverData.sin_addr.s_addr = INADDR_ANY;        // Na każdym porcie komputera
    serverData.sin_family = AF_INET;                // Internet bytes order
    serverData.sin_port = htons(cd->getPort());     // host short

    if( (serverSocket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ) {
        perror(NULL);
        cout<<"Server creation failure"<<endl;
        exit(EXIT_FAILURE);
    }

    //Aditional options on socket
    int opt= 1;	//flag
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

    //Bind socket to address
    if( bind(serverSocket, (struct sockaddr*) &serverData, sizeof serverData) < 0 ) {
        perror(NULL);
        cout<<"Server creation failure"<<endl;
        exit(EXIT_FAILURE);
    }

    //Start listening on socket
    if( listen(serverSocket, expectedPlayers) < 0 ) {    //Expecet number of players is max connection number
        perror(NULL);
        cout<<"Server creation failure"<<endl;
        exit(EXIT_FAILURE);
    }

    //BOARD init

    Utils::printDate();
    cout<<"Server started to listen clients"<<endl;

    awaitPlayers();
    gameLoop();
    closeGame();
}

void QwirkleServer::awaitPlayers(){
    int socketLength = sizeof(struct sockaddr_in);
    while(expectedPlayers > registeredPlayers) {

        struct sockaddr_in client_addr;
        int rcvSck;

        if((rcvSck = accept(serverSocket, (struct sockaddr*) &client_addr, (socklen_t*) &socketLength)) < 0){
            perror("ER");
            exit(EXIT_FAILURE);
        }

        Utils::printDate();
        cout<<"New player connected"<<endl;
        playersConnections.push_back(new PlayerHandler(rcvSck, &messages, messagesMutex));

    }
}

void QwirkleServer::gameLoop(){

}

void QwirkleServer::closeGame(){
    close(serverSocket);
}

bool QwirkleServer::isNameUnique(string name){
    for(PlayerHandler* pl: playersConnections){
        if(pl->getPlayerName().compare(name) == 0)
            return false;
    }
    return true;
}

void QwirkleServer::awaitPlayerIntroduction()
{

}
