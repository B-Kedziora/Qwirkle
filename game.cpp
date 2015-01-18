#include "game.h"

using namespace std;

Game::Game(Widget* widget)
{
    this->widget = widget;
}

void Game::receiveMessage(Message *mes){
    switch(mes->getType()) {

        case Message::CHAT:
            widget->receiveChatMessage(mes);
        break;
        case Message::PLAYER_LIST:
            receivePlayers(mes->getMessageTokens());
        break;
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
    QList<QStandardItem*> list = score_model.findItems(QString::fromStdString(players[0]));
    for (QStandardItem* name : list) {
        int points = 5;
        int row = score_model.indexFromItem(name).row();
        QStandardItem* score = score_model.item(row, 1);
        score->setText(QString::number(score->text().toInt() + points));
    }
}

void Game::receivePieces(vector<Piece> pieces) {
    for (Piece piece : pieces) {
        available_pieces.push_back(piece);
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
