#pragma once

#include <string>

class Skill
{
    std::string name;        // 名字
    std::string description; // 描述
    int consumption {}; // 耗蓝

    public:
    void display(); // 展示
    void use(int);  // 使用技能
};

class AttackSkill : public Skill
{
    int attack {}; // 攻击力
};

class BuffSkill : public Skill
{
    int HP {}; // 加血
    int MP {}; // 加蓝
};