#include "piece.h"

Piece::Piece() {
    features[COLOR] = EMPTY;
    features[SHAPE] = EMPTY;
}

Piece::Piece(short color, short shape)
{
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
