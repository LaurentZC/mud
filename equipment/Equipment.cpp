#include "../headers/Equipment.h"

using namespace std;

#include <fmt/core.h>

#include <utility>

Equipment::Equipment() = default;
Equipment::~Equipment() = default;
Equipment::Equipment(std::string name, std::string description, const int money) : name(std::move(name)), description(std::move(description)), money(money) { }

void Weapon::showAttributes() const
{
    fmt::println("����: {}", name);
    fmt::println("{}", description);
    fmt::println("�۸�: {}", money);
    fmt::println("�˺�: {}", damage);
    fmt::println("������: {}", critical);
    fmt::println("��С����Ҫ��: {}", min_strength_to_equip);
}


void Weapon::display()
{
    fmt::println("{}", name);
}

void Armor::display()
{
    fmt::println("{}", name);
}

void Armor::showAttributes() const
{
    fmt::println("����: {}", name);
    fmt::println("{}", description);
    fmt::println("�۸�: {}", money);
    fmt::println("���ӵ��������ֵ: {}", add_max_HP);
    fmt::println("���ӵ������ֵ: {}", add_max_MP);
    fmt::println("��С����Ҫ��: {}", min_agility_to_equipment);
}

int Weapon::getMinStrength() const { return min_strength_to_equip; }

int Armor::getMinAgility() const { return min_agility_to_equipment; }
