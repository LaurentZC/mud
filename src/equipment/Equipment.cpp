#include "Equipment.h"

#include <Player.h>
#include <fstream>
#include <utility>

#include "fmt/core.h"

using namespace std;

extern Player Player;

// Equipment
Equipment::Equipment() = default;

Equipment::Equipment(const int id, std::string name, std::string description, const int money) : id(id), name(std::move(name)), description(std::move(description)), money(money) { }

Equipment::Equipment(Equipment &&) noexcept = default;

Equipment &Equipment::operator=(Equipment &&) noexcept = default;

Equipment::~Equipment() = default;

string Equipment::getName() const { return name; }

int Equipment::getMoney() const { return money; }


// Weapon
Weapon::Weapon() = default;

// @formatter:off
Weapon::Weapon(const int id, std::string name, std::string description, const int money,
               const int damage, const double critical, const int min_strength_to_equip)
              : Equipment(id, std::move(name), std::move(description), money),
              damage(damage), critical(critical), min_strength_to_equip(min_strength_to_equip) { }
// @formatter:on

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

int Weapon::getMinStrength() const { return min_strength_to_equip; }

void Weapon::showAttributes() const
{
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("伤害: {}", damage);
    fmt::println("暴击率: {}", critical);
    fmt::println("最小力量要求: {}", min_strength_to_equip);
}

void Weapon::save() const
{
    ofstream out_file("../../files/" + Player.getName() + "/Bag/weapon.dat", ios::binary);
    out_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
}

vector<int> Weapon::load()
{
    ifstream in_file("../../files/" + Player.getName() + "/Bag/weapon.dat", ios::binary);
    vector<int> ids;
    int id;
    while (in_file.read(reinterpret_cast<char *>(&id), sizeof(id))) {
        ids.emplace_back(id);
    }
    return ids;
}

// Armor
Armor::Armor() = default;

// @formatter:off
Armor::Armor(const int id, std::string name, std::string description, const int money,
             const int add_max_hp, const int add_max_mp, const double evasion, const int defence, const int min_agility_to_equip)
            : Equipment(id,std::move(name), std::move(description), money),
            add_max_hp(add_max_hp), add_max_mp(add_max_mp), evasion(evasion), defence(defence), min_agility_to_equip(min_agility_to_equip) { }
// @formatter:on

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
    fmt::println("最小敏捷要求: {}", min_agility_to_equip);
}

int Armor::getMinAgility() const { return min_agility_to_equip; }

void Armor::save() const
{
    ofstream out_file("../../files/" + Player.getName() + "/Bag/armor.dat", ios::binary);
    out_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
}

vector<int> Armor::load()
{
    ifstream in_file("../../files/" + Player.getName() + "/Bag/armor.dat", ios::binary);
    vector<int> ids;
    int id;
    while (in_file.read(reinterpret_cast<char *>(&id), sizeof(id))) {
        ids.emplace_back(id);
    }
    return ids;
}
