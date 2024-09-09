#pragma once

#include <string>

class Enemy
{
public:
    enum class Type { SMALL, ELITE, BOSS };

    Enemy();
    // @formatter:off
    Enemy(Type type, std::string name, int level, int hp, int max_hp, int damage, double critical, int defence,
          int experience, int money, int weapon, int armor, int skill_id);
    // @formatter:on

    void showEnemy() const; //展示怪物信息
    static Enemy creatEnemy(const std::array<int, 3> &);
    static Enemy creatElite(const std::array<int, 3> &);
    static Enemy creatBoss(int index);

    [[nodiscard]] Type getType() const;
    void setType(Type type);
    [[nodiscard]] std::string getName() const;
    void setName(const std::string &name);
    [[nodiscard]] int getLevel() const;
    void setLevel(int level);
    [[nodiscard]] int getHp() const;
    void decHp(int hp);
    [[nodiscard]] int getMaxHp() const;
    void setMaxHp(int max_hp);
    [[nodiscard]] int getDefence() const;
    void setDefence(int defence);
    [[nodiscard]] int getExperience() const;
    void setExperience(int experience);
    [[nodiscard]] int getMoney() const;
    void setMoney(int money);
    [[nodiscard]] int getDamage() const;
    void setDamage(int attack);
    [[nodiscard]] int getWeapon() const;
    void setWeapon(int weapon);
    [[nodiscard]] int getArmor() const;
    void setArmor(int armor);
    [[nodiscard]] double getCritical() const;
    void setCritical(double critical);
    [[nodiscard]] int getSkillId() const;
    void setSkillId(int skill_id);

private:
    Type type {Type::SMALL}; // 怪物类型
    std::string name;        // 怪物名字
    int level {};            // 等级

    int hp {};     // 血量
    int max_hp {}; // 满血量

    int damage {};      // 攻击力
    double critical {}; // 暴击率
    int defence {};     // 防御力

    int experience {}; // 经验值
    int money {};      // 掉落金钱

    int weapon {-1};   // 打怪掉落的物品
    int armor {-1};    // 打怪掉落的物品数量
    int skill_id {-1}; // 技能
};
