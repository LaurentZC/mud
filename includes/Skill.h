#pragma once

#include <string>

class Skill
{
public:
    void display();
    explicit Skill(int i);
    void getName();
    [[nodiscard]] int getConsumption() const;

protected:
    std::string name;        // 名字
    std::string description; // 描述
    int consumption {};      // 耗蓝
    int damage {};           //造成伤害，只有攻击型不是0
    int type {};             //0是攻击型，1是恢复型，2是增益型
    int add_hp {};           //回血，只有恢复性不是0
    int add_mp {};           // 回蓝
    int add_defence {};      //增加攻防爆，只有增益型不是0
    int add_critical {};     // 提高暴击率
    int add_damage {};       // 增加的伤害
};
