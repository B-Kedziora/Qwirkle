#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Game* game = new Game(this);
    connection = new Connection(&chatName, game);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_SendButton_clicked()
{
    sendChatMessage();
}

void Widget::on_MessageInput_returnPressed()
{
    sendChatMessage();
}

void Widget::sendChatMessage()
{
    Message* message = new Message(Message::messageType::CHAT, ui->MessageInput->text().toStdString(), chatName);
    connection->sendMessage(message);
    ui->MessageInput->setText("");
}
