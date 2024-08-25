#pragma once

#include <string>

class Task
{
public:
    // 完成任务
    void finish();

private:
    std::string name {}; // 名字
    int experience {};   // 完成后的经验
};
