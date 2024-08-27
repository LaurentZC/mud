#pragma once

#include <memory>

#include "Bag.h"
#include "Skill.h"
#include "Task.h"

class Bag;

class Player
{
public:
    [[nodiscard]] int getStrength() const;

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
    // �򿪱���
    void openBag() const;

private:
    int level {1};     // �ȼ�
    int experience {}; // ����

    int hp {};      // Ѫ��
    int mp {};      // ����
    int health {1}; // ��������

    int damage {};      // ������
    double critical {}; // ������
    int strength {1};   // ��������

    int defence {};    // ������
    double evasion {}; // ������
    int agility {1};   // ���ݵ���

    int money {};                   // ��Ǯ
    const std::unique_ptr<Bag> bag; // ����
    std::vector<Task> tasks;        // �����б�
    std::vector<Skill> skills;      // �����б�
};
