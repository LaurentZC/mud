#include "Skill.h"

#include "fmt/core.h"

using namespace std;

void Skill::display()
{
    fmt::print("{}\n{}\n", name, description);
    fmt::println("消耗：{}", consumption);
    if (type == Type::AGGRESSIVE) {
        fmt::println("\t伤害：{}", consumption, damage);
    }
    else if (type == Type::RESTORATIVE) {
        fmt::println("\t效果：回复{}点血量", add_hp);
    }
    else if (type == Type::GAIN) {
        fmt::println("\n效果：增加{}攻击力，增加{}暴击率，增加{}防御力", add_damage, add_critical, add_defence, add_defence);
    }
}

std::string Skill::getName() const { return name; }

int Skill::getConsumption() const { return consumption; }

int Skill::getDamage() const { return damage; }

Skill::Type Skill::getType() const { return type; }

int Skill::getAddHp() const { return add_hp; }

int Skill::getAddDefence() const { return add_defence; }

int Skill::getAddCritical() const { return add_critical; }

int Skill::getAddDamage() const { return add_damage; }

int Skill::getExistTime() const { return exist_time; }

void Skill::setExistTime(const int exist_time) { this->exist_time = exist_time; }
