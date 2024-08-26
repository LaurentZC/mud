#pragma once

#include <unordered_map>
#include <vector>
#include "Equipment.h"
#include "Player.h"

class Player;

struct Pill
{
    enum class Type { BLOOD_PILL, MANA_PILL }; // 回血丹，回蓝丹
    enum class Size { BIG, MID, SMALL };       // 大、中、小号

    Type type;  // 回血/回蓝
    Size size;  // 大中小号
    int amount; // 持有数量
};

class Bag
{
public:
    Bag();

    void display();                                // 打开背包展示物品
    void useEquipment(Player &player);             // 选择物品使用
    void addArmor(const Armor &armor);             //添加防具
    void removeArmor(const Armor &armor);          //删除
    void addWeapon(const Weapon &weapon);          //往背包中添加武器
    void removeWeapon(const Weapon &weapon);       //删除
    int usePill();                                 //使用血瓶
    int addPill(Pill::Type type, Pill::Size size, int num); //添加蓝瓶
private:
    std::vector<Weapon> weapons;                                                         // 背包中的武器
    std::vector<Armor> armors;                                                           // 背包中的防具
    std::unordered_map<Pill::Type, std::unordered_map<Pill::Size, int> > pill_container; // 背包中的药品
};
