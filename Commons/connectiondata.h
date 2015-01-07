#ifndef CONNECTIONDATA_H
#define CONNECTIONDATA_H

#include <string>
#include <sstream>

using namespace std;

class ConnectionData
{
public:
    ConnectionData(string username, string ip, unsigned short port);
    ConnectionData(string connectionData);
    string getName();
    string getIp();
    unsigned short getPort();
    string toString();
private:
    string name;
    string ip;
    unsigned short port;
};

#endif // CONNECTIONDATA_H
