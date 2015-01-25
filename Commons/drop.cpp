#include "drop.h"

Drop::Drop()
{

}

Drop::Drop(Piece new_piece, int posx, int posy) : piece(new_piece) {
    position[POSX] = posx;
    position[POSY] = posy;
}

bool Drop::operator<(const Drop& that) const {
    if (this->position[POSX] < that.position[POSX]) return true;
    if (this->position[POSX] > that.position[POSX]) return false;
    if (this->position[POSY] < that.position[POSY]) return true;
    return false;
}

bool Drop::isEqual(Drop that){
    if (this->position[POSX] != that.position[POSX]) return false;
    if (this->position[POSY] != that.position[POSY]) return false;
    return this->piece.isEqual(that.piece);
}

Piece Drop::getPiece() {
    return piece;
}

int Drop::getPosX() {
    return position[POSX];
}

int Drop::getPosY() {
    return position[POSY];
}
