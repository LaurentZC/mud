#include "Task.h"

#include <fstream>

#include "Player.h"
#include "fmt/core.h"

extern Player Player;

void Task::finish()
{
    fmt::print("任务{}已完成\n", this->name);
    if_finished = true;
}

void Task::showTask()
{
    fmt::print("{} : {} \n 完成后可获得:{} 金钱 ,{} 经验", name, description, money, experience);
}

void Task::save() const
{
    std::ofstream out_file("../../files/" + Player.getName() + "/task.dat", std::ios::binary);
    out_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
}

int Task::getSkillId() const { return skill_id; }

std::string Task::getName() const { return name; }

std::string Task::getDescription() const { return description; }

int Task::getExperience() const { return experience; }

int Task::getMoney() const { return money; }

bool Task::ifTaskFinished() const { return if_finished; }

Task::Task() = default;
Task::Task(const int id, std::string n, std::string desc, const int exp, const int skill_id_, const int m): id(id), name(std::move(n)), description(std::move(desc)), experience(exp), skill_id(skill_id_), money(m) { }
