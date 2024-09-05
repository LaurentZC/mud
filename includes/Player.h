#pragma once

#include <array>
#include <memory>
#include "Bag.h"
#include "Skill.h"
#include "Task.h"

class Bag;

class Player
{
public:
    void showPlayer() const;
    void checkSkill() const;
    void checkTask() const;
    void openBag() const;
    void usePoint();

    void gainWeapon(int index) const;
    void sellWeapon(int index) const;
    void gainArmor(int index) const;
    void sellArmor(int index) const;
    void gainSkill(int index);
    void gainPill(Pill pill, int index) const;
    void acceptTask(const Task &task);

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
    void gainMoney(int money);
    [[nodiscard]] std::vector<Skill> &getSkills();

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

private:
    std::string name;
    int level {1};
    int experience {};
    int level_up_exp {100};
    int points {};

    int max_hp {100}; // 最大的血量
    int max_mp {100}; // 最大的蓝量
    int hp {max_hp};  // 当前血量
    int mp {max_mp};  // 当前蓝量
    int health {1};   // 健康点数

    int damage {10};    // 攻击力
    double critical {}; // 暴击率
    int strength {1};   // 攻击点数

    int defence {10};  // 防御力
    double evasion {}; // 闪避率
    int agility {1};   // 闪避点数

    int money {};                   // 金钱
    const std::unique_ptr<Bag> bag; // 背包
    std::vector<Skill> skills;      // 技能
    std::vector<Task> tasks;        // 任务

    void save() const;
    bool load(Player &player);
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
    14400, 14950, 15510, 16080, 16660
};
// @formatter:on
