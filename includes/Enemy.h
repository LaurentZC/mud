#pragma once

#include <string>

using namespace std;

class Enemy
{
public:
    enum class Type { SMALL, ELITE, BOSS };

    Enemy(const Enemy &e);

    explicit Enemy(int small_enemy_type);

    void showEnemy() const; //展示怪物信息

    [[nodiscard]] Type getType() const;
    void setType(Type type);
    [[nodiscard]] string getName() const;
    void setName(const string &name);
    [[nodiscard]] int getLevel() const;
    void setLevel(int level);
    [[nodiscard]] int getHp() const;
    void setHp(int hp);
    [[nodiscard]] int getMaxHp() const;
    void setMaxHp(int max_hp);
    [[nodiscard]] int getDefence() const;
    void setDefence(int defence);
    [[nodiscard]] int getExperience() const;
    void setExperience(int experience);
    [[nodiscard]] int getMoney() const;
    void setMoney(int money);
    [[nodiscard]] int getAttack() const;
    void setAttack(int attack);
    [[nodiscard]] int getWeapon() const;
    void setWeapon(int weapon);
    [[nodiscard]] int getArmor() const;
    void setArmor(int armor);
    [[nodiscard]] double getCritical() const;
    void setCritical(double critical);
    [[nodiscard]] double getEvasion() const;
    void setEvasion(double evasion);
    [[nodiscard]] int getSkillId() const;
    void setSkillId(int skill_id);

private:
    Type type {Type::SMALL}; // 怪物类型
    string name {};          // 怪物名字
    int level {};            // 等级
    int hp {};               // 血量
    int max_hp {};           // 满血量
    int defence {};          // 防御力
    int experience {};       // 经验值
    int money {};            // 掉落金钱
    int attack {};           // 攻击力
    int weapon {};           // 打怪掉落的物品
    int armor {};            // 打怪掉落的物品数量
    double critical {};      // 暴击率
    double evasion {};       // 闪避率
    int skill_id {};         // 技能
};
