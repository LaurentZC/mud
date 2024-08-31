#pragma once

#include <memory>

#include "Bag.h"
#include "Skill.h"
#include "Task.h"

class Bag;

class Player
{
public:
    //�鿴����
    void checkSkill();
    // �ü���
    void useSkill();
    // ��þ���
    void getExperience(int experience);
    // �򿪱���
    void openBag() const;
    [[nodiscard]] int getHp() const;
    [[nodiscard]] int getMp() const;
    [[nodiscard]] int getStrength() const;

    // ��Ѫ��������getter / setter

private:
    int level {1};     // �ȼ�
    int experience {}; // ����

    int max_hp {};  // ���Ѫ��
    int max_mp {};  // �������
    int hp {};      //��ǰѪ��
    int mp {};      // ��ǰ����
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
