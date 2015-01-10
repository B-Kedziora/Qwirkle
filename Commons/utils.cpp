#include "utils.h"

Utils::Utils()
{
}

std::string Utils::getDate()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
    return buf;
}

void Utils::printDate()
{
    std::cout<<Utils::getDate()<<std::endl;
}
