#pragma once

#include "Enemy.h"
#include "Player.h"

class Fight
{
public:
    explicit Fight(Enemy &enemy);
    static int calculateDamage(int damage, int defence);
    void gainTrophy() const;

private:
    std::vector<Skill> buff_skills;
    Enemy enemy;
};
