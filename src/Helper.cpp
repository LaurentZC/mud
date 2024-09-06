#include "Helper.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <windows.h>

#include "Player.h"
#include "fmt/color.h"

extern Player Player;

std::string area(const std::string &text) { return format(fg(fmt::color::purple), "{}", text); }

std::string npc(const std::string &text) { return format(fg(fmt::color::green), "{}", text); }

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
        std::this_thread::sleep_for(std::chrono::milliseconds(total_time_ms / total));
    }
    fmt::print("\n");
}

void waitForAnyKey()
{
    fmt::print("Press any key to continue...");
    const auto input_handle = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD input_record;
    DWORD events_read;

    while (true) {
        // @formatter:off
        // 读取控制台输入事件
        if (ReadConsoleInput(input_handle, &input_record, 1, &events_read) &&
                             input_record.EventType == KEY_EVENT &&
                             input_record.Event.KeyEvent.bKeyDown) {
            // 如果是键盘按下事件，则跳出循环
            fmt::print("\r\033[K");
            return;
        }
        // @formatter:on
    }
}

