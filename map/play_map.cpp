#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include "../headers/Constant.h"
#include "../headers/Helper.h"
#include "../headers/Map.h"
#include "../headers/Player.h"

using namespace std;

void getCommand(Map &map, pair<int, int> &player_position)
{
    auto &[x, y] = player_position;
    auto &rooms = map.getMap();
    string command;
    cout << "你想往哪里走呢：";
    bool error = false;
    do {
        cin >> command;
        if (command == UP) {
            if (y + 1 <= MAP_MAX_SIZE && rooms[x][y + 1].canPass()) {
                ++y;
                error = false;
            }
            else {
                cout << "前方是墙壁，你无法通过。" << endl
                    << "重新选一条路吧：";
                error = true;
            }
        }
        else if (command == DOWN) {
            if (y - 1 >= 1 && rooms[x][y - 1].canPass()) {
                --y;
                error = false;
            }
            else {
                cout << "前方是墙壁，你无法通过。" << endl
                    << "重新选一条路吧：";
                error = true;
            }
        }
        else if (command == LEFT) {
            if (x - 1 >= 1 && rooms[x - 1][y].canPass()) {
                --x;
                error = false;
            }
            else {
                cout << "前方是墙壁，你无法通过。" << endl
                    << "重新选一条路吧：";
                error = true;
            }
        }
        else if (command == RIGHT) {
            if (x + 1 <= MAP_MAX_SIZE && rooms[x + 1][y].canPass()) {
                ++x;
                error = false;
            }
            else {
                cout << "前方是墙壁，你无法通过。" << endl
                    << "重新选一条路吧：";
                error = true;
            }
        }
        else {
            cout << "这不是一个有效指令，你想往哪里走呢：";
            error = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (error);
}

void processPlayerLocation(Map &map, Player &player)
{
    // 定义玩家的位置
    pair<int, int> player_location = make_pair(0, 0);
    auto &[x, y] = player_location;

    // 玩家进入地图到城门的位置
    auto &rooms = map.getMap();
    for (int i = 1; i <= MAP_MAX_SIZE + 1; ++i) {
        for (int j = 1; j <= MAP_MAX_SIZE + 1; ++j) {
            if (rooms[i][j].getName() == Place("城门")) {
                player_location = make_pair(i, j);
            }
        }
    }

    getCommand(map, player_location);
    cout << rooms[x][y].getDescription() << endl;
    if (rooms[x][y].getContent() == EMPTY_CONTENT) {}
    else if (rooms[x][y].getContent() == ENEMY) {}
    else if (rooms[x][y].getContent() == ELITE) {}
    else if (rooms[x][y].getContent() == BOSS) {}
}