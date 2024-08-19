//
// Created by 32186 on 19/8/2024.
//

#pragma once
#include <vector>
#include "../SmallClasses/Skill.h"

using namespace std;

class Enemy
{
    int level {};      // 等级
    int HP {};         // 血量
    int damage {};     // 攻击力
    int defence {};    // 防御力
    int experience {}; // 经验值
    int money {};      // 掉落金钱

public:
    // 攻击
    void attack();
};

class Boss : public Enemy
{
    double critical {};   // 暴击率
    double evasion {};    // 闪避率
    vector<Skill> skills; // 技能

public:
    // 用技能
    void useSkill();
};
