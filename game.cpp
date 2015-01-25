#include "game.h"

using namespace std;

Game::Game(Widget* widget)
{
    this->widget = widget;
    board_widget = widget->findChild<QTableWidget*>("BoardWidget");
}

void Game::receiveMessage(Message *mes){
    switch(mes->getType()) {

        case Message::CHAT:
            widget->receiveChatMessage(mes);
        break;
        case Message::PLAYER_LIST:
            receivePlayers(mes->getMessageTokens());
        break;
        case Message::PIECE:
            receivePieces(mes->getMessage());
        break;
        case Message::TURN:
            widget->setTurn(mes->getMessage());
        break;
        case Message::EXCHANGE:
            widget->receiveExchangeMessage(mes);
        break;
        case Message::MOVE:
            receiveMoveMessage(mes);
        default:
            break;
    }
}

void Game::receivePlayers(vector<string> players) {
    QTableView* score_view = widget->findChild<QTableView*>("ScoreView");
    int index = 0;
    for (string player: players) {
        QStandardItem* name = new QStandardItem(QString::fromStdString(player));
        name->setEditable(false);
        score_model.setItem(index, 0, name);
        QStandardItem* score = new QStandardItem(QString::number(0));
        score->setEditable(false);
        score_model.setItem(index, 1, score);
        index++;
    }
    score_view->setModel(&score_model);
}

void Game::receivePieces(string message_text) {
    stringstream piece_message(message_text);
    short color, shape;
    char dot;
    vector<Piece> pieces;
    for (int i = 0; i < 6; i++){
        piece_message >> color;
        piece_message >> dot;
        piece_message >> shape;
        piece_message >> dot;
        pieces.push_back(Piece(color, shape));
    }
    widget->receivePieces(pieces);
}

void Game::receiveMoveMessage(Message* message) {
    vector<Drop> drops;
    vector<string> tokens = message->getMessageTokens();
    for (int i = 0; i < tokens.size(); i += 4) {
        Piece piece(tokens[i] + "." + tokens[i+1] + ".");
        Drop drop(piece, stoi(tokens[i+2]), stoi(tokens[i+3]));
        drops.push_back(drop);
    }
    int points = widget->executeMove(drops, message->getSenderName());

    QList<QStandardItem*> list =
            score_model.findItems(QString::fromStdString(message->getSenderName()));
    for (QStandardItem* name : list) {
        int row = score_model.indexFromItem(name).row();
        QStandardItem* score = score_model.item(row, 1);
        score->setText(QString::number(score->text().toInt() + points));
    }
}

void Game::executeMove(string name, vector<Drop> drops) {
    for (Drop drop : drops) {
        board.addDrop(drop);
    }
    if (board.areDropsValid()) {
        int points = board.getDropPoints();
        board.executeDrops();
        QList<QStandardItem*> list = score_model.findItems(QString::fromStdString(name));
        if (list.size() > 0) {
            QStandardItem* name_item = list.front();
            int row = score_model.indexFromItem(name_item).row();
            QStandardItem* score_item = score_model.item(row, 1);
            score_item->setText(QString::number(score_item->text().toInt() + points));
        }
    }
}
