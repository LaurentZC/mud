#pragma once

#include "Bag.h"
#include "Skill.h"
#include "Task.h"

class Player
{
    int level {1};     // �ȼ�
    int experience {}; // ����

    int HP {};      // Ѫ��
    int MP {};      // ����
    int health {1}; // ��������

    int damage {};      // ������
    double critical {}; // ������
    int strength {1};   // ��������

    int defence {};    // ������
    double evasion {}; // ������
    int agility {1};   // ���ݵ���

    int money {};         // ��Ǯ
    Bag bag;              // ����
    std::vector<Task> tasks;   // �����б�
    std::vector<Skill> skills; // �����б�

    public:
        // ����
    void attack();
    // 1s�ڰ��س�����
    void defend();
    // �ü���
    void useSkill();
    // �ƶ�
    void move();
    // ��þ���
    void getExperience();
};
