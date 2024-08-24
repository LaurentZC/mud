#pragma once

#include <vector>
#include "Skill.h"

class Enemy
{
    int level {};      // �ȼ�
    int HP {};         // Ѫ��
    int damage {};     // ������
    int defence {};    // ������
    int experience {}; // ����ֵ
    int money {};      // �����Ǯ

    public:
        // ����
    void attack();
};

class Boss : public Enemy
{
    double critical {};   // ������
    double evasion {};    // ������
    std::vector<Skill> skills; // ����

    public:
        // �ü���
    void useSkill();
};
