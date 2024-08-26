#include <iostream>
#include <memory>
#include <utility>
#include "../headers/Area.h"
#include "../headers/CreatMap.h"
#include "../headers/Helper.h"
#include "../headers/PlayMap.h"
#include "../headers/Player.h"

using namespace std;

int main()
{
    // 创建地图
    Area main_city("main_city");
    creatMainCity(main_city);      // 主城
    Area wu_wei_cheng("wu_wei_cheng");
    creatWuWeiCheng(wu_wei_cheng); // 武威城

    // 当前地图和玩家位置
    auto current_map = make_shared<Area>(main_city);
    const auto &rooms = current_map->getArea();
    auto [x, y] = enterNewMap(*current_map);

    bool quit = true;
    while (quit) {
        cout << "你想做什么呢？" << endl;
        cout << "移动： move \t 打开背包：bag \t 和npc对话：chat \t 环视周围：watch \t 退出：quit" << endl;
        cout << "你选择：";
        while (true) {
            string command;
            cin >> command;
            if (command == "move") {
                movePlayerLocation(*current_map, x, y);
                break;
            }
            if (command == "bag") {
                // player.openBag();
                break;
            }
            if (command == "chat") {
                if (rooms[x][y].getContent() != Content::NPC) {
                    cout << "这里没有npc可以对话，继续行动把。" << endl;
                }
                else {
                    // 和npc对话
                }
                break;
            }
            if (command == "watch") {
                // 看一看
                break;
            }
            if (command == "quit") {
                if (current_map->getName() == "main_city") {
                    cout << "你现在处于主城，退出将结束游戏，你确定吗？";
                    if (getYorN()) {
                        cout << "感谢你的游玩！" << endl;
                        return 0;
                    }
                }
                else {
                    cout << "你确定要退出当前地图吗？（y/n）";
                    if (getYorN())
                        quit = false;
                    current_map = make_shared<Area>(main_city);
                }
            }
            cout << "无效的指令！" << endl;
        }
    }
}
