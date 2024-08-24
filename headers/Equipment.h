#pragma once

#include <string>

// װ��
class Equipment
{
    std::string name {};        // ����
    std::string description {}; // ����
    int money {};          // ����۸�
    public:
        // װ����
    void equip();
    // ж��
    void unequip();
};

// ����
class Weapon : public Equipment
{
    int damage {};             // �˺�
    double critical {};        // ������
    int min_strength_to_equip {}; // װ������С��������Ҫ��
};

// ����
class Armor : public Equipment
{
    int defense {};    // ������
    double evasion {}; // ������
    int min_agility {}; // װ������С���ݵ���Ҫ��
};
