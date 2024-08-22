#include "../headers/Helper.h"
#include "../headers/Constant.h"

using namespace std;

string Color(const string &text, const string &color) { return string(color + text + RESET); }

string Place(const string &text) { return string(BLUE + text + RESET); }

string Minion(const string &text) { return string(YELLOW + text + RESET); }

string Elite(const string &text) { return string(ORANGE + text + RESET); }

string Boss(const string &text) { return string(RED + text + RESET); }
