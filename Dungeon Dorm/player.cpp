#include "player.h"

Player::Player(string nam, int hp, int atk, int def): gameChar(nam, hp, atk, def)
{
    Item flipknife = Item("Flipknife", 0, 5, 0);
    addItem(flipknife);
}

void Player::addItem(Item item) {
    inventory.push_back(item);
    increaseStats(item.health, item.attack, item.defense);
}

void Player::increaseStats(int hp, int atk, int def) {
    currentHealth += hp;
    maxHealth += hp;
    attack += atk;
    defense += def;
}

void Player::lootRoom(Room * room) {
    vector<Item> items = room->items;
    for (int i = 0; i < items.size(); i++) {
        addItem(items[i]);
    }
}

void Player::changeRoom(Room * newRoom) {
    previousRoom = currentRoom;
    currentRoom = newRoom;
}
