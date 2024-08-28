#include "Equipment.h"

using namespace std;

#include <fmt/core.h>

#include <utility>

Equipment::Equipment() = default;
Equipment::Equipment(std::string name, std::string description, const int money) : name(std::move(name)), description(std::move(description)), money(money) { }
Equipment::~Equipment() = default;
string Equipment::getName() const { return name; }
int Equipment::getMoney() const { return money; }

Weapon::Weapon() = default;
Weapon::Weapon(const int damage, const int critical, const int min_strength_to_equip, const std::string &name, const std::string &description, const int money): Equipment(name, description, money), damage(damage), critical(critical), min_strength_to_equip(min_strength_to_equip) { }

void Weapon::showAttributes() const
{
    fmt::println("����: {}", name);
    fmt::println("{}", description);
    fmt::println("�۸�: {}", money);
    fmt::println("�˺�: {}", damage);
    fmt::println("������: {}", critical);
    fmt::println("��С����Ҫ��: {}", min_strength_to_equip);
}

void Weapon::showName() const override { fmt::print("{}\n", name); }

void Armor::showName() const override { fmt::print("{}\n", name); }

Armor::Armor() = default;

Armor::Armor(const std::string &name, const std::string &description, const int money, const int add_max_hp, const int add_max_mp, const int defence, const double evasion, const int min_agility_to_equipment)
    : Equipment(name, description, money), add_max_hp(add_max_hp), add_max_mp(add_max_mp), defence(defence), evasion(evasion), min_agility_to_equipment(min_agility_to_equipment) { }

void Armor::showAttributes() const
{
    fmt::println("����: {}", name);
    fmt::println("{}", description);
    fmt::println("�۸�: {}", money);
    fmt::println("���ӵ��������ֵ: {}", add_max_hp);
    fmt::println("���ӵ������ֵ: {}", add_max_mp);
    fmt::println("��С����Ҫ��: {}", min_agility_to_equipment);
}

int Weapon::getMinStrength() const { return min_strength_to_equip; }

int Armor::getMinAgility() const { return min_agility_to_equipment; }
