#pragma once

#include <string>

using namespace std;

class Task
{
    string name {}; // 名字
    int experience {}; // 完成后的经验

public:
    // 完成任务
    void finish();
};
