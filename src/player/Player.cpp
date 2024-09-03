#include "Player.h"

#include <Helper.h>
#include <iostream>
#include <vector>
#include "fmt/core.h"

using namespace std;

void Player::showPlayer() const
{
    fmt::print("\n\n当前人物属性:\n");
    fmt::print("姓名: {} \t 等级: {}\n", name, level);
    fmt::print("经验: {} / {}\n", experience, ExpNeeded[level - 1] - ExpNeeded[level - 2]);

    print(fg(fmt::color::red), "血量: {} / {}\n", hp, max_hp);
    print(fg(fmt::color::blue), "元气: {} / {}\n", mp, max_mp);

    fmt::print("攻击力: {} \t 暴击率: {}\n", damage, critical);

    fmt::print("防御力: {} \t 闪避率: {}\n", defence);

    fmt::print("健康点数: {} \t 攻击点数: {} \t 敏捷点数: {}\n", health, strength, agility);

    fmt::print("金钱: {}\n", money);
}

void Player::checkSkill() const
{
    if (skills.begin() == skills.end()) {
        fmt::println("你没有习得任何技能！");
        return;
    }
    fmt::println("你习得的技能有：");
    int i = 0;
    for (auto it = skills.begin(); it != skills.end(); ++it, ++i) {
        fmt::print("{}. {}", i + 1, it->getName());
        if ((i + 1) % 5 == 0) {
            fmt::print("\n"); // 5个换行
        }
    }
    if (i % 5 != 0) {
        fmt::print("\n"); // 最后一行换行
    }
}

int Player::useSkill()
{
    checkSkill();
    while (true) {
        fmt::println("你想用哪个技能(请输入其编号，0是退出)：");
        int pos;
        while (true) {
            cin >> pos;
            if (pos == 0)
                return 0;
            if (0 < pos && pos < skills.size()) {
                break;
            }
            fmt::print("请输入对的编号\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (skills[pos].getConsumption() > mp) {
            fmt::println("技能释放成功!");
            swap(skills[pos], skills[0]);
            return 1;
        }
        fmt::println("元气不足，不能释放技能");
        return 0;
    }
}

void Player::usePoint()
{
    fmt::print("请选择你想要加点的选项：\n");
    while (true) {
        fmt::print("健康点数[health] \t 攻击点数 [strength] \t 敏捷点数[agility]\n");
        string choice;
        cin >> choice;
        if (choice == "health") {
            hp += 10;
            mp += 10;
            ++health;
            --points;
            break;
        }
        if (choice == "strength") {
            damage += 5;
            defence += 5;
            ++strength;
            --points;
            break;
        }
        if (choice == "agility") {
            critical += 0.01;
            evasion += 0.01;
            ++agility;
            --points;
            break;
        }
        fmt::print("输入错误，请重新输入:");
    }
}

void Player::gainWeapon(const int index) const { bag->addWeapon(Weapons[index]); }

void Player::gainArmor(const int index) const { bag->addArmor(Armors[index]); }

void Player::gainSkill(const int s) { skills.push_back(Skills[s]); }

// 当前经验
int Player::getExperience() const
{
    if (level == 1)
        return experience;
    return experience - ExpNeeded[level - 2];
}

void Player::gainExp(const int exp)
{
    experience += exp;
    const int temp_level = level;
    int skill_point = 0;
    for (int i = 0; i < 49; i++) {
        if (experience >= ExpNeeded[i] && experience < ExpNeeded[i + 1]) {
            level = i + 2;
            skill_point = level - temp_level;
        }
    }
    if (skill_point > 0) {
        fmt::println("升级了！");
        points += skill_point;
    }
}

int Player::getLevel() const { return level; }

int Player::getMaxHp() const { return max_hp; }
void Player::setMaxHp(const int max_hp) { this->max_hp = max_hp; }

int Player::getMaxMp() const { return max_mp; }
void Player::setMaxMp(const int max_mp) { this->max_mp = max_mp; }

int Player::getHp() const { return hp; }
void Player::setHp(const int hp) { this->hp = hp; }

int Player::getMp() const { return mp; }
void Player::setMp(const int mp) { this->mp = mp; }

int Player::getHealth() const { return health; }
void Player::setHealth(const int health) { this->health = health; }

int Player::getDamage() const { return damage; }
void Player::setDamage(const int damage) { this->damage = damage; }

double Player::getCritical() const { return critical; }
void Player::setCritical(const double critical) { this->critical = critical; }

int Player::getStrength() const { return strength; }
void Player::setStrength(const int strength) { this->strength = strength; }

int Player::getDefence() const { return defence; }
void Player::setDefence(const int defence) { this->defence = defence; }

double Player::getEvasion() const { return evasion; }
void Player::setEvasion(const double evasion) { this->evasion = evasion; }

int Player::getAgility() const { return agility; }
void Player::setAgility(const int agility) { this->agility = agility; }

int Player::getMoney() const { return money; }
void Player::gainMoney(const int money) { this->money += money; }

std::vector<Skill> &Player::getSkills() { return skills; }
