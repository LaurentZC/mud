#pragma once

#include <string>

class Skill
{
public:
    void display();
    explicit Skill(int i);
    void getName();
    [[nodiscard]] int getConsumption() const;

protected:
    std::string name;        // ����
    std::string description; // ����
    int consumption {};      // ����
    int damage {};           //����˺���ֻ�й����Ͳ���0
    int type {};             //0�ǹ����ͣ�1�ǻָ��ͣ�2��������
    int add_hp {};           //��Ѫ��ֻ�лָ��Բ���0
    int add_mp {};           // ����
    int add_defence {};      //���ӹ�������ֻ�������Ͳ���0
    int add_critical {};     // ��߱�����
    int add_damage {};       // ���ӵ��˺�
};
