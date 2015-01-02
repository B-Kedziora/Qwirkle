#ifndef CONNECTIONDATA_H
#define CONNECTIONDATA_H

#include <string>

using namespace std;

class ConnectionData
{
public:
    ConnectionData(string username, string ip, unsigned short port);
    string getName();
    string getIp();
    unsigned short getPort();
private:
    string name;
    string ip;
    unsigned short port;
};

#endif // CONNECTIONDATA_H
