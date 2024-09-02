#include "Skill.h"

#include "fmt/core.h"

using namespace std;

Skill::Skill(int i)
{
    switch (i) {
        case 0:
            name = "龙吟斩";
            description = "挥动刀刃，发出龙吟之声，震撼敌人并造成巨大伤害。";
            consumption = 30;
            damage = 150;
            type = 0; // 攻击型
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 1:
            name = "回天神针";
            description = "以银针刺穴，迅速回复大量生命值。";
            consumption = 20;
            damage = 0;
            type = 1; // 恢复型
            add_hp = 100;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 2:
            name = "无影剑";
            description = "剑法如鬼魅般无影无踪，敌人无法预判，造成致命一击。";
            consumption = 25;
            damage = 120;
            type = 0; // 攻击型
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 3:
            name = "养心诀";
            description = "运功调息，逐步恢复生命与法力。";
            consumption = 15;
            damage = 0;
            type = 1; // 恢复型
            add_hp = 50;
            add_mp = 30;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 4:
            name = "金刚护体";
            description = "运用金刚功法，短时间内大幅提高防御力。";
            consumption = 20;
            damage = 0;
            type = 2; // 增益型
            add_hp = 0;
            add_mp = 0;
            add_defence = 40;
            add_damage = 0;
            add_critical = 0;
            break;
        case 5:
            name = "爆裂拳";
            description = "全力一击，拳风带有爆炸力，伤害极高。";
            consumption = 35;
            damage = 180;
            type = 0; // 攻击型
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 6:
            name = "碧血丹心";
            description = "古老丹药，服用后迅速恢复大量生命与法力。";
            consumption = 40;
            damage = 0;
            type = 1; // 恢复型
            add_hp = 150;
            add_mp = 50;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 7:
            name = "神龙摆尾";
            description = "快速反击，给予敌人致命的尾击。";
            consumption = 28;
            damage = 130;
            type = 0; // 攻击型
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 8:
            name = "灵光护身";
            description = "周身散发出灵光，增强防御并短暂提升攻击伤害。";
            consumption = 25;
            damage = 0;
            type = 2; // 增益型
            add_hp = 0;
            add_mp = 0;
            add_defence = 50;
            add_damage = 20;
            add_critical = 0;
            break;
        case 9:
            name = "雷霆一击";
            description = "以雷霆之势攻击敌人，造成巨大的伤害。";
            consumption = 30;
            damage = 160;
            type = 0; // 攻击型
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 10:
            name = "清心咒";
            description = "清除心中杂念，快速恢复法力。";
            consumption = 10;
            damage = 0;
            type = 1; // 恢复型
            add_hp = 0;
            add_mp = 80;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 11:
            name = "铁布衫";
            description = "修炼铁布衫，增强防御力，减少受到的伤害。";
            consumption = 20;
            damage = 0;
            type = 2; // 增益型
            add_hp = 0;
            add_mp = 0;
            add_defence = 60;
            add_damage = 0;
            add_critical = 0;
            break;
        case 12:
            name = "风卷残云";
            description = "利用身法快速移动，带来如风般的破坏力。";
            consumption = 25;
            damage = 140;
            type = 0; // 攻击型
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 13:
            name = "神行百变";
            description = "使出神行百变，短时间内提升攻击力和暴击率。";
            consumption = 30;
            damage = 0;
            type = 2; // 增益型
            add_hp = 0;
            add_mp = 0;
            add_defence = 20;
            add_damage = 30;
            add_critical = 15;
            break;
        case 14:
            name = "寒冰掌";
            description = "掌力如寒冰般凛冽，直接攻击敌人，并有一定几率冰冻敌人。";
            consumption = 30;
            damage = 150;
            type = 0; // 攻击型
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 15:
            name = "天罡护体";
            description = "修炼天罡护体神功，提升防御和攻击力，增加战斗持续时间。";
            consumption = 35;
            damage = 0;
            type = 2; // 增益型
            add_hp = 0;
            add_mp = 0;
            add_defence = 50;
            add_damage = 20;
            add_critical = 10;
            break;
        case 16:
            name = "全力集中";
            description = "定心安神，将注意力全部集中在攻击上，大量提升攻击力和暴击率，"
                    "但是降低防御力";
            consumption = 0;
            damage = 0;
            type = 0;
            add_hp = 0;
            add_mp = 0;
            add_defence = -20;
            add_damage = 40;
            add_critical = 20;
            break;
        default:
            break;
    }
}

void Skill::display()
{
    if (type == 0) {
        fmt::print("{}\n{}\n", name, description);
        fmt::print("消耗：{}，伤害：{}\n", consumption, damage);
    }
    else if (type == 1) {
        fmt::print("{}\n{}\n", name, description);
        fmt::print("消耗：{}\n", consumption);
        fmt::print("效果：回复{}点血量，回复{}点元气\n", add_hp, add_mp);
    }
    else if (type == 2) {
        fmt::print("{}\n{}\n", name, description);
        fmt::print("消耗：{}\n", consumption);
        fmt::print("效果：增加{}攻击力，增加{}暴击率，增加{}防御力\n",
                   add_damage, add_critical, add_defence, add_defence);
    }
}

void Skill::getName() { fmt::print("{}", name); }

int Skill::getConsumption() const { return consumption; }
