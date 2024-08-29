#include "Equipment.h"

using namespace std;

#include <fmt/core.h>

#include <utility>

Equipment::Equipment() = default;
Equipment::Equipment(std::string name, std::string description, const int money) : name(std::move(name)), description(std::move(description)), money(money) { }
Equipment::Equipment(Equipment &&) noexcept = default;
Equipment &Equipment::operator=(Equipment &&) noexcept = default;
Equipment::~Equipment() = default;

string Equipment::getName() const { return name; }
int Equipment::getMoney() const { return money; }

Weapon::Weapon() = default;

Weapon::Weapon(const std::string &name, const std::string &description, const int money, const int damage, const int critical, const int min_strength_to_equip)
    : Equipment(name, description, money), damage(damage), critical(critical), min_strength_to_equip(min_strength_to_equip) { }

Weapon::Weapon(const Weapon &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->damage = other.damage;
    this->critical = other.critical;
    this->min_strength_to_equip = other.min_strength_to_equip;
}

Weapon &Weapon::operator=(const Weapon &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->damage = other.damage;
    this->critical = other.critical;
    this->min_strength_to_equip = other.min_strength_to_equip;
    return *this;
}

Weapon::Weapon(Weapon &&) noexcept = default;
Weapon &Weapon::operator=(Weapon &&) noexcept = default;

void Weapon::showAttributes() const
{
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("伤害: {}", damage);
    fmt::println("暴击率: {}", critical);
    fmt::println("最小力量要求: {}", min_strength_to_equip);
}

Armor::Armor() = default;

Armor::Armor(const std::string &name, const std::string &description, const int money, const int add_max_hp, const int add_max_mp, const int defence, const double evasion, const int min_agility_to_equipment)
    : Equipment(name, description, money), add_max_hp(add_max_hp), add_max_mp(add_max_mp), defence(defence), evasion(evasion), min_agility_to_equipment(min_agility_to_equipment) { }

Armor::Armor(const Armor &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->add_max_hp = add_max_hp;
    this->add_max_mp = add_max_mp;
    this->defence = defence;
    this->evasion = evasion;
}

Armor &Armor::operator=(const Armor &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->add_max_hp = add_max_hp;
    this->add_max_mp = add_max_mp;
    this->defence = defence;
    this->evasion = evasion;
    return *this;
}

Armor::Armor(Armor &&) noexcept = default;
Armor &Armor::operator=(Armor &&) noexcept = default;

void Armor::showAttributes() const
{
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("增加的最大生命值: {}", add_max_hp);
    fmt::println("增加的最大法力值: {}", add_max_mp);
    fmt::println("最小敏捷要求: {}", min_agility_to_equipment);
}

int Weapon::getMinStrength() const { return min_strength_to_equip; }

int Armor::getMinAgility() const { return min_agility_to_equipment; }
