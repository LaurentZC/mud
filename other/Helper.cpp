#include "../headers/Helper.h"
#include "../headers/Constant.h"

using namespace std;

string color(const string& text, const string& color) { return string(color + text + RESET); }

string place(const string& text) { return string(BLUE + text + RESET); }

string minion(const string& text) { return string(YELLOW + text + RESET); }

string elite(const string& text) { return string(ORANGE + text + RESET); }

string boss(const string& text) { return string(RED + text + RESET); }
