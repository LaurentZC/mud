#include "PlayMap.h"

#include <CreatMap.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include "Area.h"
#include "Enemy.h"
#include "Fight.h"
#include "Helper.h"
#include "Player.h"
#include "fmt/color.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

using namespace std;

extern Player Gamer;

bool isValidMove(int x, int y, Area &map, char dir);

void changeMap(Area &map)
{
    auto &[c, x, y] = Gamer.position;
    string input;
    print(fg(fmt::color::green), "马夫：公子要去那个地方？。\n");
    fmt::print("1. 武威城 \t 2. 天下商会 \t q. 暂不出行");
    while (true) {
        cin >> input;
        if (input.length() != 1) {
            fmt::print("无效的输入[1 / 2 / q]: ");
            continue;
        }
        printSlowly(format(fg(fmt::color::green), "马夫：公子且上车坐好吧。\n"));
        switch (input[0]) {
            case '1' :
                if (Gamer.getLevel() < 30) {
                    printSlowly(format(fg(fmt::color::green), "马夫：公子你的实力还不足以前往哪里。\n"));
                    return;
                }
                if (Gamer.finished[0]) {
                    printSlowly("你：师傅，你知道现如今武威城的状况吗？\n");
                    printSlowly(format(fg(fmt::color::green), "马夫：现如今啊，哪里一片祥和，百姓安居乐业。\n"));
                    printSlowly("你：是吗，那太好了。\n");
                    printSlowly(format(fg(fmt::color::green), "马夫：哈哈哈，这都归功于公子啊。\n"));
                    return;
                }
                map = creatWuWeiCheng();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
                printSlowly(format(fg(fmt::color::green), "马夫：这便是武威楼了，那陆洪实力高强，公子一定要小心啊。\n"));
                printSlowly(format(fg(fmt::color::green), "马夫：我这里有一份这楼里的地图，公子且收好，莫要丢了。\n"));
                printSlowly("你：多谢了。\n");
                printMap(map.getArea());
                return;

            case '2' :
                if (Gamer.getLevel() < 40) {
                    printSlowly(format(fg(fmt::color::green), "马夫：公子你的实力还不足以前往哪里。\n"));
                    return;
                }
                if (Gamer.finished[1]) {
                    printSlowly("你：师傅，你知道现如今天下商会的状况吗？\n");
                    printSlowly(format(fg(fmt::color::green), "马夫：哦，知道知道。这商会啊，事业是蒸蒸日上啊哈哈。\n"));
                    printSlowly("你：是吗，那太好了。\n");
                    printSlowly(format(fg(fmt::color::green), "马夫：公子有空可一定要去瞧瞧。\n"));
                    printSlowly("你：一定。\n");
                    return;
                }
                map = creatShangHui();
                x = Gates[map.getName()].first;
                y = Gates[map.getName()].second;
                waitForLoad(100);
                printSlowly(format(fg(fmt::color::green), "马夫：这便是天下商会了，那段霖擅长偷袭，公子莫要落入他的陷阱。\n"));
                printSlowly(format(fg(fmt::color::green), "马夫：这商会向来隐私，没人透露过他的真实样貌。\n"));
                printSlowly(format(fg(fmt::color::green), "马夫：这次便只能靠公子自己摸索了。\n"));
                printSlowly("你：放心吧。\n");
                return;

            case 'q' :
                print(fg(fmt::color::green), "马夫：若公子有出行必要，尽管来找我便是。\n");
                return;

            default :
                fmt::print("无效的输入[1 / 2 / q]: ");
        }
    }
}

void playWuWeiCheng(Area &map)
{
    const auto &[c, x, y] = Gamer.position;
    auto &rooms = map.getArea();
    fmt::print("{}\n", rooms[x][y].getDescription());
    fmt::print("你想做些什么呢。");
    fmt::print("\n移动:  move \t 打开背包: bag \t 离开: exit \t 保存: save \t 查看地图: map\n");
    string command;
    bool quit = false;
    while (!quit) {
        cin >> command;
        if (command == "move") {
            movePlayerLocation(map);
            switch (rooms[x][y].getContent()) {
                case Room::Content::GATE :
                    fmt::print("你：那陆洪果然有两下子。我先暂且回去休整一下");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "马夫：老夫这就带公子离开。");
                    quit = true;
                    break;

                case Room::Content::MONSTER : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    print(fg(fmt::color::yellow), "陆洪的手下: 小子，竟敢擅闯我们的地盘，拿命来！");
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatEnemy(Gamer.position)).fight();
                    rooms[x][y].clear();
                    break;
                }

                case Room::Content::ELITE : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatElite(Gamer.position)).fight();
                    rooms[x][y].clear();
                    break;
                }

                case Room::Content::BOSS : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatElite(Gamer.position)).fight([](Player &gamer, Enemy &enemy) {
                        enemy.decHp(-200);
                        if (enemy.getHp() < enemy.getMaxHp() * 0.5) {
                            enemy.setDamage(enemy.getDamage() + 10);
                        }
                    });
                    rooms[x][y].clear();
                    Gamer.finished[0] = true;
                    fmt::print("你：我已经击败了那陆洪，我们待会儿可以回去了。");
                    waitForAnyKey();
                    print(fg(fmt::color::green), "马夫：公子武功盖世！");
                    waitForAnyKey();
                    break;
                }

                case Room::Content::EMPTY : {
                    fmt::print("你想做些什么呢。");
                    fmt::print("\n移动:  move \t 打开背包: bag \t 离开: exit \t 保存: save \n");
                    break;
                }

                case Room::Content::CHEST : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    if (x == 1 && y == 3) {
                        fmt::print("这里有一颗丹药，你服用之后获得了三个属性点。");
                        Gamer.addPoints(3);
                    }
                    else {
                        fmt::print("这里是陆洪的装备仓库，这里有一套看着很不错的装备。");
                        Gamer.gainWeapon(7);
                        Gamer.gainArmor(11);
                        fmt::print("恭喜你获得了九环大刀和幽冥披风，请及时查看背包。");
                    }
                    rooms[x][y].clear();
                    break;
                }

                case Room::Content::NPC : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    printSlowly("你：你们是被那陆洪囚禁的人吗？（边说边打开笼子）\n");
                    printSlowly(format(fg(fmt::color::green), "囚犯：是的公子快救救我们把。\n"));
                    fmt::print("叮！笼子被你一剑斩开了。\n");
                    printSlowly("你：快点回家把。\n");
                    printSlowly(format(fg(fmt::color::green), "囚犯：多谢公子。\n"));
                    quit = true;
                    break;
                }
                default : ;
            }
        }
        else if (command == "bag") {
            Gamer.openBag();
        }
        else if (command == "exit") {
            handleQuit(map, quit);
            return;
        }
        else if (command == "map") {
            printMap(map.getArea());
        }
        else {
            fmt::print("无效的指令！\n");
        }
    }
}

void playShangHui(Area &map)
{
    auto &[c, x, y] = Gamer.position;
    auto &rooms = map.getArea();
    fmt::print("{}\n", rooms[x][y].getDescription());
    fmt::print("你想做些什么呢。");
    fmt::print("\n移动:  move \t 打开背包: bag \t 离开: exit \t 保存: save \n");
    string command;
    bool quit = false;
    bool mask = false;
    while (!quit) {
        cin >> command;
        if (command == "move") {
            movePlayerLocation(map);
            switch (rooms[x][y].getContent()) {
                case Room::Content::GATE : {
                    printSlowly("你：没有找到段霖的藏身之处，暂且回去把。");
                    printSlowly(format(fg(fmt::color::green), "马夫：老夫这就带公子离开。"), 10);
                    quit = true;
                    break;
                }

                case Room::Content::MONSTER : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    printSlowly(format(fg(fmt::color::yellow), "段霖的手下: 小子，来天下商会闹事，你怕是不想活了！"), 10);
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatEnemy(Gamer.position)).fight();
                    rooms[x][y].clear();
                    break;
                }

                case Room::Content::ELITE : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    Fight(Enemy::creatElite(Gamer.position)).fight();
                    rooms[x][y].clear();
                    break;
                }

                case Room::Content::BOSS : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    fmt::print("正在加载战斗场景，请稍后...");
                    waitForLoad(1000);
                    if (!mask) {
                        fmt::print("段霖在这里释放了强大的毒气，你无法抵抗。");
                        this_thread::sleep_for(chrono::seconds(5));
                        restart();
                    }
                    fmt::print("你：这里的毒气好强大，防毒面具抵挡效果也十分有限。");
                    Fight(Enemy::creatElite(Gamer.position)).fight([](Player &gamer, Enemy &enemy) {
                        gamer.setHp(static_cast<int>(gamer.getHp() * 0.3));
                    });
                    rooms[x][y].clear();
                    Gamer.finished[1] = true;
                    printSlowly("你：这段霖也不过如此。");
                    printSlowly(format(fg(fmt::color::green), "马夫：公子威武，天下无双！"));
                    break;
                }

                case Room::Content::CHEST : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    // 两个箱子获得点什么
                    if (x == 1 && y == 5) {
                        fmt::print("这里有一颗丹药，你服用之后获得了五个属性点。");
                        Gamer.addPoints(5);
                    }
                    else {
                        fmt::print("这里是陆洪的装备仓库，这里有一套看着很不错的装备。");
                        Gamer.gainWeapon(9);
                        Gamer.gainArmor(13);
                        fmt::print("恭喜你获得了霸王枪和七彩羽衣，请及时查看背包。");
                    }
                    rooms[x][y].clear();
                    break;
                }

                case Room::Content::NPC : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    printSlowly(format(fg(fmt::color::green), "老翁：公子，这商会里面毒气无数，我这里恰好有一个防毒面具。\n"));
                    printSlowly(format(fg(fmt::color::green), "老翁：只要800大洋，保证你买不了吃亏买不了上当。\n"));
                    fmt::print("是否购买？[y / n]: ");
                    string choice;
                    while (true) {
                        cin >> choice;
                        if (choice == "y" || choice == "Y") {
                            if (Gamer.getMoney() >= 800)
                                Gamer.gainMoney(-800);
                            else {
                                fmt::print("你还没有这么多钱。");
                            }
                            printSlowly("你：这是800大洋，面具我就收下了。");
                            printSlowly(format(fg(fmt::color::green), "老翁：唉，公子你且收好。\n"));
                            mask = true;
                            break;
                        }
                        if (choice == "n" || choice == "N") {
                            printSlowly("你：暂且不需要。");
                            printSlowly(format(fg(fmt::color::green), "老翁：那就祝公子一路顺风了。\n"));
                            break;
                        }
                        fmt::print("无效的指令。请重新输入[y / n]: ");
                    }
                    break;
                }

                case Room::Content::TRAP : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    Gamer.setHp(static_cast<int>(Gamer.getHp() * 0.5));
                    break;
                }

                case Room::Content::POISON : {
                    fmt::print("{}\n", rooms[x][y].getDescription());
                    if (mask) {
                        fmt::print("你：这毒气果然厉害，还好提前买了面具");
                        waitForAnyKey();
                    }
                    else {
                        Gamer.setHp(10);
                        print(fg(fmt::color::red), "血量: {} / {}\n", Gamer.getHp(), Gamer.getMaxHp());
                        fmt::print("你：糟糕，没想到这毒气这么厉害。");
                    }
                }
                default : ;
            }
        }
        else if (command == "bag") {
            Gamer.openBag();
        }
        else if (command == "exit") {
            handleQuit(map, quit);
            return;
        }
        else {
            fmt::print("无效的指令！\n");
        }
    }
}

void movePlayerLocation(Area &map)
{
    auto &[c, x, y] = Gamer.position;
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

void handleQuit(Area &current_map, bool &quit)
{
    auto &[c, x, y] = Gamer.position;
    string input;
    while (true) {
        cin >> input;
        if (input == "y" || input == "Y") {
            quit = true;
            current_map = creatMainCity();
            c = 0;
            x = Gates[current_map.getName()].first;
            y = Gates[current_map.getName()].second;
            break;
        }
        if (input == "n" || input == "N") {
            quit = false;
            break;
        }
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
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (i == Gamer.position[1] && j == Gamer.position[2])
                grid[i][j].setName(fmt::format("[{}*]", grid[i][j].getName()));
            else
                grid[i][j].setName(fmt::format("[{}]", grid[i][j].getName()));
            max_width = std::max(max_width, grid[i][j].getName().length());
        }
    }

    // 补充对齐
    for (auto &row : grid) {
        for (auto &cell : row) {
            string fill(max_width - cell.getName().length(), ' ');
            cell.setName(cell.getName().append(fill));
        }
    }

    max_width += max_width & 1 ? 1 : 0;

    fmt::print("\n\n");
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
