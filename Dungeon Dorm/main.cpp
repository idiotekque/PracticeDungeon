#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "dungeon.cpp"
#include "player.cpp"
#include "gameChar.cpp"
#include "item.cpp"
#include "room.cpp"

using namespace std;
using namespace chrono;
using namespace this_thread;

int main(void)
{
    milliseconds dura( 1000 );

    // set up player
    cout << "It feels like you've been sleeping for a long time, but something is lulling you back to consciousness. Who are you?" <<endl<<endl;
    string playerName;
    cin >> playerName;
    Player player = Player(playerName, 100, 20, 10);

    // set up first room
    Room firstRoom = Room(0, false, vector<Item>(), vector<gameChar>());
    
    // set up second room
    Item sword = Item("Sword", 0, 10, 0);
    vector<Item> secondRoomItems;
    secondRoomItems.push_back(sword);
    Room secondRoom = Room(1, false, secondRoomItems, vector<gameChar> ());

     // set up the third room
     gameChar firstEnemy = gameChar("Little Monster", 50, 15, 5);
     vector<gameChar> thirdRoomEnemies;
     thirdRoomEnemies.push_back(firstEnemy);
     Room thirdRoom = Room(2, false, vector<Item>(), thirdRoomEnemies);

     // set up fourth room
     gameChar secondEnemy = gameChar("Big Monster", 100, 20, 10);
     vector<gameChar> fourthRoomEnemies;
     fourthRoomEnemies.push_back(secondEnemy);
     Room fourthRoom = Room(3, true, vector<Item>(), fourthRoomEnemies);

    Dungeon dungeon = Dungeon(player);
    dungeon.rooms[0] = firstRoom;
    dungeon.rooms[0] = secondRoom;
    dungeon.rooms[0] = thirdRoom;
    dungeon.rooms[0] = fourthRoom;

    while(true) {
        int result = dungeon.runDungeon();
        if (result == 0) {
            break;
        }
    }
    cout << "Goodbye.";
}