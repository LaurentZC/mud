#pragma once

#include <vector>
#include "Equipment.h"

class Bag
{
public:
    void display(); // �򿪱���չʾ��Ʒ
    void use(int);  // ѡ����Ʒʹ��
private:
    std::vector<Weapon> weapons; // �����е�����
    std::vector<Armor> armors;   // �����еķ���
};
