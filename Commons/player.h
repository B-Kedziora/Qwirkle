#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../Commons/piece.h"
#include <vector>

using namespace std;

class Player
{
public:
    Player();
    void addPoints(int points);
    int getPoints();
    void setName(string newName);
    string getName();
    int getPieceCount();
    void givePices(int count);
    void takePieces(int count);
private:
    int points;
    string name;
    int pieceCount;
};

#endif // PLAYER_H
