#include <Fight.h>
#include <NPC.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>

#include "Area.h"
#include "CreatMap.h"
#include "Helper.h"
#include "PlayMap.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

Player Gamer;

void creat()
{
    namespace fs = filesystem;
    fmt::print("欢迎来到剑影江湖。");
    fmt::print("请告诉我你的名字: ");
    string name;
    cin >> name;
    Gamer.setName(name);
    Gamer.save();
    system("cls");
    printSlowly("江湖，风起云涌，无数人浪迹天涯，闯荡江湖，只为追求那心中的侠客梦。\n");
    printSlowly("殊不知，在整个江湖的背后，一直有一双大手在默默操控一切，他隐藏在江湖的阴暗面，是彻头彻尾的吸血鬼。\n");
    printSlowly("他试图颠覆武林的秩序，夺取武林之主的宝座，以实现他对整个武林的绝对统治。\n");
    printSlowly("武林中像来不缺少正义之士，而你，" + name + "，正意气风发，即将踏入江湖，势必要维护武林的安定。\n");
    printSlowly("故事从此刻开始...\n");

    printSlowly("这日，你来到了当地有名的大城市——云霄城，接下来的时间你决定在这里定居。\n");
    printSlowly("初升的朝阳透过薄雾，洒下温暖的金色光辉，映照在云霄城的城墙上。你缓步走来，心中满是期待与紧张。\n");
    printSlowly("远远望去，云霄城如同一颗璀璨的明珠，镶嵌在青山绿水之间，城墙高耸，巍峨壮观，仿佛在向世人宣告着它的威严与神秘。\n");
    printSlowly("城门口，雕刻精美的石狮子静静守护，似乎在审视每一个踏入城中的人。你深吸一口气，感受到空气中弥漫着的江湖气息。\n");
    printSlowly("一路走来已经有些累了，在赶路的过程中还受了点伤，听说这里药房的店主人很好，你准备先去那里看看。\n");
}

bool load()
{
    system("cls");
    namespace fs = filesystem;
    const fs::path path = "../files";
    int i = 0;
    vector<string> archive;
    for (const auto &entry : fs::directory_iterator(path)) {
        if (entry.path().filename().string() == "maps")
            continue;
        if (entry.is_directory()) {
            ++i;
            fmt::print("{}. {}\n", i, entry.path().filename().string());
            archive.push_back(entry.path().filename().string());
        }
        fmt::print("你想读取那个存档[编号]: ");
        string choice;
        int index = 0;
        while (true) {
            cin >> choice;
            if (!choice.empty() && all_of(choice.begin(), choice.end(), ::isdigit)) {
                index = stoi(choice);
                if (index <= i) {
                    Gamer.load(archive[index - 1]);
                    break;
                }
            }
            else {
                fmt::print("无效的指令，请输入编号: ");
            }
        }
    }
    if (i == 0) {
        fmt::print("你还没有存档！\n");
        return false;
    }
    return true;
}

void start()
{
    printTitle();
    fmt::print("\t\t\t新的开始[new]\t读取存档[load]\t退出游戏[quit]\n指令: ");
    string choice;
    cin >> choice;
    while (choice != "new" && choice != "quit" && choice != "load") {
        fmt::print("无效指令！");
        cin >> choice;
    }
    if (choice == "new")
        creat();
    else if (choice == "load") {
        if (load()) {
            fmt::print("欢迎回到游戏。\n");
        }
        else {
            system("cls");
            printTitle();
            fmt::print("\t\t\t新的开始[new]\t读取存档[load]\t退出游戏[quit]\n指令: ");
        }
    }
    else
        exit(0);
}

int main()
{
    start();
    auto &[c, x, y] = Gamer.position;
    Area current_map = creatMainCity();
    switch (c) {
        case 1 :
            current_map = creatWuWeiCheng();
            playWuWeiCheng(current_map);
            break;
        case 2 :
            current_map = creatShangHui();
            playShangHui(current_map);
            break;
        default : ;
    }

    printMap(current_map.getArea());
    while (true) {
        fmt::print("\n移动:  move \t 打开背包: bag \t 和npc对话: chat \t 退出: quit \n");
        string command;
        cin >> command;

        if (command == "move") {
            movePlayerLocation(current_map);
        }
        else if (command == "bag") {
            Gamer.openBag();
        }
        else if (command == "chat") {
            if (x == 3 && y == 1) {
                changeMap(current_map);
            }
            else if (x == 2 && y == 2) {
                ShopKeeper().talk(0);
            }
            else if (x == 2 && y == 3) {
                ShopKeeper().talk(1);
            }
            else if (x == 4 && y == 1) {
                ShopKeeper().talk(2);
            }
            else if (x == 3 && y == 5) {
                printSlowly("你：城主我来找你修炼了。\n");
                printSlowly(format(fg(fmt::color::green), "城主: 好，且来城外让我看看你的水平。\n"), 10);
                fmt::print("是否开启对战？[y / n]: ");
                while (true) {
                    cin >> command;
                    if (command == "y" || command == "Y") {
                        fmt::print("正在加载...");
                        waitForLoad(1000);
                        Fight(Enemy::creatBoss(0)).fight([](Player &gamer, Enemy &enemy) {
                            if (gamer.getHp() <= 10 || enemy.getHp() <= 10) { }
                        });
                        printSlowly(format(fg(fmt::color::green), "城主：小子不错嘛。"), 10);
                        break;
                    }
                    if (command == "n" || command == "N") {
                        printSlowly("你：我有一些问题想不通还请城主指点。");
                        fmt::print("城主正在指点你修炼...\n");
                        waitForLoad(2000);
                        printSlowly("你：多谢城主。");
                        break;
                    }
                    fmt::print("无效指令，请输入[y / n]: ");
                }
            }
            else if (current_map.getArea()[x][y].getContent() == Room::Content::NPC) {
                fmt::print("{}\n", current_map.getArea()[x][y].getDescription());
            }
            else {
                fmt::print("这里没有npc");
            }
        }
        else if (command == "quit") {
            Gamer.save();
            fmt::print("感谢你的游玩。");
            waitForAnyKey();
            return 0;
        }
        else {
            fmt::print("无效的指令！\n");
        }
    }
}
