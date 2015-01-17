#ifndef BOARD_H
#define BOARD_H

#include <Commons/piece.h>
#include <algorithm>
#include <vector>
#include <Commons/drop.h>

/**
 * @brief The Board class represents the state of the game. Every
 * player owns it locally. On client side it's used as data for
 * BoardDisplayer.
 */

class Board
{
public:
    Board();
    void addDrop(Drop drop);
    void deleteDrop(Drop toDelete);
    void executeDrops();
    std::vector<std::vector <Piece> > getPieces();
    bool areDropsValid();
    int getDropPoints();
    bool isFieldEmpty(int posx, int posy);

private:
    enum Direction {
        HORIZONTAL,
        VERTICAL,
        NONE
    };
    bool areDropsInLine(enum Direction direction);
    enum Direction getDropsDirection();
    std::vector<Piece> getLine(Drop drop, enum Direction direction);
    bool doPiecesShareFeature(std::vector<Piece> pieces, enum Piece::Feature feature);
    bool doesFeatureRepeat(std::vector<Piece> pieces, enum Piece::Feature feature);
    bool areFeaturesCorrect(std::vector<Piece> line);
    bool isDropPartOfLine(Drop drop, enum Direction direction, int* length);
    bool isFieldEmpty(enum Drop::Coordinate first_coordinate, int pos1, int pos2);
    Piece getPiece(enum Drop::Coordinate first_coordinate, int pos1, int pos2);

private:
    std::vector<std::vector<Piece>> pieces;
    std::vector<Drop> drops;
    int drop_points;
};

#endif // BOARD_H
