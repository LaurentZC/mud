#pragma once

#include <map>
#include <unordered_map>
#include <vector>

#include "Equipment.h"
#include "Pill.h"
#include "Player.h"

class Bag
{
public:
    Bag();

    void display();                          // �򿪱���չʾ��Ʒ
    void useEquipment(const Player &player); // ѡ����Ʒʹ��
    void addArmor(const Armor &armor);       // ��ӷ���
    void removeArmor(const Armor &armor);    // ɾ������
    void addWeapon(const Weapon &weapon);    // �������
    void removeWeapon(const Weapon &weapon); // ɾ������
    void usePill();                          // ʹ��
    int addPill(Pill pill, int num);         // ���
private:
    std::vector<Weapon> weapons; // �����е�����
    std::vector<Armor> armors;   // �����еķ���
    std::map<Pill, int> pills = {
        {Pill {Pill::Type::BLOOD_PILL, Pill::Size::BIG}, 0},
        {Pill {Pill::Type::BLOOD_PILL, Pill::Size::MID}, 0},
        {Pill {Pill::Type::BLOOD_PILL, Pill::Size::SMALL}, 0},

        {Pill {Pill::Type::MANA_PILL, Pill::Size::BIG}, 0},
        {Pill {Pill::Type::MANA_PILL, Pill::Size::MID}, 0},
        {Pill {Pill::Type::MANA_PILL, Pill::Size::SMALL}, 0}
    }; // �����е�ҩƷ
};
