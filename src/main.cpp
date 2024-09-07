#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Area.h"
#include "CreatMap.h"
#include "Helper.h"
#include "PlayMap.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

Player Player;

void creat()
{
    namespace fs = filesystem;
    fmt::print("欢迎来到剑影江湖。");
    fmt::print("请告诉我你的名字: ");
    string name;
    cin >> name;
    Player.setName(name);
    Player.save();
    const fs::path map_folder = "../files/maps";
    const fs::path player_folder = "../files/" + Player.getName();
    copy(map_folder, player_folder / map_folder.filename(), fs::copy_options::recursive | fs::copy_options::overwrite_existing);

    printSlowly("江湖，风起云涌，无数人浪迹天涯，闯荡江湖，只为追求那心中的侠客梦。\n");
    printSlowly("殊不知，在整个江湖的背后，一直有一双大手在默默操控一切，他隐藏在江湖的阴暗面，是彻头彻尾的吸血鬼。\n");
    printSlowly("他试图颠覆武林的秩序，夺取武林之主的宝座，以实现他对整个武林的绝对统治。\n");
    printSlowly("武林中像来不缺少正义之士，而你，" + name + "，正意气风发，即将踏入江湖，势必要维护武林的安定。");
    printSlowly("故事从此刻开始...\n");

    printSlowly("这日，你来到了当地有名的大城市——云霄城，接下来的时间你决定在这里定居。\n");
    printSlowly("初升的朝阳透过薄雾，洒下温暖的金色光辉，映照在云霄城的城墙上。你缓步走来，心中满是期待与紧张。\n");
    printSlowly("远远望去，云霄城如同一颗璀璨的明珠，镶嵌在青山绿水之间，城墙高耸，巍峨壮观，仿佛在向世人宣告着它的威严与神秘。\n");
    printSlowly("城门口，雕刻精美的石狮子静静守护，似乎在审视每一个踏入城中的人。你深吸一口气，感受到空气中弥漫着的江湖气息。\n");
    printSlowly("一路走来已经有些累了，在赶路的过程中还受了点伤，听说这里药房的店主人很好，你准备先去那里看看。\n");
}

bool load()
{
    namespace fs = filesystem;
    const fs::path path = "../files";
    int i = 0;
    vector<string> archive;
    for (const auto &entry : fs::directory_iterator(path)) {
        if (entry.is_directory() && entry.path().filename() != "maps") {
            ++i;
            fmt::print("{}. {}", i, entry.path().filename().string());
            archive.push_back(entry.path().filename().string());
        }
        fmt::print("你想读取那个存档？");
        string choice;
        int index = 0;
        while (true) {
            cin >> choice;
            if (!choice.empty() && all_of(choice.begin(), choice.end(), ::isdigit)) {
                index = stoi(choice);
                if (index <= i) {
                    Player.load(archive[index - 1]);
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
    fmt::print("\t\t\t新的开始[new]\t读取存档[load]\t退出游戏[quit]\n");
    string choice;
    cin >> choice;
    while (choice != "new" && choice != "quit" && choice != "load") {
        fmt::print("无效指令！");
        cin >> choice;
    }
    if (choice == "new")
        creat();
    else if (choice == "load")
        load();
    else
        exit(0);
}

int main()
{
    start();
    auto &[c, x, y] = Player.position;
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
        fmt::print("\n移动:  move \t 打开背包: bag \t 和npc对话: chat \t 环视周围: watch \t 退出: quit \n");
        string command;
        cin >> command;

        if (command == "move") {
            movePlayerLocation(current_map);
        }
        else if (command == "bag") {
            Player.openBag();
        }
        else if (command == "chat") {
            // if (npc != "马夫") {
            // npc.talk()
            // }
            // else {
            // changeMap(current_map, x, y);
            // }
        }
        else if (command == "quit") {
            Player.save();
            fmt::print("感谢你的游玩。");
            return 0;
        }
        else {
            fmt::print("无效的指令！\n");
        }
    }
}
