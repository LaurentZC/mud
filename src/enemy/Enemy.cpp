#include "Enemy.h"

#include <iostream>
#include <string>

#include "Player.h"

using namespace std;

extern Player Gamer;

Enemy::Enemy() = default;
// @formatter:off
Enemy::Enemy(const Type type, std::string name, const int level, const int hp, const int max_hp, const int damage, const double critical,
             const int defence, const int experience, const int money, const int weapon, const int armor, const int skill_id)
: type(type), name(std::move(name)), level(level), hp(hp), max_hp(max_hp), damage(damage), critical(critical), defence(defence),
experience(experience), money(money), weapon(weapon), armor(armor), skill_id(skill_id) { }
// @formatter:on

void Enemy::showEnemy() const
{
    fmt::print("\n\n");
    fmt::print("名称: {}\n", name);
    fmt::print("生命值: {} / {}\t", hp, max_hp);
    fmt::print("等级: {}\n", level);
    fmt::print("攻击: {}\t", damage);
    fmt::print("防御: {}\n", defence);
}

// @formatter:off
Enemy Enemy::creatEnemy(const array<int, 3> &pos)
{
    auto color = [](const string &text) {
        return format(fg(fmt::color::yellow), text);
    };
    if (auto &[c, x, y] = pos; c == 1) {
        if (x == 4 && (y == 2 || y == 4))
            return {Type::SMALL, color("铁壁守卫"), 15, 250, 250,
                15, 0.2, 10, 500, 100,
                -1, -1, -1
            };
        if (x == 3 && (y == 2 || y == 4))
            return {Type::SMALL, color("伏地魔"), 15, 300, 300,
                15, 0.2, 15, 500, 100,
                -1, -1, -1
            };
    }
    else if (c == 2) {
        if (x == 3 && y == 3)
            return {Type::SMALL, color("烈风剑士"), 40, 1000, 1000,
                100, 0.2, 30, 1000, 250,
                -1, -1, -1
            };

        if (x == 4 && y == 5)
            return {Type::SMALL, color("地煞狂徒"), 40, 1000, 1000,
                80, 0.3, 30, 1000,250,
                -1, -1, -1
            };

        if (x == 3 && y == 5)
            return {Type::SMALL, color("黑影刺客"), 40, 1000, 1000,
                70, 0.4, 30, 1000, 250,
                -1, -1, -1
            };
    }
    return {};
}

Enemy Enemy::creatElite(const array<int, 3> &pos)
{
    auto color = [](const string &text) {
        return format(fg(fmt::color::orange), text);
    };
    const auto &[c, x, y] = pos;
    if (c == 1 && x == 3 && y == 1)
        return {Type::ELITE, color("青龙卫"),
            20, 1000, 1000, 40, 0.3,
            50, 2000, 300,
            -1, -1, 4
        };

    if (c == 1 && x == 3 && y == 5)
        return {Type::ELITE, color("白虎卫"),
            20, 1000, 1000, 60, 0.3,
            20, 2000, 300,
            -1, -1, 7
        };

    if (c == 2 && x == 1 && y == 1)
        return {Type::ELITE, color("影刃卫"),
            45, 2000, 2000, 110, 0.4,
            30, 3000, 500,
            -1, -1, 8
        };

    if (c == 2 && x == 3 && y == 1)
        return {Type::ELITE, color("天霸卫"),
            45, 2000, 2000, 120, 0.4,
            40, 3000, 500,
            -1, -1, 9
        };

    if (c == 2 && x == 2 && y == 2)
        return {Type::ELITE, color("怒焰卫"),
            45, 1800, 1800, 120, 0.5,
            45, 3000, 500,
            -1, -1, 12
        };
    return {};
}

Enemy Enemy::creatBoss(const int index)
{
    auto color = [](const string &text) {
        return format(fg(fmt::color::gold), text);
    };
    switch (index) {
        case 0 :

            return  {
            Type::BOSS, color("城主"), Gamer.getLevel(), static_cast<int>(Gamer.getMaxHp() * 0.8), static_cast<int>(Gamer.getMaxHp() * 0.8),
            Gamer.getDamage(), Gamer.getCritical(), Gamer.getDefence(),
            static_cast<int> (Gamer.getLvExp() * 0.8), 0,
            -1, -1, -1
        };
        case 1 : return {
            Type::BOSS, color("陆洪"), 30, 3000, 3000,
            60, 0.7, 80,
            5000, 500,
            8, 12, 13
        };

        case 2 : return {
            Type::BOSS, color("段霖"), 50, 5000, 5000,
            150, 0.5, 120,
            8000, 800,
            10, 14, 14
        };
        default : return {};
    }
}
// @formatter:on

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
