#include "Player.h"
#include <iostream>
#include "fmt/core.h"

using namespace std;

void Player::openBag() const
{
    bag->display();
    fmt::println("�����ʹ��[u]ʹ�õ���/װ����[c]�ķ�ʽ�鿴����/װ�����ԡ�");
}

void Player::checkSkill()
{
    int i = 0;
    if (skills.begin() == skills.end()) {
        fmt::println("��û��ϰ���κμ��ܣ�");
        return;
    }
    fmt::println("��ϰ�õļ����У�");
    for (auto it = skills.begin(); it != skills.end(); ++it, ++i) {
        fmt::print("{}. ", i + 1);
        it->getName();
        if ((i + 1) % 5 == 0) {
            fmt::print("\n"); // 5������
        }
    }
    if (i % 5 != 0) {
        fmt::print("\n"); // ���һ�л���
    }
}

void Player::useSkill()
{
    checkSkill();
    while (true) {
        fmt::println("�������ĸ�����(���������ţ�0���˳�)��");
        int pos;
        while (true) {
            cin >> pos;
            if (pos == 0) return;
            if (0 < pos && pos < skills.size()) {
                break;
            }
            fmt::print("������Եı��\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (skills[pos].getConsumption() > getMp()) {
            fmt::println("�����ͷųɹ�!");
            swap(skills[pos], skills[0]);
        }
        else
            fmt::println("Ԫ�����㣬�����ͷż���");
    }
}

int Player::getStrength() const { return strength; }
int Player::getHp() const { return hp; }
int Player::getMp() const { return mp; }
void Player::getExperience(const int experience) { this->experience += experience; }
