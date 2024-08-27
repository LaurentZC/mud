#pragma once

#include <vector>
#include "Skill.h"

class Enemy
{
public:
    // ����
    void attack();

private:
    int level {};      // �ȼ�
    int hp {};         // Ѫ��
    int damage {};     // ������
    int defence {};    // ������
    int experience {}; // ����ֵ
    int money {};      // �����Ǯ
};

class Boss : public Enemy
{
public:
    // �ü���
    void useSkill();

private:
    double critical {};        // ������
    double evasion {};         // ������
    std::vector<Skill> skills; // ����
};
