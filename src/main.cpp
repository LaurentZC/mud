#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Area.h"
#include "CreatMap.h"
#include "PlayMap.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

Player Player;

void creat() { }

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

int main()
{
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
