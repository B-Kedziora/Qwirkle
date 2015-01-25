#include "board.h"

using namespace std;

Board::Board() :
    drop_points(-1),
    game_started(false)
{
    for (int i = 0; i < 181; i++) {
        pieces.push_back(vector<Piece>(181, Piece()));
    }
}

void Board::addDrop(Drop drop) {
    drops.push_back(drop);
    pieces[drop.position[0]][drop.position[1]] = drop.piece;
}

void Board::deleteDrops() {
    for (int i = drops.size() - 1; i >= 0; i--) {
        drops.erase(drops.begin() + i);
        pieces[drops[i].position[0]][drops[i].position[1]] = Piece();
    }
}

void Board::executeDrops() {
    game_started = true;
    drops.clear();
    drop_points = -1;
}

vector<vector<Piece>> Board::getPieces() {
    return pieces;
}

bool Board::areDropsValid() {
    drop_points = -1;
    sort(drops.begin(), drops.end());
    enum Direction direction = getDropsDirection();
    if (direction == NONE) {
        return false;
    }
    vector<Piece> main_line = getLine(drops.front(), direction);
    areFeaturesCorrect(main_line);
    int points = main_line.size();
    if (main_line.size() == 6)
        points += 6;
    for (Drop drop : drops) {
        int length = 0;
        if(!isDropPartOfLine(drop, (Direction)(1 - direction), &length)) {
                return false;
        }
        if (length > 1) points += length;

        if (length == 6) points += 6;
    }
    if (points == drops.size() && game_started || points == 0) {
        return false;
    }
    drop_points = points;
    return true;
}

int Board::getDropPoints() {
    if (drop_points == -1) {
        areDropsValid();
    }
    return drop_points;
}

bool Board::isFieldEmpty(int posx, int posy) {
    return (pieces[posx][posy].isEmpty());
}

bool Board::areDropsInLine(enum Direction direction) {
    enum Drop::Coordinate coordinate =
            (direction == HORIZONTAL) ? Drop::Coordinate::POSX : Drop::Coordinate::POSY;
    if (drops.front().position[coordinate] == drops.back().position[coordinate]) {
        for (int i = drops.front().position[1 - coordinate]; i <= drops.back().position[1 - coordinate]; i++) {
            if (!isFieldEmpty(drops.front().position[coordinate], i))
                return false;
        }
        return true;
    }
    return false;
}

enum Board::Direction Board::getDropsDirection() {
    sort(drops.begin(), drops.end());
    if (areDropsInLine(HORIZONTAL)) {
        return HORIZONTAL;
    }
    if (areDropsInLine(VERTICAL)) {
        return VERTICAL;
    }
    return NONE;
}

vector<Piece> Board::getLine(Drop drop, enum Direction direction) {
    vector<Piece> line = vector<Piece>();
    line.push_back(drop.piece);
    enum Drop::Coordinate common_coordinate =
            (direction == HORIZONTAL) ? Drop::Coordinate::POSX : Drop::Coordinate::POSY;
    int common_position = drop.position[common_coordinate];
    int min = drop.position[1 - common_coordinate];
    int max = drop.position[1 - common_coordinate];
    while (!isFieldEmpty(common_coordinate, common_position, min - 1)) {
        min--;
        line.push_back(getPiece(common_coordinate, common_position, min));
    }
    while (!isFieldEmpty(common_coordinate, common_position, max + 1)) {
        max--;
        line.push_back(getPiece(common_coordinate, common_position, max));
    }
    return line;
}

bool Board::doPiecesShareFeature(vector<Piece> line, enum Piece::Feature feature) {
    short piece_feature = line.front().getFeature(feature);
    bool same_feature = true;
    for (Piece piece : line) {
        if (piece.getFeature(feature) != piece_feature) {
            same_feature = false;
            continue;
        }
    }
    return same_feature;
}

bool Board::doesFeatureRepeat(vector<Piece> line, enum Piece::Feature feature) {
    int size = line.size();
    vector<int> features;
    for (Piece piece : line) {
        features.push_back(piece.getFeature(feature));
    }
    sort(features.begin(), features.end());
    unique(features.begin(), features.end());
    return (features.size() != size);
}

bool Board::areFeaturesCorrect(vector<Piece> line) {
    Piece::Feature common_feature = Piece::Feature::COLOR;
    if (doPiecesShareFeature(line, Piece::Feature::SHAPE)) {
        common_feature = Piece::Feature::SHAPE;
    } else if (!doPiecesShareFeature(line, Piece::Feature::COLOR)) {
        return false;
    }
    if (doesFeatureRepeat(line, (Piece::Feature)(1 - common_feature))) {
        return false;
    }
    return true;
}

bool Board::isDropPartOfLine(Drop drop, enum Direction direction, int* length) {
    vector<Piece> line = getLine(drop, direction);
    *length = line.size();
    return areFeaturesCorrect(line);
}

bool Board::isFieldEmpty(enum Drop::Coordinate first_coordinate, int pos1, int pos2) {
    if (first_coordinate == Drop::Coordinate::POSX) {
        return isFieldEmpty(pos2, pos1);
    }
    return isFieldEmpty(pos2, pos1);
}

Piece Board::getPiece(enum Drop::Coordinate first_coordinate, int pos1, int pos2) {
    if (first_coordinate == Drop::Coordinate::POSX) {
        return pieces[pos1][pos2];
    }
    return pieces[pos2][pos1];
}
