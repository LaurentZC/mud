#pragma once

#include "Enemy.h"
#include "Player.h"

class Fight
{
public:
    explicit Fight(const Enemy &enemy);
    bool fight();

private:
    std::vector<Skill> buff_skills;
    Enemy enemy;

    void attackEnemy();
    void attackPlayer(int) const;
    void useSkill() const;
    void gainTrophy() const;
};
