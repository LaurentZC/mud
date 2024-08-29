#include "PlayMap.h"

#include <iostream>
#include <memory>
#include <string>

#include "Area.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

bool isValidMove(const int x, const int y, Area &map, const char dir)
{
    const auto &rooms = map.getArea();
    switch (dir) {
        case 'w':
            return y + 1 <= MAP_MAX_SIZE && rooms[x][y + 1].canPass();
        case 's':
            return y - 1 >= 1 && rooms[x][y - 1].canPass();
        case 'a':
            return x - 1 >= 1 && rooms[x - 1][y].canPass();
        case 'r':
            return x + 1 <= MAP_MAX_SIZE && rooms[x + 1][y].canPass();
        default:
            return false;
    }
}

void handlePlayerAction(Area &map, const int x, const int y)
{
    auto get_yes_or_no = []() -> bool {
        while (true) {
            string input;
            cin >> input;
            if (input == "y" || input == "Y")
                return true;
            if (input == "n" || input == "N")
                return false;
            cout << "无效指令！[y / n]：";
        }
    };

    switch (const auto &rooms = map.getArea(); rooms[x][y].getContent()) {
        case Room::Content::EMPTY:
            fmt::print("{}", map.getArea()[x][y].getDescription());
            break;

        case Room::Content::CHEST:
            fmt::print("你要打开它吗？[y / n]");
            if (get_yes_or_no()) {
                // 打开宝箱的处理逻辑
            }
            break;

        case Room::Content::NPC:
            fmt::print("你要和他对话吗？[y / n]");
            if (get_yes_or_no()) {
                // 和NPC对话的处理逻辑
            }
            break;

        default: // 小怪，精英怪，boss
            fmt::print("你是要发动攻击(y)还是先打开背包休整一下(n)：");
            if (!get_yes_or_no()) {
                // player.openBag();
                break;
            }
        // 战斗的处理逻辑
            break;
    }
}

void movePlayerLocation(Area &map, int &x, int &y)
{
    string command;
    while (true) {
        fmt::print("你想往哪里走呢？[w / a / s / d]：");
        cin >> command;
        if (command.length() != 1 || strchr("wasd", command[0]) == nullptr) {
            fmt::print("无效的指令！[w / a / s / d]：");
            continue;
        }
        if (isValidMove(x, y, map, command[0])) {
            switch (command[0]) {
                case 'w':
                    ++y;
                    break;
                case 's':
                    --y;
                    break;
                case 'a':
                    --x;
                    break;
                case 'd':
                    ++x;
                    break;
                default:
                    break;
            }
            break;
        }
        fmt::print("前方是一堵墙，你无法通过。\n请换一个方向吧 [w / a / s / d]：");
    }
    handlePlayerAction(map, x, y);
}
