#pragma once

#include <string>

// װ��
class Equipment
{
public:
    // װ����
    void equip();
    // ж��
    void unequip();

private:
    std::string name {};        // ����
    std::string description {}; // ����
    int money {};               // ����۸�
};

// ����
class Weapon : public Equipment
{
    int damage {};                // �˺�
    double critical {};           // ������
    int min_strength_to_equip {}; // װ������С��������Ҫ��
};

// ����
class Armor : public Equipment
{
    int defense {};     // ������
    double evasion {};  // ������
    int min_agility {}; // װ������С���ݵ���Ҫ��
};
