#include "../headers/Helper.h"

#include <iostream>
#include <limits>

#include "../headers/Constant.h"

using namespace std;

string color(const string &text, const string &color) { return string(color + text + RESET); }

string place(const string &text) { return string(BLUE + text + RESET); }

string minion(const string &text) { return string(YELLOW + text + RESET); }

string elite(const string &text) { return string(ORANGE + text + RESET); }

string boss(const string &text) { return string(RED + text + RESET); }

bool getYorN()
{
    while (true) {
        string command;
        cin >> command;
        if (command == "y" || command == "Y")
            return true;
        if (command == "n" || command == "N")
            return false;
        cout << "无效指令，请输入 y 或 n：";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
