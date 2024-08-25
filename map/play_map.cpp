#include <iostream>
#include <limits>
#include <string>
#include "../headers/Area.h"
#include "../headers/Constant.h"
#include "../headers/Helper.h"
#include "../headers/Player.h"

using namespace std;

void getCommand(Area& map, pair<int, int>& player_position)
{
    auto& [x, y] = player_position;
    const auto& rooms = map.getArea();
    string command;
    cout << "�������������أ�";
    bool error;
    do {
        cin >> command;
        if (command == UP) {
            if (y + 1 <= MAP_MAX_SIZE && rooms[x][y + 1].canPass()) {
                ++y;
                error = false;
            }
            else {
                cout << "ǰ����һ��ǽ�����޷�ͨ��" << endl << "��һ�������߰ɣ�";
                error = true;
            }
        }
        else if (command == DOWN) {
            if (y - 1 >= 1 && rooms[x][y - 1].canPass()) {
                --y;
                error = false;
            }
            else {
                cout << "ǰ����һ��ǽ�����޷�ͨ��" << endl << "��һ�������߰ɣ�";
                error = true;
            }
        }
        else if (command == LEFT) {
            if (x - 1 >= 1 && rooms[x - 1][y].canPass()) {
                --x;
                error = false;
            }
            else {
                cout << "ǰ����һ��ǽ�����޷�ͨ��" << endl << "��һ�������߰ɣ�";
                error = true;
            }
        }
        else if (command == RIGHT) {
            if (x + 1 <= MAP_MAX_SIZE && rooms[x + 1][y].canPass()) {
                ++x;
                error = false;
            }
            else {
                cout << "ǰ����һ��ǽ�����޷�ͨ��" << endl << "��һ�������߰ɣ�";
                error = true;
            }
        }
        else {
            cout << "��Ч��ָ����������룺";
            error = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (error);
}

void processPlayerLocation(Area& map, Player& player)
{
    // ��ҵ�λ��
    pair<int, int> player_location = make_pair(0, 0);
    auto& [x, y] = player_location;

    // ���ҳ���
    const auto& rooms = map.getArea();
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

    getCommand(map, player_location);
    cout << rooms[x][y].getDescription() << endl;
    switch (rooms[x][y].getContent()) {
        case Content::EMPTY:
            break;
        case Content::MONSTER:
            break;
        case Content::ELITE:
            break;
        case Content::BOSS:
            break;
        case Content::CHEST:
            break;
        default:
            break;
    }
}
