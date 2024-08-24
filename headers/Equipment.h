#pragma once

#include <string>

// 装备
class Equipment
{
    std::string name {};        // 名字
    std::string description {}; // 描述
    int money {};          // 购买价格
    public:
        // 装备上
    void equip();
    // 卸下
    void unequip();
};

// 武器
class Weapon : public Equipment
{
    int damage {};             // 伤害
    double critical {};        // 暴击率
    int min_strength_to_equip {}; // 装备的最小力量点数要求
};

// 防具
class Armor : public Equipment
{
    int defense {};    // 防御力
    double evasion {}; // 闪避率
    int min_agility {}; // 装备的最小敏捷点数要求
};
