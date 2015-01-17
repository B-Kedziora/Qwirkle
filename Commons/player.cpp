#include "player.h"

Player::Player()
{
    name = "UNKNOWN";
    points = 0;
    pieceCount = 0;
}

void Player::addPoints(int points)
{
    this->points += points;
}

int Player::getPoints()
{
    return points;
}

void Player::setName(string newName)
{
    this->name = newName;
}

string Player::getName()
{
    return this->name;
}

int Player::getPieceCount()
{
    return pieceCount;
}

void Player::givePieces(int count)
{
    pieceCount += count;
}

void Player::takePieces(int count)
{
    pieceCount -= count;
}
