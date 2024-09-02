#include <fstream>
#include <iostream>
#include <unordered_map>
#include <windows.h>

#include "Area.h"
#include "CreatMap.h"
#include "PlayMap.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

extern auto MainCity = creatMainCity();
extern Player Player;

void waitForAnyKey()
{
    const auto input_handle = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD input_record;
    DWORD events_read;

    while (true) {
        // @formatter:off
        // ��ȡ����̨�����¼�
        if (ReadConsoleInput(input_handle, &input_record, 1, &events_read) &&
                             input_record.EventType == KEY_EVENT &&
                             input_record.Event.KeyEvent.bKeyDown) {
            // ����Ǽ��̰����¼���������ѭ��
            break;
        }
        // @formatter:on
    }
}

int main()
{
    bool quit = true;
    auto &current_map = MainCity;
    auto &[x, y] = Gates[current_map.getName()];
    while (quit) {
        fmt::print("\n�ƶ��� move \t �򿪱�����bag \t ��npc�Ի���chat \t ������Χ��watch \t �˳���quit \n");
        string command;
        cin >> command;

        if (command == "move") {
            movePlayerLocation(current_map, x, y);
        }
        else if (command == "bag") {
            // player.openBag();
        }
        else if (command == "chat") {
            // if (npc != "���") {
            // npc.talk()
            // }
            // else {
            // changeMap(current_map, x, y);
        }
        else if (command == "watch") {
            // ��һ��
        }
        else if (command == "quit") {
            handleQuit(current_map, quit, x, y);
        }
        else {
            fmt::print("��Ч��ָ�\n");
        }
    }
}
