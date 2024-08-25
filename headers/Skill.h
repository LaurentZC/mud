#pragma once

#include <string>

class Skill
{
public:
    void display(); // չʾ
    void use(int);  // ʹ�ü���
private:
    std::string name;        // ����
    std::string description; // ����
    int consumption {};      // ����
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
