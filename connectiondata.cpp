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

string ConnectionData::toString()
{
    string res;
    res = string("Name: ") + name + string("\n");
    res += string("IP:") + ip + string("\n");
    res += string("Port:") + std::to_string(port) + string("\n");
    return res;
}
