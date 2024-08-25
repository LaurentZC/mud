#pragma once

#include <vector>
#include "Equipment.h"

class Bag
{
public:
    void display(); // 打开背包展示物品
    void use(int);  // 选择物品使用
private:
    std::vector<Weapon> weapons; // 背包中的武器
    std::vector<Armor> armors;   // 背包中的防具
};
