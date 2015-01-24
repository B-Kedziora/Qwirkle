#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "startdialog.h"
#include "Commons/connectiondata.h"
#include "messagereceiver.h"
#include "errordialog.h"
#include "qprocess.h"
#include <QTcpSocket>
#include <unistd.h>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(string* chatName, MessageReceiver* receiver, QObject *parent = 0);
    void sendMessage(Message* message);

private:
    vector<string>* readSocket();

private:
    QTcpSocket* socket;
    ConnectionData* conData;
    MessageReceiver* receiver;

signals:

public slots:
    void socketError(QAbstractSocket::SocketError);
    void socketConnected();
    void readAnswer();
    void disconnected();
};

#endif // CONNECTION_H
