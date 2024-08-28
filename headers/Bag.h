#pragma once

#include <map>
#include <unordered_map>
#include <vector>

#include "Equipment.h"
#include "Pill.h"
#include "Player.h"

class Bag
{
public:
    Bag();

    void display();                          // 打开背包展示物品
    void useEquipment(const Player &player); // 选择物品使用
    void addArmor(const Armor &armor);       // 添加防具
    void removeArmor(const Armor &armor);    // 删除防具
    void addWeapon(const Weapon &weapon);    // 添加武器
    void removeWeapon(const Weapon &weapon); // 删除武器
    void usePill();                          // 使用
    int addPill(Pill pill, int num);         // 添加
private:
    std::vector<Weapon> weapons; // 背包中的武器
    std::vector<Armor> armors;   // 背包中的防具
    std::map<Pill, int> pills = {
        {Pill {Pill::Type::BLOOD_PILL, Pill::Size::BIG}, 0},
        {Pill {Pill::Type::BLOOD_PILL, Pill::Size::MID}, 0},
        {Pill {Pill::Type::BLOOD_PILL, Pill::Size::SMALL}, 0},

        {Pill {Pill::Type::MANA_PILL, Pill::Size::BIG}, 0},
        {Pill {Pill::Type::MANA_PILL, Pill::Size::MID}, 0},
        {Pill {Pill::Type::MANA_PILL, Pill::Size::SMALL}, 0}
    }; // 背包中的药品
};
