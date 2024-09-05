#include "Task.h"

#include <fstream>
#include <string>

#include "Player.h"
#include "fmt/core.h"

using namespace std;

extern Player Player;

Task::Task(const int id, string n, string desc, const int exp, const int m): id(id), name(std::move(n)), description(std::move(desc)), experience(exp), money(m) { }

void Task::finish()
{
    fmt::print("任务{}已完成\n", this->name);
    is_finished = true;
}

void Task::showTask()
{
    fmt::print("{} : {} \n 完成后可获得:{} 金钱 ,{} 经验\n\n", name, description, money, experience);
}

void Task::save() const
{
    ofstream out_file("../../file/" + Player.getName() + "/task.dat", ios::binary);
    out_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
}

int Task::load()
{
    ifstream in_file("../../file/" + Player.getName() + "/task.dat", ios::binary);
    int id;
    in_file.read(reinterpret_cast<char *>(&id), sizeof(id));
    return id;
}

std::string Task::getName() const { return name; }

std::string Task::getDescription() const { return description; }

int Task::getExperience() const { return experience; }

int Task::getMoney() const { return money; }

bool Task::isTaskFinished() const { return is_finished; }
