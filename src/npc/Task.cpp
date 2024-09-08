#include "Task.h"

#include <fstream>

#include "Player.h"
#include "fmt/core.h"

extern Player Gamer;

void Task::finish()
{
    fmt::print("任务{}已完成\n", this->name);
    if_finished = true;
}

void Task::finish(const bool if_finished) { this->if_finished = if_finished; }

void Task::showTask()
{
    print(fg(fmt::color::pink), "{}: {}\n", name, description);
    fmt::print("完成后可获得:{} 金钱 ,{} 经验\n", money, experience);
}

void Task::receive() { this->if_received = true; }

void Task::receive(const bool if_receive) { this->if_received = if_receive; }

void Task::save() const
{
    std::ofstream out_file("../files/" + Gamer.getName() + "/task.dat", std::ios::binary);
    out_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
    out_file.write(reinterpret_cast<const char *>(&if_received), sizeof(if_received));
    out_file.write(reinterpret_cast<const char *>(&if_finished), sizeof(if_finished));
}

int Task::getSkillId() const { return skill_id; }

std::string Task::getName() const { return name; }

std::string Task::getDescription() const { return description; }

int Task::getExperience() const { return experience; }

int Task::getMoney() const { return money; }

bool Task::ifTaskFinished() const { return if_finished; }

bool Task::ifReceived() const { return if_received; }

bool Task::operator==(const Task &other) const { return id == other.id; }

Task::Task() = default;

Task::Task(const int id, std::string n, std::string desc, const int exp, const int skill_id_, const int m): id(id), name(std::move(n)), description(std::move(desc)), experience(exp), skill_id(skill_id_), money(m) { }
