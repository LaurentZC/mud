//
// Created by 32186 on 19/8/2024.
//

#pragma once
#include <vector>
#include "Equipment.h"
using namespace std;

class Bag
{
    vector<Weapon> weapons; // 背包中的武器
    vector<Armor> armors;   // 背包中的防具

public:
    void display(); // 打开背包展示物品
    void use(int);  // 选择物品使用
};
