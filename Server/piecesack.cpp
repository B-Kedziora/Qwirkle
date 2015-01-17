#include "piecesack.h"

PieceSack::PieceSack()
{
    for(int i = 0; i < 6; i++) {            // Color
        for(int j = 0; j < 6; j++) {        // Shape
            for(int k = 0; k < 3; k++) {    // Copy
                pieces.push_back(new Piece(i, j));
            }
        }
    }
    reshuffle();
}

Piece* PieceSack::getPiece()
{
    if(pieces.size() != 0) {
        Piece* piece = pieces.back();
        pieces.pop_back();
        return piece;
    } else {
        return nullptr;
    }
}

void PieceSack::returnPiece(Piece *piece)
{
    pieces.push_back(piece);
    reshuffle();
}

void PieceSack::returnPiece(vector<Piece *> retPieces)
{
    pieces.reserve( pieces.size() + retPieces.size() );
    pieces.insert( pieces.end(), retPieces.begin(), retPieces.end() );
    reshuffle();
}

void PieceSack::reshuffle()
{
    srand ( unsigned(time(0)) );
    random_shuffle ( pieces.begin(), pieces.end() );
}

vector<Piece*>* PieceSack::getPiece(int pieces)
{
    vector<Piece*>* pieceVec = new vector<Piece*>();
    for(int i = 0; i < pieces; i++) {
        Piece* piece = getPiece();
        if(piece == nullptr) {
            break;
        } else {
            pieceVec->push_back(piece);
        }
    }

    if(pieceVec->size() != 0)
        return pieceVec;
    else
        return nullptr;
}
