#include "Enemy.h"

#include <iostream>
#include <string>

#include "Player.h"

using namespace std;

extern Player Player;

Enemy::Enemy() = default;
// @formatter:off
Enemy::Enemy(const Type type, std::string name, const int level, const int hp, const int max_hp, const int damage, const double critical,
             const int defence, const int experience, const int money, const int weapon, const int armor, const int skill_id)
: type(type), name(std::move(name)), level(level), hp(hp), max_hp(max_hp), damage(damage), critical(critical), defence(defence),
experience(experience), money(money), weapon(weapon), armor(armor), skill_id(skill_id) { }
// @formatter:on

void Enemy::showEnemy() const
{
    cout << endl << "当前怪物属性:" << '\t';
    cout << "名称:" << name << '\t' << endl;
    cout << "生命值:" << hp << "/" << max_hp << '\t';
    cout << "等级:" << level << endl;
    cout << "攻击:" << damage << '\t';
    cout << "防御:" << defence << endl;
}

Enemy Enemy::creatBoss(const int index)
{
    // @formatter:off
    switch (index) {
        case 1 : return {
                Type::BOSS, "陆洪", 30, 150, 150,
                20, 0.4, 10,
                static_cast<int> (Player.getLevel() * 0.3), 50,
                6, 10, 12
            };

        case 2 : return {
                Type::BOSS, "段霖", 35, 350, 350,
                30, 0.3, 15,
                static_cast<int> (Player.getLevel() * 0.3), 80,
                7, 11, 13
            };

        case 3 : return {
                Type::BOSS, "风云", 40, 550, 550,
                50, 0.3, 50,
                static_cast<int> (Player.getLevel() * 0.3), 10,
                8, 12, 14
            };

        case 4 : return {
            Type::BOSS, "李乾坤", 45, 750, 750,
            80, 0.3, 80,
            static_cast<int> (Player.getLevel() * 0.3), 10,
            9, 13, 15
            };

        case 5 : return {
            Type::BOSS, "墨惊天", 50, 1000, 1000,
            120, 0.8, 120,
            static_cast<int> (Player.getLevel() * 0.3), 10,
            10, 14, 16
            };
        default : return {};
        // @formatter:on
    }
}

Enemy::Type Enemy::getType() const { return type; }
void Enemy::setType(const Type type) { this->type = type; }

string Enemy::getName() const { return name; }
void Enemy::setName(const string &name) { this->name = name; }

int Enemy::getLevel() const { return level; }
void Enemy::setLevel(const int level) { this->level = level; }

int Enemy::getHp() const { return hp; }
void Enemy::decHp(const int hp) { this->hp -= hp; }

int Enemy::getMaxHp() const { return max_hp; }
void Enemy::setMaxHp(const int max_hp) { this->max_hp = max_hp; }

int Enemy::getDefence() const { return defence; }
void Enemy::setDefence(const int defence) { this->defence = defence; }

int Enemy::getExperience() const { return experience; }
void Enemy::setExperience(const int experience) { this->experience = experience; }

int Enemy::getMoney() const { return money; }
void Enemy::setMoney(const int money) { this->money = money; }

int Enemy::getDamage() const { return damage; }
void Enemy::setDamage(const int attack) { this->damage = attack; }

int Enemy::getWeapon() const { return weapon; }
void Enemy::setWeapon(const int weapon) { this->weapon = weapon; }

int Enemy::getArmor() const { return armor; }
void Enemy::setArmor(const int armor) { this->armor = armor; }

double Enemy::getCritical() const { return critical; }
void Enemy::setCritical(const double critical) { this->critical = critical; }

int Enemy::getSkillId() const { return skill_id; }
void Enemy::setSkillId(const int skill_id) { this->skill_id = skill_id; }

//小怪兽
// Enemy::Enemy(int id)
// {
//     switch (id) {
//         case 1 : {
//             name = "小火焰怪";
//             hp = 100;
//             max_hp = 100;
//             damage = 10;
//             defence = 10;
//             experience = 1; //打死该怪物得到的经验
//             money = 2;      //打死该怪物得到的金钱
//             skill_id = 0;
//         }
//
//         case 2 : {
//             name = "迷雾精灵";
//             hp = 100;
//             max_hp = 100;
//             damage = 15;
//             defence = 10;
//             experience = 2; //打死该怪物得到的经验
//             money = 3;      //打死该怪物得到的金钱
//             skill_id = 0;
//         }
//
//         case 3 : {
//             name = "小任";
//             hp = 100;
//             max_hp = 100;
//             damage = 10;
//             defence = 15;
//             experience = 3; //打死该怪物得到的经验
//             money = 5;      //打死该怪物得到的金钱
//             skill_id = 0;
//         }
//
//         case 4 : {
//             name = "冰霜小鬼";
//             hp = 100;
//             max_hp = 100;
//             damage = 20;
//             defence = 20;
//             experience = 4; //打死该怪物得到的经验
//             money = 7;      //打死该怪物得到的金钱
//             skill_id = 0;
//         }
//         case 5 : {
//             name = "小牛";
//             hp = 100;
//             max_hp = 100;
//             damage = 30;
//             defence = 30;
//             experience = 5; //打死该怪物得到的经验
//             money = 9;      //打死该怪物得到的金钱
//         }
//         case 6 : {
//             name = "冰霜大怪";
//             hp = 100;
//             max_hp = 100;
//             damage = 40;
//             defence = 40;
//             experience = 6; //打死该怪物得到的经验
//             money = 11;     //打死该怪物得到的金钱
//         }
//
//         case 7 : {
//             name = "小花";
//             hp = 100;
//             max_hp = 100;
//             damage = 15;
//             defence = 20;
//             experience = 7; //打死该怪物得到的经验
//             money = 15;     //打死该怪物得到的金钱
//         }
//
//
//         default :
//             break;;
//     }
// }
