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

        default:
            break;
    }
}

void Game::receivePlayers(std::vector<string> players) {
    for (string player : players) {
        points.insert(std::pair<string, int>(player, 0));
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
        int player_points = board.getDropPoints();
        board.executeDrops();
        points[name] += player_points;
    }
}
