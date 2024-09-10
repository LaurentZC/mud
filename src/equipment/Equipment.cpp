#include "Equipment.h"

#include <Player.h>
#include <fstream>
#include <utility>

#include "fmt/core.h"

using namespace std;

extern Player Gamer;

// Equipment
Equipment::Equipment() = default;

Equipment::Equipment(const int id, std::string name, std::string description, const int money) : id(id), name(std::move(name)), description(std::move(description)), money(money) { }

Equipment::Equipment(const Equipment &other) = default;

Equipment::Equipment(Equipment &&other) noexcept: id(other.id), name(std::move(other.name)), description(std::move(other.description)), money(other.money) { }

Equipment &Equipment::operator=(const Equipment &other)
{
    if (this == &other)
        return *this;
    id = other.id;
    name = other.name;
    description = other.description;
    money = other.money;
    return *this;
}

Equipment &Equipment::operator=(Equipment &&other) noexcept
{
    if (this == &other)
        return *this;
    id = other.id;
    name = std::move(other.name);
    description = std::move(other.description);
    money = other.money;
    return *this;
}

Equipment::~Equipment() = default;

string Equipment::getName() const { return name; }

int Equipment::getMoney() const { return money; }

int Equipment::getId() const { return id; }

// Weapon
Weapon::Weapon() = default;

// @formatter:off
Weapon::Weapon(const int id, std::string name, std::string description, const int money,
               const int damage, const double critical, const int min_strength_to_equip)
              : Equipment(id, std::move(name), std::move(description), money),
              damage(damage), critical(critical), min_strength_to_equip(min_strength_to_equip) { }
// @formatter:on

Weapon::Weapon(const Weapon &other) = default;

Weapon::Weapon(Weapon &&other) noexcept: Equipment(std::move(other)), damage(other.damage), critical(other.critical), min_strength_to_equip(other.min_strength_to_equip) { }

Weapon &Weapon::operator=(const Weapon &other)
{
    if (this == &other)
        return *this;
    Equipment::operator =(other);
    damage = other.damage;
    critical = other.critical;
    min_strength_to_equip = other.min_strength_to_equip;
    return *this;
}

Weapon &Weapon::operator=(Weapon &&other) noexcept
{
    if (this == &other)
        return *this;
    Equipment::operator =(std::move(other));
    damage = other.damage;
    critical = other.critical;
    min_strength_to_equip = other.min_strength_to_equip;
    return *this;
}

int Weapon::getMinStrength() const { return min_strength_to_equip; }
int Weapon::getDamage() const { return damage; }
double Weapon::getCritical() const { return critical; }

void Weapon::showAttributes() const
{
    if (name.empty()) { return; }
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("伤害: {}", damage);
    fmt::println("暴击率: {}", critical);
    fmt::println("最小力量要求: {}\n", min_strength_to_equip);
}

// Armor
Armor::Armor() = default;

// @formatter:off
Armor::Armor(const int id, std::string name, std::string description, const int money,
             const int add_max_hp, const int add_max_mp, const double evasion, const int defence, const int min_agility_to_equip)
            : Equipment(id,std::move(name), std::move(description), money),
            add_max_hp(add_max_hp), add_max_mp(add_max_mp), evasion(evasion), defence(defence), min_agility_to_equip(min_agility_to_equip) { }
// @formatter:on

Armor::Armor(const Armor &other) = default;
Armor::Armor(Armor &&other) noexcept: Equipment(std::move(other)), add_max_hp(other.add_max_hp), add_max_mp(other.add_max_mp), evasion(other.evasion), defence(other.defence), min_agility_to_equip(other.min_agility_to_equip) { }

Armor &Armor::operator=(const Armor &other)
{
    if (this == &other)
        return *this;
    Equipment::operator =(other);
    add_max_hp = other.add_max_hp;
    add_max_mp = other.add_max_mp;
    evasion = other.evasion;
    defence = other.defence;
    min_agility_to_equip = other.min_agility_to_equip;
    return *this;
}

Armor &Armor::operator=(Armor &&other) noexcept
{
    if (this == &other)
        return *this;
    Equipment::operator =(std::move(other));
    add_max_hp = other.add_max_hp;
    add_max_mp = other.add_max_mp;
    evasion = other.evasion;
    defence = other.defence;
    min_agility_to_equip = other.min_agility_to_equip;
    return *this;
}

void Armor::showAttributes() const
{
    if (name.empty()) { return; }
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("增加的最大生命值: {}", add_max_hp);
    fmt::println("增加的最大法力值: {}", add_max_mp);
    fmt::println("最小敏捷要求: {}\n", min_agility_to_equip);
}

int Armor::getMinAgility() const { return min_agility_to_equip; }
int Armor::getAddMaxHp() const { return add_max_hp; }
int Armor::getAddMaxMp() const { return add_max_mp; }
double Armor::getEvasion() const { return evasion; }
int Armor::getDefence() const { return defence; }

bool Equipment::operator==(const Equipment &other) const { return this->id == other.id; }

bool Equipment::operator!=(const Equipment &other) const { return !(*this == other); }
