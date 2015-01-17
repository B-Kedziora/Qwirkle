#include "chat.h"

Chat::Chat(vector<Message *>* messages, pthread_mutex_t messagesMutex, vector<PlayerHandler *>* playersConnections)
{
    this->messages = messages;
    this->messagesMutex = messagesMutex;
    this->playersConnections = playersConnections;
}

void Chat::serveChat()
{
    if(messages->size() != 0){
        vector<Message*> chatMessages;

        // Collect chat messages
        pthread_mutex_lock(&messagesMutex);
        for(int i = messages->size() - 1; i >= 0; i--) {
            cout<<"Is message"<<endl;
            Message* message = messages->at(i);
            if(message->getType() == Message::messageType::CHAT) {
                chatMessages.push_back(message);
                messages->erase(messages->begin() + i);
            }
        }
        pthread_mutex_unlock(&messagesMutex);

        if(chatMessages.size() != 0) {
            // Log
            Utils::printDate();
            cout << "Passing chat messages: " << endl;
            for(Message* mes : chatMessages) {
                mes->debugPrint();
                cout<<endl;
            }

            // Send chat messages
            for(Message* mes : chatMessages) {
                for(PlayerHandler* player : *playersConnections) {
                    player->sendMessage(mes);
                }
            }
        }
    }
}
