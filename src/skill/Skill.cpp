#include "Skill.h"

#include <fstream>

#include "Player.h"
#include "fmt/core.h"

using namespace std;

extern Player Player;

void Skill::display()
{
    fmt::print("{}\n{}\n", name, description);
    fmt::println("消耗: {}", consumption);
    if (type == Type::AGGRESSIVE) {
        fmt::println("\t伤害: {}", consumption, damage);
    }
    else if (type == Type::RESTORATIVE) {
        fmt::println("\t效果: 回复{}点血量", add_hp);
    }
    else if (type == Type::GAIN) {
        fmt::println("\n效果: 增加{}攻击力，增加{}暴击率，增加{}防御力", add_damage, add_critical, add_defence, add_defence);
    }
}

optional<int> Skill::use() const
{
    if (consumption > Player.getMp()) {
        return nullopt;
    }
    switch (type) {
        case Type::AGGRESSIVE :
            return damage;
        case Type::RESTORATIVE :
            Player.setHp(Player.getHp() + add_hp);
            fmt::print("你回复了{}点血量\n", add_hp);
            return 0;
        case Type::GAIN :
            Player.setDamage(Player.getDamage() + add_damage);
            Player.setCritical(Player.getCritical() + add_critical);
            Player.setDefence(Player.getDefence() + add_defence);
            fmt::print("你的伤害增加了{}点\n", add_damage);
            fmt::print("你的暴击率增加了{}%\n", add_critical * 100);
            fmt::print("你的防御力增加了{}点\n", add_defence);
            fmt::print("你感觉浑身充满了力量\n");
            return 0;
    }
    return 0;
}

int Skill::getId() const { return id; }

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

void Skill::save() const
{
    ofstream out_file("../../files/" + Player.getName() + "/skill.dat", ios::binary);
    out_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
}
