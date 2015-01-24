#include "connection.h"

#include <QTcpSocket>

Connection::Connection(string* chatName, MessageReceiver* receiver, QObject *parent) :
    QObject(parent)
{
    this->receiver = receiver;
    conData = nullptr;
    bool hostingGame;
    int players;

    StartDialog* dialog = new StartDialog(&conData, &hostingGame, &players);
    dialog->exec();

    *chatName = conData->getName();

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
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    socket->connectToHost(QString::fromStdString(conData->getIp()), (quint16) conData->getPort());
}

void Connection::sendMessage(Message *message)
{
    QString mes = QString::fromStdString(message->toString());
    QByteArray qb = mes.toLatin1();
    char* encMes = qb.data();

    socket -> write(encMes);
}

void Connection::socketError(QAbstractSocket::SocketError)
{
    ErrorDialog* dialog = new ErrorDialog(QString::fromStdString("Server connection error"));
    dialog->exec();
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
    vector<string>* rawMessages = readSocket();
    for (string rawMessage : *rawMessages) {
        Message* mes = new Message(rawMessage);
        receiver->receiveMessage(mes);
    }
}

vector<string>* Connection::readSocket()
{
    QByteArray message = socket->readAll();
    string text = string(message.data());

    vector<string>* rawMessages = new vector<string>();
    char* mes = strtok(const_cast<char*>(text.c_str()), "\n");
    while (mes) {
        rawMessages->push_back(mes);
        mes = strtok(NULL, "\n");
    }
    return rawMessages;
}

void Connection::disconnected()
{
    ErrorDialog* dialog = new ErrorDialog(QString::fromStdString("Disconnected from server. If you can't start game try changing user name."));
    dialog->exec();
}
