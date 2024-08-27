#pragma once

#include <string>

// װ��
class Equipment
{
public:
    Equipment();
    Equipment(std::string name, std::string description, int money);
    virtual ~Equipment();

    virtual void display() const = 0;
    [[nodiscard]] std::string getName() const { return name; }
    [[nodiscard]] int getMoney() const { return money; }

protected:
    std::string name {};        // ����
    std::string description {}; // ����
    int money {};               // ����۸�
};

// ����
class Weapon final : public Equipment
{
public:
    Weapon() = default;
    Weapon(const int damage, const int critical, const int min_strength_to_equip, const std::string &name, const std::string &description, const int money): Equipment(name, description, money), damage(damage), critical(critical), min_strength_to_equip(min_strength_to_equip) { }
    void showAttributes() const;
    void display() const override;
    [[nodiscard]] int getMinStrength() const;

private:
    int damage {};                // �˺�
    double critical {};           // ������
    int min_strength_to_equip {}; // װ������С��������Ҫ��
};

// ����
class Armor final : public Equipment
{
public:
    void showAttributes() const;
    void display() const override;
    [[nodiscard]] int getMinAgility() const;

private:
    int add_max_hp {};
    int add_max_mp {};
    int defence {};                  // ������
    double evasion {};               // ������
    int min_agility_to_equipment {}; // װ������С���ݵ���Ҫ��
};
