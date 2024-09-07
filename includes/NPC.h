#pragma once

#include <map>
#include <vector>

#include "Equipment.h"
#include "Pill.h"
#include "Task.h"

class NPC
{
public:
    NPC() = default;
    virtual ~NPC() = default;
    virtual void talk() = 0;

protected:
    std::string name;        // 名字
    std::string description; // 描述特征
    std::string dialogue;    // 对白
};

class TaskGivingNPC final : public NPC
{
public:
    void talk() override;

private:
    void giveTask() const;
    void giveReward() const;
    [[nodiscard]] bool ifFinishTask() const;
    Task task {};
    bool if_first_talk = true;  //是否发布任务
    bool if_give_reward = true; //是否给予奖励
};

class ShopKeeper final : public NPC
{
public:
    void talk() override;
    [[nodiscard]] int getPillNum(const Pill &pill) const;

private:
    void showGoods();
    void buy();
    void sell();
    void enterStore();
    void buyPills() const;
    void buyWeapon();
    void buyArmor();
    void sellArmor();
    void sellWeapon();

    std::vector<Weapon> weapons;
    std::vector<Armor> armors;
    // @formatter:off
    std::map<Pill, int> pills = {
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::BIG}, 0},
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::MID}, 0},
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::SMALL}, 0},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::BIG}, 0},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::MID}, 0},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::SMALL}, 0}
    };
    // @formatter:on
};
