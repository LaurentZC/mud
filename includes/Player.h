#pragma once

#include <memory>

#include "Bag.h"
#include "Skill.h"
#include "Task.h"

class Bag;

class Player
{
public:
    //查看技能
    void checkSkill();
    // 用技能
    void useSkill();
    // 获得经验
    void getExperience(int experience);
    // 打开背包
    void openBag() const;
    [[nodiscard]] int getHp() const;
    [[nodiscard]] int getMp() const;
    [[nodiscard]] int getStrength() const;

    // 扣血，扣蓝，getter / setter

private:
    int level {1};     // 等级
    int experience {}; // 经验

    int max_hp {};  // 最大血量
    int max_mp {};  // 最大蓝量
    int hp {};      //当前血量
    int mp {};      // 当前蓝量
    int health {1}; // 健康点数

    int damage {};      // 攻击力
    double critical {}; // 暴击率
    int strength {1};   // 攻击点数

    int defence {};    // 防御力
    double evasion {}; // 闪避率
    int agility {1};   // 敏捷点数

    int money {};                   // 金钱
    const std::unique_ptr<Bag> bag; // 背包
    std::vector<Task> tasks;        // 任务列表
    std::vector<Skill> skills;      // 技能列表
};
