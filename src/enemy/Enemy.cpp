#include "Enemy.h"

#include <iostream>
#include <string>

using namespace std;

Enemy::Enemy(const Enemy &e)
{
    name = e.name;
    level = e.level;
    hp = e.hp;
    max_hp = e.max_hp;
    attack = e.attack;
    defence = e.defence;
    experience = e.experience;
    money = e.money;
    attack = e.attack;
    armor = e.armor;
    weapon = e.weapon;
    skill_id = e.skill_id;
}

void Enemy::showEnemy() const
{
    cout << endl << "当前怪物属性:" << '\t';
    cout << "名称:" << name << '\t' << endl;
    cout << "生命值:" << hp << "/" << max_hp << '\t';
    cout << "等级:" << level << endl;
    cout << "攻击:" << attack << '\t';
    cout << "防御:" << defence << endl;
}

Enemy::Type Enemy::getType() const { return type; }
void Enemy::setType(const Type type) { this->type = type; }
string Enemy::getName() const { return name; }
void Enemy::setName(const string &name) { this->name = name; }
int Enemy::getLevel() const { return level; }
void Enemy::setLevel(const int level) { this->level = level; }
int Enemy::getHp() const { return hp; }
void Enemy::setHp(const int hp) { this->hp = hp; }
int Enemy::getMaxHp() const { return max_hp; }
void Enemy::setMaxHp(const int max_hp) { this->max_hp = max_hp; }
int Enemy::getDefence() const { return defence; }
void Enemy::setDefence(const int defence) { this->defence = defence; }
int Enemy::getExperience() const { return experience; }
void Enemy::setExperience(const int experience) { this->experience = experience; }
int Enemy::getMoney() const { return money; }
void Enemy::setMoney(const int money) { this->money = money; }
int Enemy::getAttack() const { return attack; }
void Enemy::setAttack(const int attack) { this->attack = attack; }
int Enemy::getWeapon() const { return weapon; }
void Enemy::setWeapon(const int weapon) { this->weapon = weapon; }
int Enemy::getArmor() const { return armor; }
void Enemy::setArmor(const int armor) { this->armor = armor; }
double Enemy::getCritical() const { return critical; }
void Enemy::setCritical(const double critical) { this->critical = critical; }
double Enemy::getEvasion() const { return evasion; }
void Enemy::setEvasion(const double evasion) { this->evasion = evasion; }
int Enemy::getSkillId() const { return skill_id; }
void Enemy::setSkillId(const int skill_id) { this->skill_id = skill_id; }

//小怪兽
Enemy::Enemy(int small_enemy_type)
{
    switch (small_enemy_type) {
        case 1 : {
            name = "小火焰怪";
            hp = 100;
            max_hp = 100;
            attack = 10;
            defence = 10;
            experience = 1; //打死该怪物得到的经验
            money = 2;      //打死该怪物得到的金钱
            skill_id = 0;
        }

        case 2 : {
            name = "迷雾精灵";
            hp = 100;
            max_hp = 100;
            attack = 15;
            defence = 10;
            experience = 2; //打死该怪物得到的经验
            money = 3;      //打死该怪物得到的金钱
            skill_id = 0;
        }

        case 3 : {
            name = "小任";
            hp = 100;
            max_hp = 100;
            attack = 10;
            defence = 15;
            experience = 3; //打死该怪物得到的经验
            money = 5;      //打死该怪物得到的金钱
            skill_id = 0;
        }

        case 4 : {
            name = "冰霜小鬼";
            hp = 100;
            max_hp = 100;
            attack = 20;
            defence = 20;
            experience = 4; //打死该怪物得到的经验
            money = 7;      //打死该怪物得到的金钱
            skill_id = 0;
        }
        case 5 : {
            name = "小牛";
            hp = 100;
            max_hp = 100;
            attack = 30;
            defence = 30;
            experience = 5; //打死该怪物得到的经验
            money = 9;      //打死该怪物得到的金钱
        }
        case 6 : {
            name = "冰霜大怪";
            hp = 100;
            max_hp = 100;
            attack = 40;
            defence = 40;
            experience = 6; //打死该怪物得到的经验
            money = 11;     //打死该怪物得到的金钱
        }

        case 7 : {
            name = "小花";
            hp = 100;
            max_hp = 100;
            attack = 15;
            defence = 20;
            experience = 7; //打死该怪物得到的经验
            money = 15;     //打死该怪物得到的金钱
        }


        case 8 : {
            type = Type::BOSS;
            name = "陆洪";
            hp = 150;
            max_hp = 150;
            attack = 20;
            defence = 10;
            weapon = 1;
            armor = 12;
            skill_id = 14;
            experience = 8; //打死该怪物得到的经验
            money = 30;     //打死该怪物得到的金钱
            break;
        }
        case 9 : {
            type = Type::BOSS;
            name = "段霖";
            hp = 350;
            max_hp = 350;
            attack = 30;
            defence = 15;
            weapon = 2;
            armor = 10;
            skill_id = 7;


            experience = 10; //打死该怪物得到的经验
            money = 50;      //打死该怪物得到的金钱
            break;
        }

        case 10 : {
            type = Type::BOSS;
            name = "风云";
            hp = 700;
            max_hp = 700;
            attack = 100;
            defence = 50;

            weapon = 2;
            armor = 8;
            skill_id = 8;


            experience = 10; //打死该怪物得到的经验
            money = 50;      //打死该怪物得到的金钱
            break;
        }

        case 11 : {
            type = Type::BOSS;
            name = "李乾坤";
            hp = 1000;
            max_hp = 1000;
            attack = 200;
            defence = 100;

            weapon = 4;
            armor = 10;
            skill_id = 3;

            experience = 15; //打死该怪物得到的经验
            money = 40;      //打死该怪物得到的金钱
            break;
        }

        case 12 : {
            type = Type::BOSS;
            name = "墨惊天";
            hp = 4000;
            max_hp = 4000;
            attack = 400;
            defence = 200;

            weapon = 6;
            armor = 14;
            skill_id = 5;

            experience = 15; //打死该怪物得到的经验
            money = 40;      //打死该怪物得到的金钱
            break;
        }
        default :
            break;;
    }
}
