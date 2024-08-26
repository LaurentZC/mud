#pragma once

#include <map>
#include <vector>
#include "Equipment.h"
#include "Player.h"

class Player;

class Bag
{
public:
    Bag();
    void display();                                       // 打开背包展示物品
    void useEquipment(Player &player);                    // 选择物品使用
    void addArmor(const Armor &armor);                    //添加防具
    void removeArmor(const Armor &armor);                 //删除
    void addWeapon(const Weapon &weapon);                 //往背包中添加武器
    void removeWeapon(const Weapon &weapon);              //删除
    int useBloodPotion();                                 //使用血瓶
    int useManaPotion();                                  //使用蓝瓶
    int addBloodPotion(const std::string &type, int num); //添加血瓶
    int addManaPotion(const std::string &type, int num);  //添加蓝瓶
private:
    friend Player;
    std::vector<Weapon> weapons;                                                      // 背包中的武器
    std::vector<Armor> armors;                                                        // 背包中的防具
    std::map<std::string, int> blood_potion = {{"big", 0}, {"mid", 0}, {"small", 0}}; //血瓶数和类型
    std::map<std::string, int> mana_potion = {{"big", 0}, {"mid", 0}, {"small", 0}};; //蓝瓶数和类型s
};
