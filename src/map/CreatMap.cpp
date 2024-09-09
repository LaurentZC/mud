#include "CreatMap.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "fmt/color.h"

using namespace std;

void changeColor(string &text, const vector<TextColor> &colors)
{
    size_t start = 0;
    while ((start = text.find('[', start)) != string::npos) {
        const size_t end = text.find(']', start);

        string key = text.substr(start + 1, end - start - 1);
        bool replaced = false;

        for (const auto &[keys, color] : colors) {
            if (find(keys.begin(), keys.end(), key) != keys.end()) {
                string replacement = format(fg(color), "{}", key);
                text.replace(start, end - start + 1, replacement);
                start += replacement.length();
                replaced = true;
                break;
            }
        }
        if (!replaced) {
            start = end + 1;
        }
    }
}

//  X        X       城主府      X         X
//  X       居民区     空       居民区       X
//  X       铁匠铺     空       任务地点     X
//  X       医院     出生地      商店        X
//  X        X       城 门      X          X
Area creatMainCity()
{
    Area main_city(area("main_city"));
    auto &rooms = main_city.getArea();
    ifstream input_file("../files/maps/MainCity.txt");
    if (!input_file.is_open()) {
        cerr << "Could not open file MainCity.txt" << endl;
        exit(1);
    }

    // @formatter:off
    static const vector COLORS = {
        // 房间
        TextColor {{"城门", "医馆", "杂货商店", "铁匠铺", "居民区", "城主府"}, fmt::color::magenta},
        // npc
        TextColor {{"马夫", "医生", "铁匠师傅", "老李", "小翠", "李白", "城主", "老张"}, fmt::color::green}
    };
    // @formatter:on

    int x, y;
    string name, description, content;
    while (input_file >> x >> y >> name >> description >> content) {
        auto content_handled = Room::Content::EMPTY;
        changeColor(description, COLORS);
        if (content == "npc")
            content_handled = Room::Content::NPC;
        rooms[x][y].setup(name, description, content_handled);
    }
    return main_city;
}

//   X      X     npc   X      X
// 武器仓库  X     陆洪   X    丹药仓库
// 青龙堂   小怪    空   小怪   白虎堂
//   X    门卫亭  城门  门卫亭    X

Area creatWuWeiCheng()
{
    Area wu_wei_cheng(area("wu_wei_cheng"));
    auto &rooms = wu_wei_cheng.getArea();
    ifstream input_file("../files/maps/WuWeiCheng.txt");
    if (!input_file.is_open()) {
        cerr << "Could not open file WuWeiCheng.txt" << endl;
        exit(1);
    }

    // @formatter:off
    static const vector COLORS = {
        // 房间
        TextColor {{"城门", "门卫亭", "青龙堂", "白虎堂"}, fmt::color::magenta},
        // npc
        TextColor {{"囚犯"}, fmt::color::green},
        // 小怪
        TextColor {{"门卫", "陆洪的手下"}, fmt::color::yellow},
        // 精英怪
        TextColor {{"青龙卫", "白虎卫"}, fmt::color::orange},
        // boss
        TextColor {{"陆洪"}, fmt::color::gold},
        // 奖励
        TextColor {{"箱子"}, fmt::color::cyan}
    };
    // @formatter:on

    int x, y;
    string name, description, content;
    while (input_file >> x >> y >> name >> description >> content) {
        Room::Content content_handled;
        changeColor(description, COLORS);
        if (content == "empty")
            content_handled = Room::Content::EMPTY;
        else if (content == "gate")
            content_handled = Room::Content::GATE;
        else if (content == "chest")
            content_handled = Room::Content::CHEST;
        else if (content == "npc")
            content_handled = Room::Content::NPC;
        else if (content == "monster")
            content_handled = Room::Content::MONSTER;
        else if (content == "elite")
            content_handled = Room::Content::ELITE;
        else
            content_handled = Room::Content::BOSS;
        rooms[x][y].setup(name, description, content_handled);
    }
    return wu_wei_cheng;
}

Area creatShangHui()
{
    Area shang_hui(area("shang_hui"));
    auto &rooms = shang_hui.getArea();
    ifstream input_file("../files/maps/ShangHui.txt");
    if (!input_file.is_open()) {
        cerr << "Could not open file ShangHui.txt" << endl;
        exit(1);
    }

    // @formatter:off
    static const vector COLORS = {
        // 房间
        TextColor {{"飞云商会"}, fmt::color::magenta},
        // npc
        TextColor {{"老翁"}, fmt::color::green},
        // 小怪
        TextColor {{"敌人"}, fmt::color::yellow},
        // 精英怪
        TextColor {{"影刃卫", "怒焰卫", "天霸卫"}, fmt::color::orange},
        // boss
        TextColor {{"段霖"}, fmt::color::gold},
        // 奖励
        TextColor {{"箱子"}, fmt::color::cyan},
        // 陷阱
        TextColor {{"陷阱", "毒气", "爆炸", "箭"}, fmt::color::red}
    };
    // @formatter:on

    int x, y;
    string name, description, content;
    while (input_file >> x >> y >> name >> description >> content) {
        Room::Content content_handled;
        changeColor(description, COLORS);
        if (content == "gate")
            content_handled = Room::Content::GATE;
        else if (content == "chest")
            content_handled = Room::Content::CHEST;
        else if (content == "npc")
            content_handled = Room::Content::NPC;
        else if (content == "monster")
            content_handled = Room::Content::MONSTER;
        else if (content == "elite")
            content_handled = Room::Content::ELITE;
        else if (content == "boss")
            content_handled = Room::Content::BOSS;
        else if (content == "trap")
            content_handled = Room::Content::TRAP;
        else
            content_handled = Room::Content::POISON;
        rooms[x][y].setup(name, description, content_handled);
    }
    return shang_hui;
}
