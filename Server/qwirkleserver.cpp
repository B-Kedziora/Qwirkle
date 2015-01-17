#include "qwirkleserver.h"

QwirkleServer::QwirkleServer(ConnectionData* cd, int players)
{ 
    messagesMutex = PTHREAD_MUTEX_INITIALIZER;
    chat = new Chat(&messages, messagesMutex, &playersConnections);
    pieceSack = new PieceSack();

    gameOngoing = false;
    expectedPlayers = players;

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
    while(playersConnections.size() < expectedPlayers) {

        struct sockaddr_in client_addr;
        int rcvSck;

        if((rcvSck = accept(serverSocket, (struct sockaddr*) &client_addr, (socklen_t*) &socketLength)) < 0){
            perror("ER");
            exit(EXIT_FAILURE);
        }

        Utils::printDate();
        cout<<"New player connected at socket: "<<rcvSck<<endl;
        playersConnections.push_back(new PlayerHandler(rcvSck, &messages, messagesMutex));

        awaitPlayerIntroduction();
    }

    sendPlayerList();

    //GIVE INITIAL PIECES
    for(PlayerHandler* handler : playersConnections) {
        givePieces(handler);
    }
}

void QwirkleServer::gameLoop(){
    Utils::printDate();
    cout<<"Server ready to play!";
    while(1){
        chat->serveChat();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
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
    clock_t start = clock();
    float timedif;

    while(1){

        timedif = ((float)(clock() - start))/CLOCKS_PER_SEC;
        if(timedif>REG_TIMEOUT)
            cout<<"Player didn't introduced himself. Discarding"<<endl;

        for(int i = 0; i < messages.size(); i++){
            Message* mes = messages.at(i);

            if(mes->getType() == mes->REGISTRATION){
                messages.erase(messages.begin() + i);   // Delete from vector, so it doesn't affect next registration

                string name = mes->getSenderName();
                if(isNameUnique(name)){ // Accept player
                    playersConnections.back()->setPlayerName(name); //Setting name means acceptance of player
                } else  {                // Reject player

                    Utils::printDate();
                    cout<<"Player name("<< mes->getSenderName() <<") is not unique. Closing connection."<<endl;

                    playersConnections.back()->discardPlayer();
                    playersConnections.pop_back();
                }

                delete mes;
                return;
            }

        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void QwirkleServer::sendPlayerList()
{
    // LIST CREATION
    string message = "";
    for(PlayerHandler* player : playersConnections) {
        message += player->getPlayerName() + ".";
    }

    // SENDING
    for(PlayerHandler* player: playersConnections) {    // creates new message in loop, cause sended messages are deleted by thread
        player->sendMessage(new Message(Message::messageType::PLAYER_LIST, message, "SERVER"));
    }

    Utils::printDate();
    cout<<"Sended player list: \n";
    cout<<Message::messageType::PLAYER_LIST<<"."<<"SERVER."<<message<<endl;
}

void QwirkleServer::givePieces(PlayerHandler *player)
{
    int ownPieces = player->getPlayer()->getPoints();

    vector<Piece*>* pieces = pieceSack->getPiece(6 - ownPieces);

    player->givePieces(*pieces);
}
