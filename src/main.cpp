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

int main()
{
    // ��ǰ��ͼ�����λ��


    // bool quit = true;
    // while (quit) {
    //     fmt::print("������ʲô�أ�\n");
    //     fmt::print("�ƶ��� move \t �򿪱�����bag \t ��npc�Ի���chat \t ������Χ��watch \t �˳���quit \n");
    //     fmt::print("��ѡ��");
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
    //             fmt::print("����û��npc���ԶԻ��������ж��ɡ�\n");
    //         }
    //         else {
    //             // ��npc�Ի�
    //         }
    //     }
    //     else if (command == "watch") {
    //         // ��һ��
    //     }
    //     else if (command == "quit") {
    //         handleQuit(current_map, main_city, quit);
    //     }
    //     else {
    //         fmt::print("��Ч��ָ�\n");
    //     }
    // }
}
