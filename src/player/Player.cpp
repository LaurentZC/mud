#include "Player.h"
#include <iostream>
#include "fmt/core.h"

using namespace std;

void Player::openBag() const
{
    bag->display();
    fmt::println("你可以使用[u]使用道具/装备，[c]的方式查看道具/装备属性。");
}

void Player::checkSkill()
{
    int i = 0;
    if (skills.begin() == skills.end()) {
        fmt::println("你没有习得任何技能！");
        return;
    }
    fmt::println("你习得的技能有：");
    for (auto it = skills.begin(); it != skills.end(); ++it, ++i) {
        fmt::print("{}. ", i + 1);
        it->getName();
        if ((i + 1) % 5 == 0) {
            fmt::print("\n"); // 5个换行
        }
    }
    if (i % 5 != 0) {
        fmt::print("\n"); // 最后一行换行
    }
}

void Player::useSkill()
{
    checkSkill();
    while (true) {
        fmt::println("你想用哪个技能(请输入其编号，0是退出)：");
        int pos;
        while (true) {
            cin >> pos;
            if (pos == 0) return;
            if (0 < pos && pos < skills.size()) {
                break;
            }
            fmt::print("请输入对的编号\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (skills[pos].getConsumption() > getMp()) {
            fmt::println("技能释放成功!");
            swap(skills[pos], skills[0]);
        }
        else
            fmt::println("元气不足，不能释放技能");
    }
}

int Player::getStrength() const { return strength; }
int Player::getHp() const { return hp; }
int Player::getMp() const { return mp; }
void Player::getExperience(const int experience) { this->experience += experience; }
