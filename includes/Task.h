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
    void finish(bool if_finished);
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
    int id {};               // id
    std::string name;        // 名字
    std::string description; // 任务描述
    int experience {};       // 完成后的经验
    int skill_id {};         // 获得的技能Id
    int money {};            // 钱
    bool if_finished {};     // 是否完成
};

// @formatter:off
inline const std::array<Task, 15> Tasks = {
    {
        {0, "寻找人参草", "给老张在城中找到一株人参草",
            150, 1, 200},
        {1, "寻找定神丹", "给老张找到一颗定神丹",
            240,6 , 500},
        {2, "一剑封喉，为民除害", "江湖百姓苦陆洪已久，杀了他为民除害",
            800, 3, 800},
        {3, "找回货物", "去武威城帮老张取回货物",
            600, -1, 1500},
    }
};
// @formatter:on
