#include "connectiondata.h"

ConnectionData::ConnectionData(std::string username, std::string ip, unsigned short port)
{
    name = username;
    this->ip = ip;
    this->port = port;
}


std::string ConnectionData::getName()
{
    return name;
}

std::string ConnectionData::getIp()
{
    return ip;
}

unsigned short ConnectionData::getPort()
{
    return port;
}
