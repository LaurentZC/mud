#pragma once

#include <string>

class Skill
{
    std::string name;        // ����
    std::string description; // ����
    int consumption {}; // ����

    public:
    void display(); // չʾ
    void use(int);  // ʹ�ü���
};

class AttackSkill : public Skill
{
    int attack {}; // ������
};

class BuffSkill : public Skill
{
    int HP {}; // ��Ѫ
    int MP {}; // ����
};