#include "PlayMap.h"

#include <CreatMap.h>
#include <filesystem>
#include <iostream>
#include <string>

#include "Area.h"
#include "Enemy.h"
#include "Fight.h"
#include "Helper.h"
#include "Player.h"
#include "fmt/color.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

using namespace std;

extern Player Player;
extern Area MainCity;

bool isValidMove(int x, int y, Area &map, char dir);

void changeMap(Area &map, int &x, int &y)
{
    string input;
    print(fg(fmt::color::green), "马夫：公子要去那个地方？。\n");
    fmt::print("1. 武威城 \t 2. 天下商会 \t q. 暂不出行");
    while (true) {
        cin >> input;
        if (input.length() != 1) {
            fmt::print("无效的输入[1 / 2 / q]: ");
            continue;
        }
        print(fg(fmt::color::green), "马夫：公子且上车坐好吧。\n");
        switch (input[0]) {
            case '1' :
                if (Player.getLevel() < 30) {
                    print(fg(fmt::color::green), "马夫：公子你的实力还不足以前往哪里。\n");
                    return;
                }
                if (const filesystem::path file_path = "../../files/" + Player.getName() + "/maps/WuWeiCheng.txt"; !exists(file_path)) {
                    fmt::print("你：师傅，你知道现如今武威城的状况吗？\n");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "马夫：现如今啊，哪里一片祥和，百姓安居乐业。\n");
                    waitForAnyKey();
                    fmt::print("你：是吗，那太好了。\n");
                    print(fg(fmt::color::green), "马夫：哈哈哈，这都归功于公子啊。\n");
                    waitForAnyKey();
                    return;
                }
                map = creatWuWeiCheng();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
                print(fg(fmt::color::green), "马夫：这便是武威楼了，那陆洪实力高强，公子一定要小心啊。\n");
                waitForAnyKey();
                print(fg(fmt::color::green), "马夫：我这里有一份这楼里的地图，公子且收好，莫要丢了。\n");
                waitForAnyKey();
                fmt::print("你：多谢了。\n");
                printMap(map.getArea());
                return;
            case '2' :
                if (Player.getLevel() < 40) {
                    print(fg(fmt::color::green), "马夫：公子你的实力还不足以前往哪里。\n");
                    return;
                }
                if (const filesystem::path file_path = "../../files/" + Player.getName() + "/maps/ShangHui.txt"; !exists(file_path)) {
                    fmt::print("你：师傅，你知道现如今天下商会的状况吗？\n");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "马夫：哦，知道知道。这商会啊，事业是蒸蒸日上啊哈哈。\n");
                    waitForAnyKey();
                    fmt::print("你：是吗，那太好了。\n");
                    print(fg(fmt::color::green), "马夫：公子有空可一定要去瞧瞧。\n");
                    waitForAnyKey();
                    fmt::print("你：一定。\n");
                    waitForAnyKey();
                    return;
                }
                map = creatShangHui();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
                print(fg(fmt::color::green), "马夫：这便是天下商会了，那段霖擅长偷袭，公子莫要落入他的陷阱。\n");
                waitForAnyKey();
                print(fg(fmt::color::green), "马夫：这商会向来隐私，没人透露过他的真实样貌。\n");
                waitForAnyKey();
                print(fg(fmt::color::green), "马夫：这次便只能靠公子自己摸索了。\n");
                waitForAnyKey();
                fmt::print("你：放心吧。\n");
                return;
            case 'q' :
                print(fg(fmt::color::green), "马夫：若公子有出行必要，尽管来找我便是。\n");
                return;
            default :
                fmt::print("无效的输入[1 / 2 / q]: ");
        }
    }
}

void playWuWeiCheng(Area &map, int &x, int &y)
{
    auto &rooms = map.getArea();
    fmt::print("{}\n", rooms[x][y].getDescription());
    fmt::print("你想做些什么呢。");
    fmt::print("\n移动:  move \t 打开背包: bag \t 离开: exit \t 保存: save \n");
    string command;
    bool quit = false;
    while (!quit) {
        cin >> command;
        if (command == "move") {
            movePlayerLocation(map, x, y);
            switch (rooms[x][y].getContent()) {
                case Room::Content::GATE :
                    fmt::print("你：那陆洪果然有两下子。我先暂且回去休整一下");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "马夫：老夫这就带公子离开。");
                    quit = true;
                    break;
                case Room::Content::MONSTER :
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    print(fg(fmt::color::yellow), "陆洪的手下: 小子，竟敢擅闯我们的地盘，拿命来！");
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatEnemy(1)).fight();
                    rooms[x][y].clear();
                    break;
                case Room::Content::ELITE :
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatElite(1)).fight();
                    rooms[x][y].clear();
                    break;
                case Room::Content::BOSS :
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatElite(1)).fight();
                    rooms[x][y].clear();
                    const filesystem::path file_path = "../../files/" + Player.getName() + "/maps/WuWeiCheng.txt";
                    filesystem::remove(file_path);
                    fmt::print("你：我已经击败了那陆洪，我们可以回去了。");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "马夫：公子武功盖世！");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "马夫：以后百姓就不会被折磨了！");
                    waitForAnyKey();
                    break;
                case Room::Content::EMPTY :
                    fmt::print("你想做些什么呢。");
                    fmt::print("\n移动:  move \t 打开背包: bag \t 离开: exit \t 保存: save \n");
                    cin >> command;
                case Room::Content::CHEST :
                    fmt::print("{}\n", rooms[x][y].getDescription());
                // 获得点什么
                    rooms[x][y].clear();
                case Room::Content::NPC :
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    fmt::print("你：你们是被那陆洪囚禁的人吗？（边说边打开笼子）\n");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "囚犯：是的公子快救救我们把。\n");
                    waitForAnyKey();
                    fmt::print("叮！笼子被你一剑斩开了。\n");
                    fmt::print("你：快点回家把。\n");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "囚犯：多谢公子。\n");
                    waitForAnyKey();
                    return;
                default : ;
            }
        }
        else if (command == "bag") {
            Player.openBag();
        }
        else if (command == "quit") {
            handleQuit(map, quit, x, y);
            return;
        }
        else {
            fmt::print("无效的指令！\n");
        }
    }
}

void movePlayerLocation(Area &map, int &x, int &y)
{
    string command;
    fmt::print("你想往哪里走呢？[w / a / s / d] (q for quit): ");
    while (true) {
        cin >> command;
        if (command.length() != 1 || strchr("wasdq", command[0]) == nullptr) {
            fmt::print("无效的指令！[w / a / s / d / q]: ");
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
        fmt::print("前方是一堵墙，你无法通过。\n请换一个方向吧 [w / a / s / d / q]: ");
    }
}

void handleQuit(Area &current_map, bool &quit, int &x, int &y)
{
    string input;
    while (true) {
        cin >> input;
        if (input == "y" || input == "Y") {
            current_map = creatMainCity();
            x = Gates[current_map.getName()].first;
            y = Gates[current_map.getName()].second;
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
        default :
            return false;
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
