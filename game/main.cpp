#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <utility>

#include "Area.h"
#include "CreatMap.h"
#include "Helper.h"
#include "Player.h"
#include "PlayMap.h"
#include "fmt/color.h"
#include "fmt/core.h"

using namespace std;

struct TextColor
{
    vector<string> keys;
    fmt::color color;

    TextColor(vector<string> keys, const fmt::color color) : keys(std::move(keys)), color(color) { };
};

static const vector COLORS = {
    TextColor {{""}, fmt::color::purple},  // 地图
    TextColor {{""}, fmt::color::magenta}, // 房间
    TextColor {{""}, fmt::color::yellow},  // 小怪
    TextColor {{""}, fmt::color::orange},  // 精英怪
    TextColor {{""}, fmt::color::gold},    // boss
    TextColor {{""}, fmt::color::green}    // npc
};

// 函数来替换字符串中的关键字颜色
void changeColor(string &text)
{
    size_t start = 0;
    while ((start = text.find('[', start)) != string::npos) {
        const size_t end = text.find(']', start);
        string key = text.substr(start + 1, end - start - 1);
        for (auto it : COLORS) {
            for (auto &[vec, color] : COLORS) {
                if (find(vec.begin(), vec.end(), key) != vec.end()) {
                    string replacement = format(fg(color), "{}", key);
                    text.replace(start, end - start + 1, replacement);
                    start += replacement.length();
                }
            }
        }
    }
}

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

void creatMainCity()
{
    Area main_city("main_city");
    auto &rooms = main_city.getArea();
    ifstream input_file("main_city.txt");
    if (!input_file.is_open()) {
        cerr << "Could not open file main_city.txt" << endl;
    }
    int x, y;
    string name, description, content;
    while (input_file >> x >> y >> name >> description >> content) {
        RoomContent content_handled;
        changeColor(description);
        if (content == "empty")
            content_handled = RoomContent::EMPTY;
        else if (content == "gate")
            content_handled = RoomContent::GATE;
        else if (content == "chest")
            content_handled = RoomContent::CHEST;
        else if (content == "npc")
            content_handled = RoomContent::NPC;
        else if (content == "monster")
            content_handled = RoomContent::MONSTER;
        else if (content == "elite")
            content_handled = RoomContent::ELITE;
        else if (content == "boss")
            content_handled = RoomContent::BOSS;
        rooms[x][y].setup(name, description, content_handled);
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
        fmt::print("你想做什么呢？\n");
        fmt::print("移动： move \t 打开背包：bag \t 和npc对话：chat \t 环视周围：watch \t 退出：quit \n");
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
                fmt::print("这里没有npc可以对话，继续行动吧。\n");
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
