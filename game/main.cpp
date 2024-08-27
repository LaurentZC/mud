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
        fmt::print(current_map->getName() == "main_city" ? "�����ڴ������ǣ��˳���������Ϸ����ȷ����[y/n]: " : "��ȷ��Ҫ�˳���ǰ��ͼ��[y/n]: ");

        cin >> input;
        if (input == "y" || input == "Y") {
            if (current_map->getName() == "main_city") {
                fmt::print("��л������棡\n");
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
        fmt::print("��Ч���룬������ 'y' �� 'n'��\n");
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
        fmt::println("������ʲô�أ�");
        fmt::println("�ƶ��� move \t �򿪱�����bag \t ��npc�Ի���chat \t ������Χ��watch \t �˳���quit");
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
                fmt::println("����û��npc���ԶԻ��������ж��ɡ�");
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
