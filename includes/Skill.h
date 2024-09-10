#pragma once

#include <array>
#include <optional>
#include <string>

class Skill
{
public:
    enum class Type { AGGRESSIVE, RESTORATIVE, GAIN }; // 攻击型，恢复型，增益型

    Skill() = default;
    // @formatter:off
    Skill(const int id, std::string name, std::string description, const int consumption, const int damage, const Type type,
          const int add_hp, const int add_defence, const int add_critical, const int add_damage, const int exist_time)
    : id(id), name(std::move(name)), description(std::move(description)), consumption(consumption), damage(damage), type(type),
      add_hp(add_hp), add_defence(add_defence), add_critical(add_critical), add_damage(add_damage), exist_time(exist_time) { }
    // @formatter:on

    void display() const;
    [[nodiscard]] std::optional<int> use() const;

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getConsumption() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] Type getType() const;
    [[nodiscard]] int getAddHp() const;
    [[nodiscard]] int getAddDefence() const;
    [[nodiscard]] int getAddCritical() const;
    [[nodiscard]] int getAddDamage() const;
    [[nodiscard]] int getExistTime() const;
    void setExistTime(int exist_time);

    void save(std::ofstream &file) const;
    bool operator==(const Skill &other) const;
    bool operator!=(const Skill &other) const;

private:
    int id {};               // id
    std::string name;        // 名字
    std::string description; // 描述
    int consumption {};      // 耗蓝
    int damage {};           // 造成伤害，只有攻击型不是 0
    Type type;               // 0 是攻击型，1 是恢复型，2 是增益型
    int add_hp {};           // 回血回蓝，只有恢复性不是0
    int add_defence {};      // 增加攻防爆，只有增益型不是0
    int add_critical {};     // 添加的暴击率
    int add_damage {};       // 添加的攻击力
    int exist_time {};       // 持续时间
};

// @formatter:off
inline const std::array<Skill, 16> Skills = {
    {
        {0,"龙吟斩", "挥动刀刃，发出龙吟之声，震撼敌人并造成巨大伤害。",
            30, 150, Skill::Type::AGGRESSIVE, 0, 0, 0, 0, 0},
        {1, "回天神针", "以银针刺穴，迅速回复大量生命值。",
            20, 0, Skill::Type::RESTORATIVE, 100, 0, 0, 0, 0},
        {2, "无影剑", "剑法如鬼魅般无影无踪，敌人无法预判，造成致命一击。",
            25, 120, Skill::Type::AGGRESSIVE, 0, 0, 0, 0, 0},
        {3, "养心诀", "运功调息，大幅恢复生命。",
            15, 0, Skill::Type::RESTORATIVE, 250, 0, 0, 0, 0},
        {4, "金刚护体", "运用金刚功法，3回合内内大幅提高防御力。",
            20, 0, Skill::Type::GAIN, 0, 40, 0, 0, 3},
        {5, "爆裂拳", "全力一击，拳风带有爆炸力，伤害极高。",
            35, 180, Skill::Type::AGGRESSIVE, 0, 0, 0, 0, 0},
        {6, "碧血丹心", "古老丹药，服用后迅速恢复大量生命。",
            40, 0, Skill::Type::RESTORATIVE, 150, 0, 0, 0, 0},
        {7, "神龙摆尾", "快速反击，给予敌人致命的踢击。",
            28, 130, Skill::Type::AGGRESSIVE, 0, 0, 0, 0, 0},
        {8, "灵光护身", "周身散发出灵光，4回合内增强防御并提升攻击伤害。",
            25, 0, Skill::Type::GAIN, 0, 50, 20, 0, 4},
        {9, "雷霆一击", "以雷霆之势攻击敌人，造成巨大的伤害。",
            30, 160, Skill::Type::AGGRESSIVE, 0, 0, 0, 0, 0},
        {10, "铁布衫", "修炼铁布衫，5回合内增强防御力，减少受到的伤害。",
            20, 0, Skill::Type::GAIN, 0, 60, 0, 0, 5},
        {11, "风卷残云", "利用身法快速移动，带来如风般的破坏力。",
            25, 140, Skill::Type::AGGRESSIVE, 0, 0, 0, 0, 0},
        {12, "神行百变", "使出神行百变，3回合内内提升攻击力和暴击率。",
            30, 0, Skill::Type::GAIN, 0, 20, 30, 15, 3},
        {13, "寒冰掌", "掌力如寒冰般凛冽，直接攻击敌人，并有一定几率冰冻敌人。",
            30, 150, Skill::Type::AGGRESSIVE, 0, 0, 0, 0, 0},
        {14, "天罡护体", "修炼天罡护体神功，3回合内提升防御和攻击力。",
            35, 0, Skill::Type::GAIN, 0, 50, 20, 10, 3},
        {15, "全力集中", "定心安神，将注意力全部集中在攻击上，3回合内大量提升攻击力和暴击率，但是降低防御力",
            0, 0, Skill::Type::GAIN, 0, -20, 100, 20, 3}
    }
};
// @formatter:on
