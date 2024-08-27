#include <iostream>
#include <memory>
#include <utility>

#include "Area.h"
#include "CreatMap.h"
#include "Helper.h"
#include "PlayMap.h"
#include "Player.h"
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
            else {
                current_map = make_shared<Area>(main_city);
            }
            break;
        }
        if (input == "n" || input == "N") {
            break;
        }
        fmt::print("无效输入，请输入 'y' 或 'n'。\n");
    }
}

int main()
{
    // 创建地图
    Area main_city(area("main_city"));
    creatMainCity(main_city); // 主城
    Area wu_wei_cheng(area("wu_wei_cheng"));
    creatWuWeiCheng(wu_wei_cheng); // 武威城
    // 城门位置
    unordered_map<string, pair<int, int> > gate = {
        {area("main_city"), make_pair(3, 1)},
        {area("wu_wei_cheng"), make_pair(3, 1)}
    };

    // 当前地图和玩家位置
    auto current_map = make_shared<Area>(main_city);
    const auto &rooms = current_map->getArea();
    auto [x, y] = gate[current_map->getName()];

    bool quit = true;
    while (quit) {
        fmt::println("你想做什么呢？");
        fmt::println("移动： move \t 打开背包：bag \t 和npc对话：chat \t 环视周围：watch \t 退出：quit");
        fmt::print("你选择：");
        string command;
        cin >> command;

        if (command == "move") {
            movePlayerLocation(*current_map, x, y);
        }
        else if (command == "bag") {
            // player.openBag();
        }
        else if (command == "chat") {
            if (rooms[x][y].getContent() != RoomContent::NPC) {
                fmt::println("这里没有npc可以对话，继续行动吧。");
            }
            else {
                // 和npc对话
            }
        }
        else if (command == "watch") {
            // 看一看
        }
        else if (command == "quit") {
            handleQuit(current_map, main_city, quit);
        }
        else {
            fmt::print("无效的指令！\n");
        }
    }
}
