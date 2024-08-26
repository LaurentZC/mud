#include "../headers/Equipment.h"

using namespace std;

#include <fmt/core.h>

#include <utility>

Equipment::Equipment() = default;
Equipment::~Equipment() = default;
Equipment::Equipment(std::string name, std::string description, const int money) : name(std::move(name)), description(std::move(description)), money(money) { }

void Weapon::showAttributes() const
{
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("伤害: {}", damage);
    fmt::println("暴击率: {}", critical);
    fmt::println("最小力量要求: {}", min_strength_to_equip);
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
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("增加的最大生命值: {}", add_max_HP);
    fmt::println("增加的最大法力值: {}", add_max_MP);
    fmt::println("最小敏捷要求: {}", min_agility_to_equipment);
}

int Weapon::getMinStrength() const { return min_strength_to_equip; }

int Armor::getMinAgility() const { return min_agility_to_equipment; }
