#include "player.h"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{
public:
    Player player;
    Room rooms[4];
    Dungeon(Player);
    int runDungeon();
    void enterRoom(Room *);
    void handleRoomEmpty(Room *);
    void handleRoomLoot(Room *);
    void handleRoomEnemy(Room *);
    void handleLootActions(Room *);
    void handleFightActions(gameChar *);
    void handleMovementActions(Room *);
    void printActions(int, string[]);
    int performEndGame();
};

#endif