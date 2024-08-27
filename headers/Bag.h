#pragma once

#include <unordered_map>
#include <vector>
#include "Constant.h"
#include "Equipment.h"
#include "Player.h"

class Player;

class Bag
{
public:
    Bag();

    void display();                                     // �򿪱���չʾ��Ʒ
    void useEquipment(const Player &player);            // ѡ����Ʒʹ��
    void addArmor(const Armor &armor);                  // ��ӷ���
    void removeArmor(const Armor &armor);               // ɾ������
    void addWeapon(const Weapon &weapon);               // �������
    void removeWeapon(const Weapon &weapon);            // ɾ������
    int usePill();                                      // ʹ��Ѫƿ
    int addPill(PillType type, PillSize size, int num); // �����ƿ
private:
    std::vector<Weapon> weapons;                                                     // �����е�����
    std::vector<Armor> armors;                                                       // �����еķ���
    std::unordered_map<PillType, std::unordered_map<PillSize, int> > pill_container; // �����е�ҩƷ
};
