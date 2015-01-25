#include "piece.h"

using namespace std;

Piece::Piece() {
    features[COLOR] = EMPTY;
    features[SHAPE] = EMPTY;
}

Piece::Piece(short color, short shape)
{
    features[COLOR] = color;
    features[SHAPE] = shape;
}

Piece::Piece(string text) {
    stringstream stream(text);
    short color;
    short shape;
    char dot;
    stream >> color;
    stream >> dot;
    stream >> shape;
    features[COLOR] = color;
    features[SHAPE] = shape;
}

short Piece::getColor()
{
    return features[COLOR];
}

short Piece::getShape()
{
    return features[SHAPE];
}

short Piece::getFeature(Feature feature) {
    return features[feature];
}

bool Piece::isEmpty() {
    return features[COLOR] == NONE && features[SHAPE] == EMPTY;
}

bool Piece::isEqual(Piece that) {
    if (this->features[COLOR] != that.features[COLOR]) return false;
    return (this->features[SHAPE] == that.features[SHAPE]);
}

std::string Piece::getDescription() {
    std::string text;
    text += to_string(features[COLOR]);
    text += string(".");
    text += to_string(features[SHAPE]);
    text += string(".");
    return text;
}
