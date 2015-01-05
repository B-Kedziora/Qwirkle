#ifndef PIECE_H
#define PIECE_H

class Piece
{
public:
    enum pieceColor{
        BLUE,
        YELLOW,
        ORANGE,
        RED,
        GREEN,
        PURPLE
    };

    enum pieceShape{
        CIRCLE,
        SQUARE,
        STAR,
        DIAMOND,
        FLOWER,
        SHURIKEN
    };

    Piece(short color, short shape);
    short getColor();
    short getShape();
private:
    short color;
    short shape;
};

#endif // PIECE_H
