#pragma once

#include "Bag.h"
#include "Skill.h"
#include "Task.h"

class Player
{
    int level {1};     // 等级
    int experience {}; // 经验

    int HP {};      // 血量
    int MP {};      // 蓝量
    int health {1}; // 健康点数

    int damage {};      // 攻击力
    double critical {}; // 暴击率
    int strength {1};   // 攻击点数

    int defence {};    // 防御力
    double evasion {}; // 闪避率
    int agility {1};   // 敏捷点数

    int money {};         // 金钱
    Bag bag;              // 背包
    std::vector<Task> tasks;   // 任务列表
    std::vector<Skill> skills; // 技能列表

    public:
        // 攻击
    void attack();
    // 1s内按回车反伤
    void defend();
    // 用技能
    void useSkill();
    // 移动
    void move();
    // 获得经验
    void getExperience();
};
