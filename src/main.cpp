#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>

#include "Area.h"
#include "CreatMap.h"
#include "Helper.h"
#include "Player.h"
#include "PlayMap.h"
#include "fmt/color.h"
#include "fmt/core.h"

using namespace std;

void handleQuit(shared_ptr<Area> &current_map, const Area &main_city, bool &quit)
{
    string input;
    while (true) {
        fmt::print(current_map->getName() == "main_city" ? "你现在处于主城，退出将结束游戏，你确定吗？[y/n]: " : "你确定要退出当前地图吗？[y/n]: ");

        cin >> input;
        if (input == "y" || input == "Y") {
            if (current_map->getName() == "main_city") {
                fmt::print("感谢你的游玩！\n");
                quit = false;
            }
            else
                current_map = make_shared<Area>(main_city);
            break;
        }
        if (input == "n" || input == "N")
            break;
        fmt::print("无效输入，请输入 'y' 或 'n'。\n");
    }
}

int main()
{
    // 当前地图和玩家位置


    // bool quit = true;
    // while (quit) {
    //     fmt::print("你想做什么呢？\n");
    //     fmt::print("移动： move \t 打开背包：bag \t 和npc对话：chat \t 环视周围：watch \t 退出：quit \n");
    //     fmt::print("你选择：");
    //     string command;
    //     cin >> command;
    //
    //     if (command == "move") {
    //         movePlayerLocation(*current_map, x, y);
    //     }
    //     else if (command == "bag") {
    //         // player.openBag();
    //     }
    //     else if (command == "chat") {
    //         if (rooms[x][y].getContent() != Room::Content::NPC) {
    //             fmt::print("这里没有npc可以对话，继续行动吧。\n");
    //         }
    //         else {
    //             // 和npc对话
    //         }
    //     }
    //     else if (command == "watch") {
    //         // 看一看
    //     }
    //     else if (command == "quit") {
    //         handleQuit(current_map, main_city, quit);
    //     }
    //     else {
    //         fmt::print("无效的指令！\n");
    //     }
    // }
}
