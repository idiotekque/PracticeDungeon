#include "gameChar.h"

gameChar::gameChar(string nam, int hp, int atk, int def) {
    name = nam;
    maxHealth = hp;
    currentHealth = hp;
    attack = atk;
    defense = def;
}

int gameChar::takeDamage(int dmg)
{
    int damage = dmg - defense;
    if (damage < 0) {
        damage = 0;
    }
    currentHealth -= damage;
    return damage;
}

bool gameChar::checkDead()
{
    return currentHealth <= 0;
}