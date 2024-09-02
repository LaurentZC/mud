#pragma once

#include <vector>
#include "Skill.h"

class Enemy
{
public:
    // 攻击
    void attack();

private:
    int level {};      // 等级
    int hp {};         // 血量
    int damage {};     // 攻击力
    int defence {};    // 防御力
    int experience {}; // 经验值
    int money {};      // 掉落金钱
};

class Boss : public Enemy
{
public:
    // 用技能
    void useSkill();

private:
    double critical {};        // 暴击率
    double evasion {};         // 闪避率
    std::vector<Skill> skills; // 技能
};
