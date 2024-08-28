#pragma once

#include <string>

// װ��
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
    std::string name {};        // ����
    std::string description {}; // ����
    int money {};               // ����۸�
};

// ����
class Weapon final : public Equipment
{
public:
    Weapon();
    Weapon(int damage, int critical, int min_strength_to_equip, const std::string &name, const std::string &description, int money);

    void showName() const override;
    void showAttributes() const override;
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
    Armor();
    Armor(const std::string &name, const std::string &description, int money, int add_max_hp, int add_max_mp, int defence, double evasion, int min_agility_to_equipment);

    void showName() const override;
    void showAttributes() const override;
    [[nodiscard]] int getMinAgility() const;

private:
    int add_max_hp {};
    int add_max_mp {};
    int defence {};                  // ������
    double evasion {};               // ������
    int min_agility_to_equipment {}; // װ������С���ݵ���Ҫ��
};
