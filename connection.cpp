#include "connection.h"

#include <QTcpSocket>

Connection::Connection(QObject *parent) :
    QObject(parent)
{
    conData = nullptr;
    bool hostingGame;
    int players;

    StartDialog* dialog = new StartDialog(&conData, &hostingGame, &players);
    dialog->exec();

    if(hostingGame) {
        QStringList arg;
        arg << QString::fromStdString(conData->toString()) << QString::number(players);
        QProcess* serverProcess = new QProcess(this);
        serverProcess->start("./Server", arg);
        cout<<"Running server...";
        while(serverProcess->Running != 2)
            cout<<".";
            cout.flush();
        usleep(10000);
    }

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readAnswer()));
    socket->connectToHost(QString::fromStdString(conData->getIp()), (quint16) conData->getPort());
}

void Connection::socketError(QAbstractSocket::SocketError)
{
    // Notify widget about that
}

void Connection::socketConnected()
{
    QString introduction = "0." + QString::fromStdString(conData->getName()) + ".0";

    QByteArray qb = introduction.toLatin1();
    char* intro = qb.data();

    socket -> write(intro);
}

void Connection::readAnswer()
{

}
