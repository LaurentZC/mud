#include "../headers/PlayMap.h"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "../headers/Area.h"
#include "../headers/Constant.h"
#include "../headers/Helper.h"
#include "../headers/Player.h"

using namespace std;

pair<int, int> enterNewMap(Area &map)
{
    // 玩家的位置
    pair<int, int> player_location = make_pair(0, 0);

    // 查找城门，即玩家刚到达的地方
    const auto &rooms = map.getArea();
    bool found = false;
    for (int i = 1; i <= MAP_MAX_SIZE; ++i) {
        for (int j = 1; j <= MAP_MAX_SIZE; ++j) {
            if (rooms[i][j].getName() == place("城门")) {
                player_location = make_pair(i, j);
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    return player_location;
}

bool isValidMove(const int x, const int y, const vector<vector<Room> > &rooms, const char dir)
{
    switch (dir) {
        case 'w' :
            return y + 1 <= MAP_MAX_SIZE && rooms[x][y + 1].canPass();
        case 's' :
            return y - 1 >= 1 && rooms[x][y - 1].canPass();
        case 'a' :
            return x - 1 >= 1 && rooms[x - 1][y].canPass();
        case 'r' :
            return x + 1 <= MAP_MAX_SIZE && rooms[x + 1][y].canPass();
        default :
            return false;
    }
}

void applyMove(int &x, int &y, const char dir)
{
    switch (dir) {
        case 'w' :
            ++y;
            break;
        case 's' :
            --y;
            break;
        case 'a' :
            --x;
            break;
        case 'd' :
            ++x;
            break;
        default :
            break;
    }
}

void movePlayerLocation(Area &map, int &x, int &y)
{
    const auto &rooms = map.getArea();

    string command;
    while (true) {
        cout << "你想往哪里走呢（w/a/s/d）：";
        cin >> command;
        // 指令字符比一个多
        if (command.length() > 1) {
            cout << "无效的指令，请输入 'w', 'a', 's', 'd' 之一：" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (isValidMove(x, y, rooms, command[0])) {
            // 成功移动就可以退出循环
            applyMove(x, y, command[0]);
            cout << rooms[x][y].getDescription() << endl;
            break;
        }
        // 移动不成功
        cout << "前方是一堵墙，你无法通过。请换一个方向：" << endl;
    }

    switch (rooms[x][y].getContent()) {
        case Content::EMPTY :
            break;

        case Content::CHEST :
            cout << "你要打开他吗（y/n）？";
            if (getYorN()) {
                // 打开宝箱
            }
            break;

        case Content::NPC :
            cout << "你要和他对话吗？（y/n）";
            if (getYorN()) {
                // 和npc对话
            }
            break;

        default : // 小怪，精英怪，boss
            cout << "你是要发动攻击（y）还是先打开背包休整一下（n）：";
            if (!getYorN()) {
                // player.openBag();
                break;
            }

        // 战斗
            break;
    }
}
