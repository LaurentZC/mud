#pragma once

#include <array>
#include <memory>
#include <unordered_map>

#include "Bag.h"
#include "Skill.h"
#include "Task.h"

class Bag;

class Player
{
public:
    std::array<int, 3> position {0, 4, 3};
    std::array<bool, 2> finished {false, false};

    void showPlayer() const;
    [[nodiscard]] bool checkSkill() const;
    void checkTask() const;
    void openBag();
    void showBag();
    void usePoint();
    void usePill();

    void acceptTask(const Task &task);
    void finishTask(const Task &task);
    void gainSkill(int index);

    void removeTask(const Task &task);
    [[nodiscard]] int gainPill(Pill pill, int index);

    void buyArmor(const Armor &armor);
    void buyWeapon(const Weapon &weapon);
    void gainWeapon(int index);
    void gainArmor(int index);

    void sellArmor(const Armor &armor);
    void sellWeapon(const Weapon &weapon);
    void removeArmor(const Armor &armor); //卸下装备
    void removeWeapon(const Weapon &weapon);
    void equipWeapon(const Weapon &weapon); //装上装备
    void equipArmor(const Armor &armor);

    void save() const;
    bool load(const std::string &archive);

    [[nodiscard]] std::string getName() const;
    void setName(const std::string &name);
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getLvExp() const;
    void gainExp(int exp);
    [[nodiscard]] int getMaxHp() const;
    void setMaxHp(int max_hp);
    [[nodiscard]] int getMaxMp() const;
    void setMaxMp(int max_mp);
    [[nodiscard]] int getHp() const;
    void setHp(int hp);
    [[nodiscard]] int getMp() const;
    void setMp(int mp);
    [[nodiscard]] int getHealth() const;
    void setHealth(int health);
    [[nodiscard]] int getDamage() const;
    void setDamage(int damage);
    [[nodiscard]] double getCritical() const;
    void setCritical(double critical);
    [[nodiscard]] int getStrength() const;
    void setStrength(int strength);
    [[nodiscard]] int getDefence() const;
    void setDefence(int defence);
    [[nodiscard]] double getEvasion() const;
    void setEvasion(double evasion);
    [[nodiscard]] int getAgility() const;
    void setAgility(int agility);
    [[nodiscard]] int getMoney() const;
    [[nodiscard]] int getPoints() const;
    void gainMoney(int money);
    void addPoints(int points);
    [[nodiscard]] std::vector<Skill> &getSkills();
    [[nodiscard]] std::vector<Weapon> &getWeapons();
    [[nodiscard]] std::vector<Armor> &getArmors();

private:
    std::string name;
    int level {1};
    int experience {};
    int level_up_exp {100};
    int points {};

    int max_hp {1000}; // 最大的血量
    int max_mp {1050}; // 最大的蓝量
    int hp {max_hp};   // 当前血量
    int mp {max_mp};   // 当前蓝量
    int health {1};    // 健康点数

    int damage {110};       // 攻击力
    double critical {0.10}; // 暴击率
    int strength {1};       // 攻击点数

    int defence {65};      // 防御力
    double evasion {0.10}; // 闪避率
    int agility {1};       // 闪避点数

    int money {200};                       // 金钱
    Bag bag;                               // 背包
    std::vector<Skill> skills {Skills[0]}; // 技能
    std::vector<Task> tasks;               // 任务
};

// @formatter:off
// 升级 1 ~ n 的总经验
inline std::array ExpNeeded = {
        0,   100,   210,   330,   460,
      600,   750,   910,  1080,  1260,
     1450,  1650,  1860,  2080,  2310,
     2550,  2800,  3060,  3330,  3610,
     3900,  4200,  4510,  4830,  5160,
     5500,  5850,  6210,  6580,  6960,
     7350,  7750,  8160,  8580,  9010,
     9450,  9900, 10360, 10830, 11310,
    11800, 12300, 12810, 13330, 13860,
    14400, 14950, 15510, 16080, 16660,
    INT_MAX
};
// @formatter:on
