#include "dungeon.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace chrono;
using namespace this_thread;

Dungeon::Dungeon(Player plr)
{
    player = plr;
}

void Dungeon::printActions(int numActions, string actions[]) {
    cout << "What do you do?" <<endl;
    for (int i = 0; i < numActions; i++) {
        cout << actions[i] <<endl;
    }
}

void Dungeon::handleFightActions(gameChar * enemy) {
    milliseconds micro(500);
    string actions[] = {
        "1. Strike.",
        "2. Run away.",
    };
    while(true) {
        printActions(2, actions);
        string input;
        cin >> input;
        // handle player actions
        if (input == "1") {
            int damage = enemy->takeDamage(player.attack);
            cout << "You deal " << damage << " damage." <<endl<<endl;
        } else if (input == "2") {
            player.changeRoom(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        } else {
            cout << "What do you do?" <<endl;
        }
        // check if enemy is dead
        if (enemy->checkDead()) {
            cout << "Your vision burns, and then you're alone again. You win." <<endl<<endl;
            player.increaseStats(10, 5, 5);
            cout << "There's a flicker in your chest." <<endl;
            sleep_for (micro);
            cout << "Your vitality is now " << player.currentHealth << "." <<endl;
            sleep_for (micro);
            cout << "Your offense is now " << player.attack << "." <<endl;
            sleep_for (micro);
            cout << "Your defense is now " << player.defense << "." <<endl<<endl;
            player.currentRoom->clearEnemies ();    
            return;    
        }
        // handle enemy actions
        int damage = player.takeDamage(enemy->attack);
        cout << enemy->name << " lashes out. You take " << damage << " damage." <<endl;
        cout << "You're reduced to " << player.currentHealth << " HP." <<endl<<endl;
        if (player.checkDead()) {
            return;
        }
    }
}

void Dungeon::handleRoomEnemy(Room * room) {
    gameChar enemy = room->enemies.front();
    cout << "You aren't alone here. Reality parts like a curtain, and you see " << enemy.name << " before you." <<endl<<endl;
    string actions[] = {
        "1. Defend yourself.",
        "2. Run away.",
        };
    while(true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "1") {
            handleFightActions(&enemy);
            return;
        } else if (input == "2") {
            player.changeRoom(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        } else {
            cout << "What do you do?" <<endl;
        }
    }
}

void Dungeon::handleLootActions(Room * room) {
    milliseconds micro(500);
    Item item = room->items.front();
    int size = room->items.size();
    player.lootRoom(room);
    room->clearLoot();
    for(int i = 0; i < size; i++) {
        cout << "It's as if whatever you're looking for is on the fringes of perception, and then you touch it. You find " << item.name <<endl<<endl; 
        cout << "There's a flicker in your chest." <<endl;
        sleep_for (micro);
        cout << "Your vitality is now " << player.currentHealth << "." <<endl;
        sleep_for (micro);
        cout << "Your offense is now " << player.attack << "." <<endl;
        sleep_for (micro);
        cout << "Your defense is now " << player.defense << "." <<endl<<endl;
    }
}

void Dungeon::handleRoomLoot(Room * room) {
    cout << "Your skin prickles as you step through the doorframe - there's something here." <<endl<<endl;
    string actions[] = {
        "1. Investigate.",
        "2. Keep moving.",
        };
    while(true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "1") {
            handleLootActions(room);
            return;
        } else if (input == "2") {
            return;
        } else {
            cout << "What do you do?" <<endl;
        }
    }
}

void Dungeon::handleRoomEmpty(Room * room) {
    cout << "You've already been here and it's oddly difficult to care about anything you see. You should move on." <<endl<<endl;
    string actions[] = {"1. Move forward."};
    while(true) {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "1") {
            return;
        } else {
            cout << "What do you do?" <<endl;
        }
    }
}

void Dungeon::enterRoom(Room * room) {
    if (room->enemies.size() != 0) {
        handleRoomEnemy(room);
    } else if (room->items.size() != 0) {
        handleRoomLoot(room);
    } else {
        handleRoomEmpty(room);
    }
}

void Dungeon::handleMovementActions(Room * room) {
    while (true) {
        if (room->position ==0) {
            string actions[] = {"1. Move east.", "2. Move down."};
            printActions(2, actions);
            string input;
            cin >> input;
            if (input == "1") {
                player.changeRoom(&rooms[1]);
                return;   
            } else if (input == "2") {
                player.changeRoom(&rooms[2]);
                return;
            } else {
                cout << "You can't go that way." <<endl<<endl;
            }
        } else if (room->position == 1) {
            string actions[] = {"1. Move west."};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "1") {
                player.changeRoom(&rooms[0]);
                return;   
            } else {
                cout << "You can't go that way." <<endl<<endl;
            }
        } else if (room->position == 2) {
            string actions[] = {"1. Move north.", "2. Move east."};
            printActions(2, actions);
            string input;
            cin >> input;
            if (input == "1") {
                player.changeRoom(&rooms[0]);
                return;   
            } else if (input == "2") {
                player.changeRoom(&rooms[3]);
                return;
            } else {
                cout << "You can't go that way." <<endl<<endl;
            }
        } else {
            string actions[] = {"1. Move west."};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "1") {
                player.changeRoom(&rooms[2]);
                return;   
            } else {
                cout << "You can't go that way." <<endl<<endl;
            }
        }
    }
}

int Dungeon::performEndGame() {
    string actions[] = {"1. Wake up.", "2. Succumb."};
    while(true) {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "1") {
            return 1;
        } else if (input == "2") {
            return 0;
        } else {
            cout << "Would you like to wake up?" <<endl<<endl;
        }
    }
}

int Dungeon::runDungeon() {
    milliseconds micro(500);
    milliseconds small(1000);
    milliseconds medium(1500);
    milliseconds large(2000);

    cout << "You're awake - you think." <<endl <<endl;
    sleep_for(medium);
    cout << "Your back aches as you sit up from sleeping on the cheap mattress beneath you, but your attention is drawn to a different sort of discomfort. Something harder to define, but impossible to brush off." <<endl;
    sleep_for(small);
    cout << "You've had false awakenings before - where it feels like you conscious again, but there are bits and pieces of the world around you that just aren't as they should be." <<endl;
    sleep_for(small);
    cout << "Maybe the room is missing a few things, or you can't hear the familiar ambient noise you're accustomed to, or the color of your familiar space is just a little";
    sleep_for(micro);
    cout << ".";
    sleep_for(micro);
    cout << ".";
    sleep_for(micro);
    cout << ".";
    sleep_for(micro);
    cout << " off." <<endl;
    sleep_for(small);
    cout << "Something is definitely off, and there's a sick feeling in your gut that blinking a few times isn't going to put an end to this illusion, if that's what it is." <<endl<<endl;
    sleep_for(medium);
    cout << "Not content with sitting in bed in such a dull, uncertain state of consciousness, you kick the blanket off of you and stand up." <<endl;
    sleep_for(small);
    cout << "Whatever weirdness is going on, interacting with your environment always seems to be the best course of action to come to your senses." <<endl<<endl;
    sleep_for(small);
    cout << "What do you do?";

    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];

    while(true) {
        enterRoom(player.currentRoom);
        if (player.checkDead()) {
            cout << "Life pours from you, but it almost feels like waking up from a dream. Would you like to wake up?" <<endl<<endl;
            return performEndGame();
        } else {
            if (player.currentRoom->isExit) {
                if (player.currentRoom->enemies.size() == 0) {
                    cout << "The halls lay silent, but a familiar din emanates from the doorway before you. Would you like to wake up?" <<endl<<endl;
                    return performEndGame();
                }
            }
        }
        handleMovementActions(player.currentRoom);
    }
}