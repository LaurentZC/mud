#pragma once

#include <string>

// 装备
class Equipment
{
public:
    Equipment();
    virtual ~Equipment();

    Equipment(std::string name, std::string description, int money);

    virtual void display() = 0;
    [[nodiscard]] std::string getName() const { return name; }
    [[nodiscard]] int getMoney() const { return money; }

protected:
    std::string name {};        // 名字
    std::string description {}; // 描述
    int money {};               // 购买价格
};

// 武器
class Weapon final : public Equipment
{
public:
    Weapon() = default;
    Weapon(const int damage, const int critical, const int minStrengthToEquip, const std::string &name, const std::string &description, const int money): Equipment(name, description, money), damage(damage), critical(critical), min_strength_to_equip(minStrengthToEquip) { }
    void showAttributes() const;
    void display() override;
    [[nodiscard]] int getMinStrength() const;

private:
    int damage {};                // 伤害
    double critical {};           // 暴击率
    int min_strength_to_equip {}; // 装备的最小力量点数要求
};

// 防具
class Armor final : public Equipment
{
public:
    void showAttributes() const;
    void display() override;
    [[nodiscard]] int getMinAgility() const;

private:
    int add_max_HP {};
    int add_max_MP {};
    int defence {};                  // 防御力
    double evasion {};               // 闪避率
    int min_agility_to_equipment {}; // 装备的最小敏捷点数要求
};
