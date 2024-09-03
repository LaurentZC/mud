#include "PlayMap.h"

#include <CreatMap.h>
#include <iostream>
#include <memory>
#include <string>

#include "Area.h"
#include "Helper.h"
#include "fmt/color.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

using namespace std;
extern Area MainCity;

bool isValidMove(int x, int y, Area &map, char dir);

void handlePlayerAction(Area &map, int x, int y);

void changeMap(Area &map, int &x, int &y)
{
    string input;
    while (true) {
        cin >> input;
        if (input.length() != 1) {
            fmt::print("无效的输入[1 / 2 / 3 / 4 / 5 / q]: ");
            continue;
        }
        switch (input[0]) {
            case '1' :
                map = creatWuWeiCheng();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
            // npc.talk();
                printMap(map.getArea());
                return;
            case '2' :
                map = creatShangHui();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
            // npc.talk();
                printMap(map.getArea());
                return;
            case '3' :
                map = creatWuWeiCheng();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
            // npc.talk();
                printMap(map.getArea());
                return;
            case '4' :
                map = creatWuWeiCheng();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
            // npc.talk();
                printMap(map.getArea());
                return;
            case '5' :
                map = creatWuWeiCheng();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
            // npc.talk();
                printMap(map.getArea());
                return;
            case 'q' :
                return;
            default :
                fmt::print("无效的输入[1 / 2 / 3 / 4 / 5 / q]: ");
        }
    }
}

void movePlayerLocation(Area &map, int &x, int &y)
{
    string command;
    fmt::print("你想往哪里走呢？[w / a / s / d] (q for quit)：");
    while (true) {
        cin >> command;
        if (command.length() != 1 || strchr("wasdq", command[0]) == nullptr) {
            fmt::print("无效的指令！[w / a / s / d / q]：");
            continue;
        }
        if (isValidMove(x, y, map, command[0])) {
            switch (command[0]) {
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
                case 'q' :
                    return;
                default : ;
            }
            break;
        }
        fmt::print("前方是一堵墙，你无法通过。\n请换一个方向吧 [w / a / s / d / q]：");
    }
    handlePlayerAction(map, x, y);
}

void handleQuit(Area &current_map, bool &quit, int &x, int &y)
{
    string input;
    // @formatter:off
    fmt::print(current_map.getName() == area("main_city") ?
                                            "你现在处于主城，退出将结束游戏，你确定吗？[y/n]: " :
                                            "你确定要退出当前地图吗？[y/n]: ");
    // @ formatter:on
    while (true) {
        cin >> input;
        if (input == "y" || input == "Y") {
            if (current_map.getName() == "main_city") {
                fmt::print("感谢你的游玩！\n");
                quit = false;
            }
            else {
                current_map = MainCity;
                x = Gates["main_city"].first;
                y = Gates["main_city"].second;
            }
            break;
        }
        if (input == "n" || input == "N")
            break;
        fmt::print("无效输入！请输入[y / n]。\n");
    }
}

bool isValidMove(const int x, const int y, Area &map, const char dir)
{
    const auto &rooms = map.getArea();
    switch (dir) {
        case 'w' :
            return y + 1 <= MAP_MAX_SIZE && rooms[x][y + 1].canPass();
        case 's' :
            return y - 1 >= 1 && rooms[x][y - 1].canPass();
        case 'a' :
            return x - 1 >= 1 && rooms[x - 1][y].canPass();
        case 'r' :
            return x + 1 <= MAP_MAX_SIZE && rooms[x + 1][y].canPass();
        case 'q' :
            return true;
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
        case Room::Content::EMPTY :
            fmt::print("{}", map.getArea()[x][y].getDescription());
        break;

        case Room::Content::CHEST :
            fmt::print("你要打开它吗？[y / n]");
        if (get_yes_or_no()) {
            // 打开宝箱的处理逻辑
        }
        break;

        case Room::Content::NPC :
            fmt::print("你要和他对话吗？[y / n]");
        if (get_yes_or_no()) {
            // 和NPC对话的处理逻辑
        }
        break;

        default : // 小怪，精英怪，boss
            fmt::print("你是要发动攻击(y)还是先打开背包休整一下(n)：");
        if (!get_yes_or_no()) {
            // player.openBag();
            break;
        }
        // 战斗的处理逻辑
        break;
    }
}

void printMap(std::vector<std::vector<Room> > grid)
{
    size_t max_width = 0;
    // 计算字符串的最大宽度
    for (auto &row : grid) {
        for (auto &cell : row) {
            cell.setName(fmt::format("[{}]", cell.getName()));
            max_width = std::max(max_width, cell.getName().length());
        }
    }

    // 补充对齐
    for (auto &row : grid) {
        for (auto &cell : row) {
            string fill(max_width - cell.getName().length(), ' ');
            cell.getName().append(fill);
        }
    }

    max_width += max_width & 1 ? 1 : 0;

    fmt::print("\n");
    for (const auto &row : grid) {
        string check;
        for (auto &cell : row) {
            check += cell.getName();
        }
        if (check.find_first_not_of(" \n[]") != string::npos) {
            for (const auto &cell : row) {
                if (format("{}", fmt::join(cell.getName(), "")).find_first_not_of(" \n[]") != string::npos)
                    print(fg(fmt::color::blue), "{:<{}}{}{:<{}}", "", max_width >> 1, cell.getName(), "", max_width >> 1);
                else
                    print(fg(fmt::color::blue), "{}", "", max_width);
            }
            fmt::print("\n");
        }
    }
    fmt::print("\n");
}
