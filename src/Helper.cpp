#include "Helper.h"

#include <chrono>
#include <thread>
#include "fmt/color.h"

using namespace std;

string area(const string &text) { return format(fg(fmt::color::purple), "{}", text); }

string npc(const string &text) { return format(fg(fmt::color::green), "{}", text); }

void waitForLoad(const int total_time_ms)
{
    constexpr int total = 100;
    for (int progress = 0; progress <= total; ++progress) {
        constexpr int bar_width = 70;
        const auto progress_rate = 1.0 * progress / total;
        const int pos = static_cast<int>(bar_width * progress_rate);
        fmt::print("[");
        for (int i = 0; i < bar_width; ++i) {
            if (i < pos)
                print(fg(fmt::color::yellow), "=");
            else if (i == pos)
                print(fg(fmt::color::yellow), ">");
            else
                fmt::print(" ");
        }
        fmt::print("] {}% \r", static_cast<int>(progress_rate * total));
        this_thread::sleep_for(chrono::milliseconds(total_time_ms / total));
    }
}
