#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>
#include <fstream>
#include <connection.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "Commons/piece.h"
#include "Commons/drop.h"

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
    void receivePieces(vector<Piece> pieces);
    void setTurn(string playername);
    ~Widget();

private slots:
    void on_SendButton_clicked();

    void on_MessageInput_returnPressed();

    void on_PiecesWidget_itemSelectionChanged();

    void on_pushButton_clicked();

private:
    void sendChatMessage();

    Ui::Widget *ui;
    Connection* connection;
    string chatName;
    QTableWidget* pieces_widget;
    QTableWidget* board_widget;
};

#endif // WIDGET_H
