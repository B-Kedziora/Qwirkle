#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player
{
public:
    Player();
    void addPoints(int points);
    int getPoints();
    void setName(string newName);
    string getName();
private:
    int points;
    string name;
};

#endif // PLAYER_H
