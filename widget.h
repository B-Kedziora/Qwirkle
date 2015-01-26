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
#include "Commons/board.h"

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
    void receivePlayerCount(int count);
    void receiveExchangeMessage(Message* message);
    void receivePieces(vector<Piece> pieces);
    void setTurn(string message);
    int executeMove(vector<Drop> drops, string player);
    void displayWinner(QString winner);
    ~Widget();

private slots:
    void on_SendButton_clicked();
    void on_MessageInput_returnPressed();
    void on_MoveButton_clicked();
    void on_PiecesWidget_cellClicked(int row, int column);
    void on_BoardWidget_cellClicked(int row, int column);
    void on_ExchangeRadioButton_toggled(bool checked);

    void on_QuitButton_clicked();

private:
    void sendChatMessage();
    void resetMove();
    void sendDropMessage();
    QTableWidgetItem* createItem(Piece piece);

private:
    Ui::Widget *ui;
    Connection* connection;
    string chatName;
    bool players_turn;
    bool exchange_mode;
    vector<QTableWidgetItem*> player_pieces;
    Board board;
    int pieces_left;
};

#endif // WIDGET_H
