#pragma once

#include <string>

// 装备
class Equipment
{
public:
    Equipment();
    Equipment(std::string name, std::string description, int money);
    virtual ~Equipment();

    virtual void showName() const = 0;
    virtual void showAttributes() const = 0;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getMoney() const;

protected:
    std::string name {};        // 名字
    std::string description {}; // 描述
    int money {};               // 购买价格
};

// 武器
class Weapon final : public Equipment
{
public:
    Weapon();
    Weapon(int damage, int critical, int min_strength_to_equip, const std::string &name, const std::string &description, int money);

    void showName() const override;
    void showAttributes() const override;
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
    Armor();
    Armor(const std::string &name, const std::string &description, int money, int add_max_hp, int add_max_mp, int defence, double evasion, int min_agility_to_equipment);

    void showName() const override;
    void showAttributes() const override;
    [[nodiscard]] int getMinAgility() const;

private:
    int add_max_hp {};
    int add_max_mp {};
    int defence {};                  // 防御力
    double evasion {};               // 闪避率
    int min_agility_to_equipment {}; // 装备的最小敏捷点数要求
};
