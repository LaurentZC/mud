#pragma once

#include <functional>

#include "Enemy.h"
#include "Player.h"

class Fight
{
public:
    explicit Fight(const Enemy& enemy);
    explicit Fight(Enemy&& enemy);
    void fight(const std::function<void(Player &, Enemy &)> &func = [](Player &, Enemy &) { });

private:
    std::vector<Skill> buff_skills;
    Enemy enemy;

    void attackEnemy();
    void attackPlayer(int) const;
    [[nodiscard]] bool useSkill();
    void gainTrophy() const;
};
