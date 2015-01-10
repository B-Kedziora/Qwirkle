#include "player.h"

Player::Player()
{
    name = "UNKNOWN";
    points = 0;
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
