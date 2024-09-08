#include "Helper.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <thread>
#include <windows.h>

#include "Player.h"
#include "fmt/color.h"

extern Player Gamer;

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
    // 清空控制台输入缓冲区
    DWORD dw_read;
    while (PeekConsoleInput(input_handle, &input_record, 1, &dw_read) && dw_read > 0) {
        ReadConsoleInput(input_handle, &input_record, 1, &dw_read);
    }
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

void printTitle()
{
    const std::string title = R"(
                 ||       ||             ||                                        ||
                 ||       ||        |||||||    ||        ||                       ||
                |||       ||        |||| ||   |||        |||                 |||  ||     |
                |||||     ||         ||| |    ||          ||    ||||||        ||  ||  |||||
               ||| |||||  ||         |||||   ||              ||||||||          |  |   || ||
               ||    |||| ||         |||    || |       |     |||||         ||     |||||| ||
              |||||||  |  ||          |||||||  ||      |||      ||         ||| |||||| |||||
             || |||||  |  ||     |||||||||||  ||        ||      ||          || ||||   || ||
            ||   | ||| |  ||     |||||||||   ||          | |    ||            |  |||| |||||
           || || ||||  |  ||        ||  |   || |          ||    ||            ||||||| |||||
               |||||| ||  ||        |||||  ||  ||        ||     || |||       ||||  ||||  ||
               || ||  ||  ||       || ||||    |||       |||   |||||||||      |  | || ||  ||
                  |||| |  ||       || || ||   ||       |||||||||||||||||    ||  |||| ||  ||
             ||||||||     ||      ||||||  |  ||        ||| ||               ||  |   ||   ||
             ||||       ||||       | |||    |||        ||                   ||     ||  ||||
                        ||||          |    |||          |                         ||   ||||
                         ||              |||                                      |     ||
                          |             |||                                              |
    )";
    fmt::print(title);
}

void printSlowly(const std::string &text, const int delay_milliseconds)
{
    for (const auto &c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_milliseconds)); // 延迟
    }
    waitForAnyKey();
}

// 随机返回 true / false
bool achievePercent(const double probability)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution d(probability);
    return d(gen);
}

void restart()
{
    // 问的大佬: 重启程序
    TCHAR sz_file_name[MAX_PATH];
    GetModuleFileName(nullptr, sz_file_name, MAX_PATH);
    // 设置启动信息
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    // 启动新进程
    // @formatter:off
    if (CreateProcess(nullptr, sz_file_name, nullptr, nullptr,
        FALSE, 0, nullptr, nullptr, &si, &pi)) {
        // 关闭句柄
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        // 退出当前进程
        exit(0);
    }
    // @formatter:on
}
