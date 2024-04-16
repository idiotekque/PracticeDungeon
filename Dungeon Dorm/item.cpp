#include "item.h"

#ifndef ITEM_H
#define ITEM_H

Item::Item(string nam, int hp, int atk, int def) {
    name = nam;
    health = hp;
    attack = atk;
    defense = def;
}

#endif