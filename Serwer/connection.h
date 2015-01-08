#ifndef CONNECTION_H
#define CONNECTION_H

#include <vector>
#include <string>
#include <pthread.h>

class Connection
{
public:
    Connection();
    void sendMessage(std::string);
    void discardPlayer();
private:
    std::string playerName;
    std::vector<std::string> toSend;
    pthread_t connectionThread;
};

#endif // CONNECTION_H
