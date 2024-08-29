#include "../includes/Helper.h"

#include <iostream>
#include "../fmt/include/fmt/color.h"

using namespace std;

string area(const string &text) { return format(fg(fmt::color::purple), "{}", text); }

string place(const string &text) { return format(fg(fmt::color::magenta), "{}", text); }

string minion(const string &text) { return format(fg(fmt::color::yellow), "{}", text); }

string elite(const string &text) { return format(fg(fmt::color::orange), "{}", text); }

string boss(const string &text) { return format(fg(fmt::color::gold), "{}", text); }

string npc(const string &text) { return format(fg(fmt::color::green), "{}", text); }

string armor(const string &text) { return format(fg(fmt::color::light_green), "{}", text); }

string weapon(const string &text) { return format(fg(fmt::color::cyan), "{}", text); }

string bloodPill(const string &text) { return format(fg(fmt::color::red), "{}", text); }

string manaPill(const string &text) { return format(fg(fmt::color::blue), "{}", text); }
