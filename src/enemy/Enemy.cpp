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

// @formatter:off
Enemy Enemy::creatEnemy(const int index)
{
    switch (index) {
        case 1 : return {Type::SMALL, "烈风剑士", 3, 120, 120,
                15, 0.3, 12, 60, 80,
                -1, -1, -1
            };

        case 2 : return {Type::SMALL, "地煞狂徒", 8, 200, 200,
                20, 0.3, 18, 120, 100,
                -1, -1, -1
            };

        case 3 : return {Type::SMALL, "铁壁守卫", 13, 300, 300,
                30, 0.4, 25, 200, 110,
                -1, -1, -1
            };

        case 4 : return {Type::SMALL, "黑影刺客", 17, 400, 400,
                40, 0.4, 35, 260, 120,
                -1, -1, -1
            };

        case 5 : return {Type::SMALL, "雷霆战将", 22, 550, 550,
                60, 0.5, 50, 300, 130,
                -1, -1, -1
            };

        default : return {};
    }
}

Enemy Enemy::creatElite(const int index)
{
    switch (index) {
        case 1 : return {
                Type::ELITE, "风刃卫", 10, 500, 500,
                50, 0.3, 15, 400, 40,
                -1, -1, 3
            };

        case 2 : return {Type::ELITE, "雷霆卫", 15, 700, 700,
                80, 0.3, 20, 800, 50,
                -1, -1, 5
            };

        case 3 : return {Type::ELITE, "影刃卫", 20, 900, 900,
                110, 0.4, 30, 1200, 60,
                -1, -1, 7
            };

        case 4 : return {Type::ELITE, "天霸卫", 25, 1200, 1200,
                120, 0.4, 40, 1500, 70,
                -1, -1, 8
            };

        case 5 : return {Type::ELITE, "怒焰卫", 30, 1800, 1800,
                150, 0.5, 45, 1800, 80,
                -1, -1, 9
            };

        default : return {};
    }
}

Enemy Enemy::creatBoss(const int index)
{
    switch (index) {
        case 0 : return  {
                Type::BOSS, "城主", Player.getLevel(), Player.getHp(), Player.getMaxHp(),
                Player.getDamage(), Player.getCritical(), Player.getDefence(),
                static_cast<int> (Player.getLvExp() * 0.5), 0,
                -1, -1, -1
            };
        case 1 : return {
                Type::BOSS, "陆洪", 32, 3000, 3000,
                60, 0.7, 80,
                5000, 500,
                9, 13, 13
            };

        case 2 : return {
                Type::BOSS, "段霖", 48, 5000, 5000,
                150, 0.3, 120,
                8000, 800,
                10, 14, 14
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

