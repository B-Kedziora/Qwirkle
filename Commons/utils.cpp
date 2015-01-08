#include "utils.h"

#include <QDateTime>

Utils::Utils()
{
}

std::string Utils::getDate()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString();
    return dateTimeString.toStdString();
}
