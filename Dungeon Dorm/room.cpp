#include "Room.h"

Room::Room(int pos, bool exit, vector<Item> itm, vector<gameChar> chars)
{
    position = pos;
    isExit = exit;
    items = itm;
    enemies = chars;
}
    
void Room::clearLoot() {
    items.clear();
}

void Room::clearEnemies() {
    enemies.clear();
}