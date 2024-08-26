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
    // ������ͼ
    Area main_city("main_city");
    creatMainCity(main_city);      // ����
    Area wu_wei_cheng("wu_wei_cheng");
    creatWuWeiCheng(wu_wei_cheng); // ������

    // ��ǰ��ͼ�����λ��
    auto current_map = make_shared<Area>(main_city);
    const auto &rooms = current_map->getArea();
    auto [x, y] = enterNewMap(*current_map);

    bool quit = true;
    while (quit) {
        cout << "������ʲô�أ�" << endl;
        cout << "�ƶ��� move \t �򿪱�����bag \t ��npc�Ի���chat \t ������Χ��watch \t �˳���quit" << endl;
        cout << "��ѡ��";
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
                    cout << "����û��npc���ԶԻ��������ж��ѡ�" << endl;
                }
                else {
                    // ��npc�Ի�
                }
                break;
            }
            if (command == "watch") {
                // ��һ��
                break;
            }
            if (command == "quit") {
                if (current_map->getName() == "main_city") {
                    cout << "�����ڴ������ǣ��˳���������Ϸ����ȷ����";
                    if (getYorN()) {
                        cout << "��л������棡" << endl;
                        return 0;
                    }
                }
                else {
                    cout << "��ȷ��Ҫ�˳���ǰ��ͼ�𣿣�y/n��";
                    if (getYorN())
                        quit = false;
                    current_map = make_shared<Area>(main_city);
                }
            }
            cout << "��Ч��ָ�" << endl;
        }
    }
}
