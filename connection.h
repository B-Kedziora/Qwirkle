#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "startdialog.h"
#include "Commons/connectiondata.h"
#include "qprocess.h"
#include <QTcpSocket>
#include <unistd.h>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);

private:
    QTcpSocket* socket;
    ConnectionData* conData;

signals:

public slots:
    void socketError(QAbstractSocket::SocketError);
    void socketConnected();
    void readAnswer();
};

#endif // CONNECTION_H
