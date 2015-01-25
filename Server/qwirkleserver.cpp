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
    if( ::bind(serverSocket, (struct sockaddr*) &serverData, sizeof serverData) < 0 ) {
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
    close(serverSocket);
    sendPlayerList();

    //GIVE INITIAL PIECES
    for(int index = 0; index < playersConnections.size(); index++) {
        givePieces(index);
    }
}

void QwirkleServer::gameLoop(){
    Utils::printDate();
    cout<<"Server ready to play!";
    int player_index = 0;
    sendTurnMessage(player_index);
    while (1) {
        chat->serveChat();
        if (messages.size() > 0) {
            Message* message = messages.front();
            int type = message->getType();
            if (type == message->PIECE) {
                servePieceMessage(message, player_index);
            } else if (type == message->MOVE) {
                serveMoveMessage(message, player_index);
            }
            if (playersConnections[player_index]->getPlayer()->getPieceCount() == 0) {
                Utils::printDate();
                cout << "Game ended!" << endl;

                messages.erase(messages.begin());
                sendMessageToAll(new Message(Message::messageType::ENDGAME, "GAMEOVER", "SERVER"));
                break;
            }
            messages.erase(messages.begin());
            player_index = (player_index + 1) % playersConnections.size();
            sendTurnMessage(player_index);
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    while (1) {
        chat->serveChat();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void QwirkleServer::servePieceMessage(Message* message, int player_index) {
    Utils::printDate();
    cout<<"Player exchanged pieces: "<<message->getMessage()<<endl;

    int count = message->getMessage().size() / 4;
    playersConnections[player_index]->getPlayer()->takePieces(count);
    stringstream stream(message->getMessage());
    vector<Piece*> pieces;
    for (int i = 0; i < count; i++) {
        short color;
        short shape;
        char dot;
        stream >> color;
        stream >> dot;
        stream >> shape;
        stream >> dot;
        pieces.push_back(new Piece(color, shape));
    }
    pieceSack->returnPiece(pieces);
    givePieces(player_index);

    Message* exchange_message =
            new Message(Message::messageType::EXCHANGE, to_string(count), message->getSenderName());
    sendMessageToAll(exchange_message);
}

void QwirkleServer::serveMoveMessage(Message* message, int player_index) {
    Utils::printDate();
    cout<<"Player " << message->getSenderName() << " executed move: "<<message->getMessage()<<endl;
    int count = message->getMessageTokens().size() / 4;
    playersConnections[player_index]->getPlayer()->takePieces(count);
    givePieces(player_index);
    sendMessageToAll(message);
}

void QwirkleServer::closeGame() {
    close(serverSocket);
}

bool QwirkleServer::isNameUnique(string name){
    for(PlayerHandler* pl: playersConnections){
        if(pl->getPlayerName().compare(name) == 0)
            return false;
    }
    return true;
}

void QwirkleServer::awaitPlayerIntroduction() {
    clock_t start = clock();
    float timedif;

    while(1){

        timedif = ((float)(clock() - start))/CLOCKS_PER_SEC;
        if(timedif>REG_TIMEOUT)
            cout<<"Player didn't introduce himself. Discarding"<<endl;

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

void QwirkleServer::sendPlayerList() {
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

void QwirkleServer::sendTurnMessage(int index) {
    PlayerHandler* playing_player = playersConnections[index];
    string message = playing_player->getPlayerName() + ".";
    for (PlayerHandler* player: playersConnections) {
        player->sendMessage(new Message(Message::messageType::TURN, message, "SERVER"));
    }
    Utils::printDate();
    cout<<"Sended player turn: \n";
    cout<<Message::messageType::TURN<<"."<<"SERVER."<<message<<endl;
}

void QwirkleServer::givePieces(int index) {
    PlayerHandler* player = playersConnections[index];
    int ownPieces = player->getPlayer()->getPieceCount();
    vector<Piece*>* pieces = pieceSack->getPiece(6 - ownPieces);
    if (pieces != nullptr)
        player->givePieces(*pieces);
}

void QwirkleServer::sendMessageToAll(Message* message) {
    for (PlayerHandler* player: playersConnections) {
        player->sendMessage(message);
    }
}
