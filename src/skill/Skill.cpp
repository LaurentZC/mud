#include "Skill.h"

#include <fstream>

#include "Player.h"
#include "fmt/core.h"

using namespace std;

extern Player Gamer;

void Skill::display() const
{
    print(fg(fmt::color::light_yellow), "{}\n{}\n", name, description);
    print(fg(fmt::color::light_yellow), "消耗: {}", consumption);
    if (type == Type::AGGRESSIVE) {
        print(fg(fmt::color::light_yellow), "\t伤害: {}\n", damage + Gamer.getDamage());
    }
    else if (type == Type::RESTORATIVE) {
        print(fg(fmt::color::light_yellow), "\n效果: 回复{}点血量\n", add_hp);
    }
    else if (type == Type::GAIN) {
        print(fg(fmt::color::light_yellow), "\n效果: 增加{}攻击力，增加{}暴击率，增加{}防御力\n", add_damage, add_critical, add_defence, add_defence);
    }
}

optional<int> Skill::use() const
{
    if (consumption > Gamer.getMp()) { return nullopt; }
    switch (type) {
        case Type::AGGRESSIVE :
            return damage;
        case Type::RESTORATIVE :
            Gamer.setHp(Gamer.getHp() + add_hp);
            fmt::print("你回复了{}点血量\n", add_hp);
            return 0;
        case Type::GAIN :
            Gamer.setDamage(Gamer.getDamage() + add_damage);
            Gamer.setCritical(Gamer.getCritical() + add_critical);
            Gamer.setDefence(Gamer.getDefence() + add_defence);
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

void Skill::save(ofstream &file) const
{
    file.write(reinterpret_cast<const char *>(&id), sizeof(id));
    file.close();
}

bool Skill::operator==(const Skill &other) const { return this->id == other.id; }

bool Skill::operator!=(const Skill &other) const { return !(*this == other); }
