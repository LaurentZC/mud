#include "../headers/PlayMap.h"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "../headers/Area.h"
#include "../headers/Constant.h"
#include "../headers/Helper.h"
#include "../headers/Player.h"

using namespace std;

pair<int, int> enterNewMap(Area &map)
{
    // ��ҵ�λ��
    pair<int, int> player_location = make_pair(0, 0);

    // ���ҳ��ţ�����Ҹյ���ĵط�
    const auto &rooms = map.getArea();
    bool found = false;
    for (int i = 1; i <= MAP_MAX_SIZE; ++i) {
        for (int j = 1; j <= MAP_MAX_SIZE; ++j) {
            if (rooms[i][j].getName() == place("����")) {
                player_location = make_pair(i, j);
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    return player_location;
}

bool isValidMove(const int x, const int y, const vector<vector<Room> > &rooms, const char dir)
{
    switch (dir) {
        case 'w' :
            return y + 1 <= MAP_MAX_SIZE && rooms[x][y + 1].canPass();
        case 's' :
            return y - 1 >= 1 && rooms[x][y - 1].canPass();
        case 'a' :
            return x - 1 >= 1 && rooms[x - 1][y].canPass();
        case 'r' :
            return x + 1 <= MAP_MAX_SIZE && rooms[x + 1][y].canPass();
        default :
            return false;
    }
}

void applyMove(int &x, int &y, const char dir)
{
    switch (dir) {
        case 'w' :
            ++y;
            break;
        case 's' :
            --y;
            break;
        case 'a' :
            --x;
            break;
        case 'd' :
            ++x;
            break;
        default :
            break;
    }
}

void movePlayerLocation(Area &map, int &x, int &y)
{
    const auto &rooms = map.getArea();

    string command;
    while (true) {
        cout << "�������������أ�w/a/s/d����";
        cin >> command;
        // ָ���ַ���һ����
        if (command.length() > 1) {
            cout << "��Ч��ָ������� 'w', 'a', 's', 'd' ֮һ��" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (isValidMove(x, y, rooms, command[0])) {
            // �ɹ��ƶ��Ϳ����˳�ѭ��
            applyMove(x, y, command[0]);
            cout << rooms[x][y].getDescription() << endl;
            break;
        }
        // �ƶ����ɹ�
        cout << "ǰ����һ��ǽ�����޷�ͨ�����뻻һ������" << endl;
    }

    switch (rooms[x][y].getContent()) {
        case Content::EMPTY :
            break;

        case Content::CHEST :
            cout << "��Ҫ������y/n����";
            if (getYorN()) {
                // �򿪱���
            }
            break;

        case Content::NPC :
            cout << "��Ҫ�����Ի��𣿣�y/n��";
            if (getYorN()) {
                // ��npc�Ի�
            }
            break;

        default : // С�֣���Ӣ�֣�boss
            cout << "����Ҫ����������y�������ȴ򿪱�������һ�£�n����";
            if (!getYorN()) {
                // player.openBag();
                break;
            }

        // ս��
            break;
    }
}
