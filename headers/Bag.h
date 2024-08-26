#pragma once

#include <unordered_map>
#include <vector>
#include "Equipment.h"
#include "Player.h"

class Player;

struct Pill
{
    enum class Type { BLOOD_PILL, MANA_PILL }; // ��Ѫ����������
    enum class Size { BIG, MID, SMALL };       // ���С�С��

    Type type;  // ��Ѫ/����
    Size size;  // ����С��
    int amount; // ��������
};

class Bag
{
public:
    Bag();

    void display();                                // �򿪱���չʾ��Ʒ
    void useEquipment(Player &player);             // ѡ����Ʒʹ��
    void addArmor(const Armor &armor);             //��ӷ���
    void removeArmor(const Armor &armor);          //ɾ��
    void addWeapon(const Weapon &weapon);          //���������������
    void removeWeapon(const Weapon &weapon);       //ɾ��
    int usePill();                                 //ʹ��Ѫƿ
    int addPill(Pill::Type type, Pill::Size size, int num); //�����ƿ
private:
    std::vector<Weapon> weapons;                                                         // �����е�����
    std::vector<Armor> armors;                                                           // �����еķ���
    std::unordered_map<Pill::Type, std::unordered_map<Pill::Size, int> > pill_container; // �����е�ҩƷ
};
