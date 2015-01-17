#ifndef PIECESACK_H
#define PIECESACK_H

#include "../Commons/piece.h"
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace std;

class PieceSack
{
public:
    PieceSack();
    Piece* getPiece();
    vector<Piece*> getPiece(int pieces);
private:
    vector<Piece*> pieces;
};

#endif // PIECESACK_H
