#pragma once

#include <map>
#include <vector>
#include "Equipment.h"
#include "Player.h"

class Player;

class Bag
{
public:
    Bag();
    void display();                                       // �򿪱���չʾ��Ʒ
    void useEquipment(Player &player);                    // ѡ����Ʒʹ��
    void addArmor(const Armor &armor);                    //��ӷ���
    void removeArmor(const Armor &armor);                 //ɾ��
    void addWeapon(const Weapon &weapon);                 //���������������
    void removeWeapon(const Weapon &weapon);              //ɾ��
    int useBloodPotion();                                 //ʹ��Ѫƿ
    int useManaPotion();                                  //ʹ����ƿ
    int addBloodPotion(const std::string &type, int num); //���Ѫƿ
    int addManaPotion(const std::string &type, int num);  //�����ƿ
private:
    friend Player;
    std::vector<Weapon> weapons;                                                      // �����е�����
    std::vector<Armor> armors;                                                        // �����еķ���
    std::map<std::string, int> blood_potion = {{"big", 0}, {"mid", 0}, {"small", 0}}; //Ѫƿ��������
    std::map<std::string, int> mana_potion = {{"big", 0}, {"mid", 0}, {"small", 0}};; //��ƿ��������s
};
