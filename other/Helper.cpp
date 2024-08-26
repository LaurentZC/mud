#include "Helper.h"

#include <iostream>
#include <limits>
#include "fmt/color.h"

using namespace std;

string place(const string &text) { return format(fg(fmt::color::blue), "{}", text); }

string minion(const string &text) { return format(fg(fmt::color::yellow), "{}", text); }

string elite(const string &text) { return format(fg(fmt::color::orange), "{}", text); }

string boss(const string &text) { return format(fg(fmt::color::red), "{}", text); }

string npc(const string &text) { return format(fg(fmt::color::cyan), "{}", text); }

string armor(const string &text) { return format(fg(fmt::color::magenta), "{}", text); }

string weapon(const string &text) { return format(fg(fmt::color::blue), "{}", text); }

string bloodPill(const string &text) { return format(fg(fmt::color::yellow), "{}", text); }

string manaPill(const string &text) { return format(fg(fmt::color::red), "{}", text); }

string area(const string &text) { return format(fg(fmt::color::cyan), "{}", text); }
