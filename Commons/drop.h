#ifndef DROP_H
#define DROP_H

#include <Commons/piece.h>

class Drop
{
friend class Board;

public:
    enum Coordinate {
        POSX,
        POSY
    };
    Drop(Piece new_piece, int posx, int posy);
    bool operator<(const Drop& that) const;
    bool isEqual(Drop that);

private:
    Drop();

private:
    Piece piece;
    int position[2];
};

#endif // DROP_H
