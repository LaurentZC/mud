#pragma once

#include <vector>
#include "Equipment.h"

class Bag
{
    std::vector<Weapon> weapons; // �����е�����
    std::vector<Armor> armors;   // �����еķ���

    public:
    void display(); // �򿪱���չʾ��Ʒ
    void use(int);  // ѡ����Ʒʹ��
};
