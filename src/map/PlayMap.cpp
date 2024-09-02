#include "PlayMap.h"

#include <CreatMap.h>
#include <iostream>
#include <memory>
#include <string>

#include "Area.h"
#include "Helper.h"
#include "fmt/core.h"

using namespace std;
extern Area MainCity;

bool isValidMove(const int x, const int y, Area &map, const char dir)
{
    const auto &rooms = map.getArea();
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

void handlePlayerAction(Area &map, const int x, const int y)
{
    auto get_yes_or_no = []() -> bool {
        while (true) {
            string input;
            cin >> input;
            if (input == "y" || input == "Y")
                return true;
            if (input == "n" || input == "N")
                return false;
            cout << "��Чָ�[y / n]��";
        }
    };

    switch (const auto &rooms = map.getArea(); rooms[x][y].getContent()) {
        case Room::Content::EMPTY :
            fmt::print("{}", map.getArea()[x][y].getDescription());
            break;

        case Room::Content::CHEST :
            fmt::print("��Ҫ������[y / n]");
            if (get_yes_or_no()) {
                // �򿪱���Ĵ����߼�
            }
            break;

        case Room::Content::NPC :
            fmt::print("��Ҫ�����Ի���[y / n]");
            if (get_yes_or_no()) {
                // ��NPC�Ի��Ĵ����߼�
            }
            break;

        default : // С�֣���Ӣ�֣�boss
            fmt::print("����Ҫ��������(y)�����ȴ򿪱�������һ��(n)��");
            if (!get_yes_or_no()) {
                // player.openBag();
                break;
            }
        // ս���Ĵ����߼�
            break;
    }
}

void movePlayerLocation(Area &map, int &x, int &y)
{
    string command;
    while (true) {
        fmt::print("�������������أ�[w / a / s / d]��");
        cin >> command;
        if (command.length() != 1 || strchr("wasd", command[0]) == nullptr) {
            fmt::print("��Ч��ָ�[w / a / s / d]��");
            continue;
        }
        if (isValidMove(x, y, map, command[0])) {
            switch (command[0]) {
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
            break;
        }
        fmt::print("ǰ����һ��ǽ�����޷�ͨ����\n�뻻һ������� [w / a / s / d]��");
    }
    handlePlayerAction(map, x, y);
}

void handleQuit(Area &current_map, bool &quit, int &x, int &y)
{
    string input;
    // @formatter:off
    fmt::print(current_map.getName() == area("main_city") ?
                                            "�����ڴ������ǣ��˳���������Ϸ����ȷ����[y/n]: " :
                                            "��ȷ��Ҫ�˳���ǰ��ͼ��[y/n]: ");
    // @ formatter:on
    while (true) {
        cin >> input;
        if (input == "y" || input == "Y") {
            if (current_map.getName() == "main_city") {
                fmt::print("��л������棡\n");
                quit = false;
            }
            else {
                current_map = MainCity;
                x = Gates["main_city"].first;
                y = Gates["main_city"].second;
            }
            break;
        }
        if (input == "n" || input == "N")
            break;
        fmt::print("��Ч���룡������[y / n]��\n");
    }
}

void changeMap(Area &map, int &x,int &y)
{
    string input;
    while (true) {
        cin >> input;
        if (input.length() != 1) {
            fmt::print("��Ч������[1 / 2 / 3 / 4 / 5 / q]: ");
            continue;
        }
        switch (input[0]) {
            case '1':
                // map = creat()
                // x = Gates[map].first;
                // y = Gates[map].second;
                    waitForLoad(100);
                return;
            case '2':
                // map = creat()
                // x = Gates[map].first;
                // y = Gates[map].second;
                    waitForLoad(100);
                return;
            case '3':
                // map = creat()
                // x = Gates[map].first;
                // y = Gates[map].second;
                    waitForLoad(100);
                return;
            case '4':
                // map = creat()
                // x = Gates[map].first;
                // y = Gates[map].second;
                    waitForLoad(100);
                return;
            case '5':
                // map = creat()
                // x = Gates[map].first;
                // y = Gates[map].second;
                    waitForLoad(100);
                return;
            case 'q':
                return;
            default:
                fmt::print("��Ч������[1 / 2 / 3 / 4 / 5 / q]: ");
        }
    }
}
