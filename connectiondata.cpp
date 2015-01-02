#include "connectiondata.h"

ConnectionData::ConnectionData(string username, string ip, unsigned short port)
{
    name = username;
    this->ip = ip;
    this->port = port;
}


string ConnectionData::getName()
{
    return name;
}

string ConnectionData::getIp()
{
    return ip;
}

unsigned short ConnectionData::getPort()
{
    return port;
}
