#pragma once

#include <string>

// װ��
class Equipment
{
public:
    Equipment();
    Equipment(std::string name, std::string description, int money);
    Equipment(Equipment &&) noexcept;
    Equipment &operator=(Equipment &&) noexcept;
    virtual ~Equipment();

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
    explicit Weapon(int i);
    Weapon(const Weapon &other);
    Weapon &operator=(const Weapon &other);
    Weapon(Weapon &&) noexcept;
    Weapon &operator=(Weapon &&) noexcept;

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
    explicit Armor(int i);
    Armor(const Armor &other);
    Armor &operator=(const Armor &other);
    Armor(Armor &&) noexcept;
    Armor &operator=(Armor &&) noexcept;

    void showAttributes() const override;
    [[nodiscard]] int getMinAgility() const;

private:
    int add_max_hp {};
    int add_max_mp {};
    int defence {};              // ������
    double evasion {};           // ������
    int min_agility_to_equip {}; // װ������С���ݵ���Ҫ��
};
