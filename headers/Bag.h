#pragma once

#include <unordered_map>
#include <vector>
#include "Constant.h"
#include "Equipment.h"
#include "Player.h"

class Player;

class Bag
{
public:
    Bag();

    void display();                                     // 打开背包展示物品
    void useEquipment(const Player &player);            // 选择物品使用
    void addArmor(const Armor &armor);                  // 添加防具
    void removeArmor(const Armor &armor);               // 删除防具
    void addWeapon(const Weapon &weapon);               // 添加武器
    void removeWeapon(const Weapon &weapon);            // 删除武器
    int usePill();                                      // 使用血瓶
    int addPill(PillType type, PillSize size, int num); // 添加蓝瓶
private:
    std::vector<Weapon> weapons;                                                     // 背包中的武器
    std::vector<Armor> armors;                                                       // 背包中的防具
    std::unordered_map<PillType, std::unordered_map<PillSize, int> > pill_container; // 背包中的药品
};
