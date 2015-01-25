#ifndef PIECE_H
#define PIECE_H

#include<sstream>

class Piece
{
public:
    enum Feature {
        COLOR,
        SHAPE
    };

    enum pieceColor{
        BLUE,
        YELLOW,
        ORANGE,
        RED,
        GREEN,
        PURPLE,
        NONE
    };

    enum pieceShape{
        CIRCLE,
        SQUARE,
        STAR,
        DIAMOND,
        FLOWER,
        SHURIKEN,
        EMPTY
    };

    Piece();
    Piece(short color, short shape);
    Piece(std::string text);
    short getColor();
    short getShape();
    short getFeature(Feature feature);
    bool isEmpty();
    bool isEqual(Piece that);
    std::string getDescription();

private:
    short features[2];
};

#endif // PIECE_H
