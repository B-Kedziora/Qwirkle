#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>
#include <fstream>
#include <connection.h>
#include <QStandardItemModel>

class Widget;
#include "game.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void receiveChatMessage(Message* mes);
    ~Widget();

private slots:
    void on_SendButton_clicked();

    void on_MessageInput_returnPressed();

private:
    void sendChatMessage();

    Ui::Widget *ui;
    Connection* connection;
    string chatName;
};

#endif // WIDGET_H
