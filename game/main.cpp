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
    TextColor {{""}, fmt::color::purple},  // ��ͼ
    TextColor {{""}, fmt::color::magenta}, // ����
    TextColor {{""}, fmt::color::yellow},  // С��
    TextColor {{""}, fmt::color::orange},  // ��Ӣ��
    TextColor {{""}, fmt::color::gold},    // boss
    TextColor {{""}, fmt::color::green}    // npc
};

// �������滻�ַ����еĹؼ�����ɫ
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
        fmt::print(current_map->getName() == "main_city" ? "�����ڴ������ǣ��˳���������Ϸ����ȷ����[y/n]: " : "��ȷ��Ҫ�˳���ǰ��ͼ��[y/n]: ");

        cin >> input;
        if (input == "y" || input == "Y") {
            if (current_map->getName() == "main_city") {
                fmt::print("��л������棡\n");
                quit = false;
            }
            else
                current_map = make_shared<Area>(main_city);
            break;
        }
        if (input == "n" || input == "N")
            break;
        fmt::print("��Ч���룬������ 'y' �� 'n'��\n");
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
    // ������ͼ
    Area main_city(area("main_city"));
    creatMainCity(main_city); // ����
    Area wu_wei_cheng(area("wu_wei_cheng"));
    creatWuWeiCheng(wu_wei_cheng); // ������
    // ����λ��
    unordered_map<string, pair<int, int> > gate = {
        {area("main_city"), make_pair(3, 1)},
        {area("wu_wei_cheng"), make_pair(3, 1)}
    };

    // ��ǰ��ͼ�����λ��
    auto current_map = make_shared<Area>(main_city);
    const auto &rooms = current_map->getArea();
    auto [x, y] = gate[current_map->getName()];

    bool quit = true;
    while (quit) {
        fmt::print("������ʲô�أ�\n");
        fmt::print("�ƶ��� move \t �򿪱�����bag \t ��npc�Ի���chat \t ������Χ��watch \t �˳���quit \n");
        fmt::print("��ѡ��");
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
                fmt::print("����û��npc���ԶԻ��������ж��ɡ�\n");
            }
            else {
                // ��npc�Ի�
            }
        }
        else if (command == "watch") {
            // ��һ��
        }
        else if (command == "quit") {
            handleQuit(current_map, main_city, quit);
        }
        else {
            fmt::print("��Ч��ָ�\n");
        }
    }
}
