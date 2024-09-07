#pragma once

#include <array>
#include <string>
#include <utility>

class Task
{
public:
    Task();
    Task(int id, std::string n, std::string desc, int exp, int skill_id_, int m);
    // 完成任务
    void finish();
    void showTask();
    void save() const;
    [[nodiscard]] int getSkillId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] int getExperience() const;
    [[nodiscard]] int getMoney() const;
    [[nodiscard]] bool ifTaskFinished() const;

    bool operator==(const Task &other) const;

private:
    int id {};                // id
    std::string name;         // 名字
    std::string description;  // 任务描述
    int experience {};        // 完成后的经验
    int skill_id {};          // 获得的技能Id
    int money {};             // 钱
    bool if_finished = false; // 是否完成
};

// @formatter:off
inline const std::array<Task, 4> Tasks = {
    {
        {0, "寻找失落的宝藏", "在古老的森林中寻找传说中的失落宝藏。你需要找到隐藏在树木之间的宝箱，并带回村庄。",
            150, 1, 50},
        {1, "击败森林守卫", "森林中出现了一只强大的守卫，威胁着村庄的安全。前往森林深处，击败这只守卫，保护村庄。",
            200, 4, 75,},
        {2, "收集草药", "村庄的医生需要一些稀有草药来治疗生病的村民。前往附近的山丘，收集五种不同的草药并带回给医生。",
            100, 6, 30},
        {3, "护送商人", "一位商人需要安全地穿越危险的道路前往邻近的城镇。护送他并确保他安全到达。",
            250, 15, 100}
    }
};
// @formatter:on
