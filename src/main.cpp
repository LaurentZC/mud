#include <fstream>
#include <iostream>
#include <unordered_map>

#include "Area.h"
#include "CreatMap.h"
#include "PlayMap.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

auto MainCity = creatMainCity();
Player Player;

int main()
{
    bool quit = true;
    auto &current_map = MainCity;
    auto &[x, y] = Gates[current_map.getName()];
    printMap(current_map.getArea());
    while (quit) {
        fmt::print("\n移动:  move \t 打开背包: bag \t 和npc对话: chat \t 环视周围: watch \t 退出: quit \n");
        string command;
        cin >> command;

        if (command == "move") {
            movePlayerLocation(current_map, x, y);
        }
        else if (command == "bag") {
            // player.openBag();
        }
        else if (command == "chat") {
            // if (npc != "马夫") {
            // npc.talk()
            // }
            // else {
            // changeMap(current_map, x, y);
        }
        else if (command == "watch") {
            // 看一看
        }
        else if (command == "quit") {
            handleQuit(current_map, quit, x, y);
        }
        else {
            fmt::print("无效的指令！\n");
        }
    }
}
