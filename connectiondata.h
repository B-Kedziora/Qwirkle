#ifndef CONNECTIONDATA_H
#define CONNECTIONDATA_H

class ConnectionData
{
public:
    ConnectionData(std::string username, std::string ip, unsigned short port);
    std::string getName();
    std::string getIp();
    unsigned short getPort();
private:
    std::string name;
    std::string ip;
    unsigned short port;
};

#endif // CONNECTIONDATA_H
