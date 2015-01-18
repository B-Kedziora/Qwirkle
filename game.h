#ifndef GAME_H
#define GAME_H

#include "messagereceiver.h"
#include "Commons/message.h"
#include "Commons/board.h"
#include "widget.h"
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <QTableView>

class Game : public MessageReceiver
{
public:
    Game(Widget* widget);
    void receiveMessage(Message* mes);
    void receivePlayers(std::vector<string>);
    void receivePieces(std::vector<Piece> pieces);
    void executeMove(string name, vector<Drop>);
    void viewScore();

private:
    Widget* widget;
    Board board;
    std::vector<Piece> available_pieces;
    map<string, int> score;
    QStandardItemModel score_model;
};

#endif // GAME_H
