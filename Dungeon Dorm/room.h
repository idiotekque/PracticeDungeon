#include <vector>
#include "item.h"
#include "gameChar.h"

#ifndef ROOM_H
#define ROOM_H

using namespace std;

class Room 
{
 public:
    int position;
    bool isExit;
    vector<Item> items;
    vector<gameChar> enemies;
    // Room(int = 0, bool = false, vector<Item>, vector<gameChar>);
    Room(int = 0, bool = false, vector<Item> = vector<Item>(), vector<gameChar> = vector<gameChar>());
    void clearLoot();
    void clearEnemies();
};

#endif