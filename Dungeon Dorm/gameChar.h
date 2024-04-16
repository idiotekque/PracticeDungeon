#include <string>

#ifndef GAMECHAR_H
#define GAMECHAR_H

using namespace std;

class gameChar 
{
 public:
    string name;
    int maxHealth, currentHealth, attack, defense;
    gameChar(string, int, int, int);
    int takeDamage(int);
    bool checkDead();
};

#endif