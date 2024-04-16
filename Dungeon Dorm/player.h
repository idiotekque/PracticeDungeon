#include "room.h"

#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player: public gameChar
{
public:
    Room * currentRoom;
    Room * previousRoom;
    vector<Item> inventory;
    Player(string = "", int = 0, int = 0, int = 0);
    void addItem(Item);
    void increaseStats(int, int, int);
    void lootRoom(Room *);
    void changeRoom(Room *);
};

#endif