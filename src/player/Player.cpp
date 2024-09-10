#include "Player.h"

#include <NPC.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <io.h>
#include <iostream>
#include <vector>

#include "fmt/core.h"

using namespace std;

extern Player Gamer;

void Player::acceptTask(const Task &task) { tasks.push_back(task); }

void Player::finishTask(const Task &task)
{
    if (const auto it = find(tasks.begin(), tasks.end(), task); it != tasks.end())
        it->finish(true);
}

void Player::showPlayer() const
{
    fmt::print("姓名: {} \t 等级: {}\n", name, level);
    fmt::print("经验: {} / {}\n", experience - ExpNeeded[level - 1], level_up_exp);

    print(fg(fmt::color::red), "血量: {} / {}\n", hp, max_hp);
    print(fg(fmt::color::blue), "元气: {} / {}\n", mp, max_mp);

    fmt::print("攻击力: {} \t 暴击率: {:.3f}\n", damage, critical);

    fmt::print("防御力: {} \t 闪避率: {:.3f}\n", defence, evasion);

    fmt::print("健康点数: {} \t 攻击点数: {} \t 敏捷点数: {}\n", health, strength, agility);

    print(fg(fmt::color::gold), "金钱: {}\n", money);

    print(fg(fmt::color::gold), "可用属性点: {}\n\n", points);
}

bool Player::checkSkill() const
{
    if (skills.begin() == skills.end()) {
        return false;
    }
    fmt::println("你习得的技能有: ");

    int i = 1;
    for (const auto &skill : skills) {
        fmt::print("{}. ", i);
        skill.display();
        ++i;
    }

    return true;
}

void Player::checkTask() const
{
    if (tasks.begin() == tasks.end()) {
        fmt::print("你当前没有任务。\n");
        return;
    }
    for (const auto &task : tasks) { task.showTask(); }
}

void Player::openBag()
{
    system("cls");
    fmt::print("你想要做什么[check]查看背包，[equip]更改装备, [pill]服用药品, [out]退出:");
    string choice;
    cin >> choice;
    while (choice != "pill" && choice != "equip" && choice != "check" && choice != "out") {
        fmt::print("无效指令！");
        cin >> choice;
    }
    if (choice == "pill") { bag.usePill(); }
    else if (choice == "equip") { bag.useEquipment(); }
    else
        if (choice == "check") { bag.display(); }
}

void Player::showBag() { bag.display(); }

void Player::usePoint()
{
    while (points > 0) {
        system("cls");
        showPlayer();
        fmt::print("请选择你想要加点的选项: \n");
        fmt::print("健康点数[health] \t 攻击点数 [strength] \t 敏捷点数[agility]\t 退出[out]\n");
        string choice;
        cin >> choice;
        if (choice == "health") {
            max_hp += 100;
            max_mp += 100;
            hp = max_hp;
            mp = max_mp;
            ++health;
            --points;
            continue;
        }
        if (choice == "strength") {
            damage += 20;
            defence += 20;
            ++strength;
            --points;
            continue;
        }
        if (choice == "agility") {
            critical += 0.01;
            evasion += 0.01;
            ++agility;
            --points;
            continue;
        }
        if (choice == "out") { break; }
        fmt::print("输入错误，请重新输入: ");
    }
}

void Player::usePill() { bag.usePill(); }

void Player::gainSkill(const int index)
{
    if (index == -1)
        return;
    skills.push_back(Skills[index]);
}

void Player::removeTask(const Task &task) { tasks.erase(remove(tasks.begin(), tasks.end(), task), tasks.end()); }

int Player::gainPill(const Pill pill, const int index)
{
    const int num = bag.addPill(pill, index);
    return num;
}

void Player::gainWeapon(const int index)
{
    if (index == -1)
        return;
    bag.addWeapon(Weapons[index]);
    fmt::println("获得了{}", Weapons[index].getName());
}

void Player::gainArmor(const int index)
{
    if (index == -1)
        return;
    bag.addArmor(Armors[index]);
    fmt::println("获得了{}", Armors[index].getName());
}

string Player::getName() const { return name; }
void Player::setName(const string &name) { this->name = name; }

// level ~ level + 1 总经验
int Player::getLvExp() const { return ExpNeeded[level] - ExpNeeded[level - 1]; }

void Player::gainExp(const int exp)
{
    experience += exp;
    const int temp_level = level;
    const auto it = lower_bound(ExpNeeded.begin(), ExpNeeded.end(), experience);
    const size_t index = distance(ExpNeeded.begin(), it);
    level = static_cast<int>(index);
    points += level - temp_level;
    print(fg(fmt::color::green), "{} \t {} \t", name, level);
    print(fg(fmt::color::green), "{} / {}\n", experience - *(it - 1), level_up_exp);
    if (points > 0) {
        level_up_exp = ExpNeeded[level] - ExpNeeded[level - 1];
        fmt::print("恭喜，你升到了{}级！\n", level);
        fmt::print("你有{}点技能点可用，请及时查看！\n", points);
    }
}

int Player::getMaxHp() const { return max_hp; }
void Player::setMaxHp(const int max_hp) { this->max_hp = max_hp; }
int Player::getMaxMp() const { return max_mp; }
void Player::setMaxMp(const int max_mp) { this->max_mp = max_mp; }
int Player::getHp() const { return hp; }

void Player::setHp(const int hp)
{
    if (hp > max_hp) {
        this->hp = max_hp;
        return;
    }
    this->hp = hp;
}

int Player::getMp() const { return mp; }

void Player::setMp(const int mp)
{
    if (mp > max_mp) {
        this->mp = max_mp;
        return;
    }
    if (mp <= 0) {
        this->mp = 0;
        return;
    }
    this->mp = mp;
}

int Player::getHealth() const { return health; }
void Player::setHealth(const int health) { this->health = health; }

void Player::buyArmor(const Armor &armor) { bag.addArmor(armor); }

void Player::buyWeapon(const Weapon &weapon) { bag.addWeapon(weapon); }

void Player::sellArmor(const Armor &armor) { bag.removeArmor(armor); }

void Player::sellWeapon(const Weapon &weapon) { bag.removeWeapon(weapon); }

void Player::removeArmor(const Armor &armor)
{
    max_hp -= armor.getAddMaxHp();
    max_mp -= armor.getAddMaxMp();
    defence -= armor.getDefence();
    evasion -= armor.getEvasion();
}

void Player::removeWeapon(const Weapon &weapon)
{
    damage -= weapon.getDamage();
    critical -= weapon.getCritical();
}

void Player::equipArmor(const Armor &armor)
{
    max_hp += armor.getAddMaxHp();
    max_mp += armor.getAddMaxMp();
    defence += armor.getDefence();
    evasion += armor.getEvasion();
}


void Player::equipWeapon(const Weapon &weapon)
{
    damage += weapon.getDamage();
    critical += weapon.getCritical();
}

int Player::getLevel() const { return level; }

int Player::getDamage() const { return damage; }

void Player::setDamage(const int damage) { this->damage = damage; }

double Player::getCritical() const { return critical; }

void Player::setCritical(const double critical) { this->critical = critical; }

int Player::getStrength() const { return strength; }

void Player::setStrength(const int strength) { this->strength = strength; }

int Player::getDefence() const { return defence; }

void Player::setDefence(const int defence) { this->defence = defence; }

double Player::getEvasion() const { return evasion; }

void Player::setEvasion(const double evasion) { this->evasion = evasion; }

int Player::getAgility() const { return agility; }

void Player::setAgility(const int agility) { this->agility = agility; }

int Player::getMoney() const { return money; }

int Player::getPoints() const { return points; }

void Player::gainMoney(const int money) { this->money += money; }

void Player::addPoints(const int points) { this->points += points; }

vector<Skill> &Player::getSkills() { return skills; }

std::vector<Weapon> &Player::getWeapons() { return bag.getWeapons(); }

std::vector<Armor> &Player::getArmors() { return bag.getArmors(); }

void Player::save() const
{
    // 玩家创建一个新的文件夹
    const string folder_path = "../files/" + name;
    filesystem::create_directories(folder_path);
    //创建了一个fileToPlayer的文件输出流对象，以二进制写入SavePlayer.txt
    ofstream out_file(folder_path + "/Player.dat", ios::binary);

    if (!out_file.is_open()) {
        fmt::print("保存失败！\n");
    }
    // 保存 name 长度和内容
    const size_t name_length = name.size();
    out_file.write(reinterpret_cast<const char *>(&name_length), sizeof(name_length));
    out_file.write(name.c_str(), static_cast<long long>(name_length));

    // 将玩家信息写入 Player.dat
    out_file.write(reinterpret_cast<const char *>(&position[0]), sizeof(position[0]));
    out_file.write(reinterpret_cast<const char *>(&position[1]), sizeof(position[1]));
    out_file.write(reinterpret_cast<const char *>(&position[2]), sizeof(position[2]));
    out_file.write(reinterpret_cast<const char *>(&finished[0]), sizeof(finished[0]));
    out_file.write(reinterpret_cast<const char *>(&finished[1]), sizeof(finished[1]));
    out_file.write(reinterpret_cast<const char *>(&level), sizeof(level));
    out_file.write(reinterpret_cast<const char *>(&experience), sizeof(experience));
    out_file.write(reinterpret_cast<const char *>(&level_up_exp), sizeof(level_up_exp));
    out_file.write(reinterpret_cast<const char *>(&points), sizeof(points));
    out_file.write(reinterpret_cast<const char *>(&max_hp), sizeof(max_hp));
    out_file.write(reinterpret_cast<const char *>(&max_mp), sizeof(max_mp));
    out_file.write(reinterpret_cast<const char *>(&hp), sizeof(hp));
    out_file.write(reinterpret_cast<const char *>(&mp), sizeof(mp));
    out_file.write(reinterpret_cast<const char *>(&health), sizeof(health));
    out_file.write(reinterpret_cast<const char *>(&damage), sizeof(damage));
    out_file.write(reinterpret_cast<const char *>(&critical), sizeof(critical));
    out_file.write(reinterpret_cast<const char *>(&strength), sizeof(strength));
    out_file.write(reinterpret_cast<const char *>(&defence), sizeof(defence));
    out_file.write(reinterpret_cast<const char *>(&evasion), sizeof(evasion));
    out_file.write(reinterpret_cast<const char *>(&agility), sizeof(agility));
    out_file.write(reinterpret_cast<const char *>(&money), sizeof(money));
    out_file.close();
    //向文件中写入数据，将skill类型的类型数据转换成char类型的指针
    ofstream skill_file("../files/" + Gamer.getName() + "/skill.dat", ios::binary);
    if (!skills.empty()) {
        int size = static_cast<int>(skills.size());
        skill_file.write(reinterpret_cast<const char *>(&size), sizeof(size));
        for (const auto &skill : skills) {
            int id = skill.getId();
            skill_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
        }
    }
    std::ofstream task_file("../files/" + Gamer.getName() + "/task.dat", std::ios::binary);
    if (!tasks.empty()) {
        for (const auto &task : tasks) {
            task.save(task_file);
        }
    }
    bag.save();
    TaskGivingNPC::save();
    fmt::print("保存成功！\n");
}

bool Player::load(const string &archive)
{
    if (string folder_path = "../files/" + archive; filesystem::exists(folder_path) && filesystem::is_directory(folder_path)) {
        ifstream read_file(folder_path + "/Player.dat", ios::binary);
        // 读取 name 长度和内容
        size_t name_length;
        read_file.read(reinterpret_cast<char *>(&name_length), sizeof(name_length));
        name.resize(name_length);
        read_file.read(&name[0], static_cast<long long>(name_length));

        // 从 Player.dat 中读取其他属性
        read_file.read(reinterpret_cast<char *>(&position[0]), sizeof(position[0]));
        read_file.read(reinterpret_cast<char *>(&position[1]), sizeof(position[1]));
        read_file.read(reinterpret_cast<char *>(&position[2]), sizeof(position[2]));
        read_file.read(reinterpret_cast<char *>(&finished[0]), sizeof(finished[0]));
        read_file.read(reinterpret_cast<char *>(&finished[1]), sizeof(finished[1]));
        read_file.read(reinterpret_cast<char *>(&level), sizeof(level));
        read_file.read(reinterpret_cast<char *>(&experience), sizeof(experience));
        read_file.read(reinterpret_cast<char *>(&level_up_exp), sizeof(level_up_exp));
        read_file.read(reinterpret_cast<char *>(&points), sizeof(points));
        read_file.read(reinterpret_cast<char *>(&max_hp), sizeof(max_hp));
        read_file.read(reinterpret_cast<char *>(&max_mp), sizeof(max_mp));
        read_file.read(reinterpret_cast<char *>(&hp), sizeof(hp));
        read_file.read(reinterpret_cast<char *>(&mp), sizeof(mp));
        read_file.read(reinterpret_cast<char *>(&health), sizeof(health));
        read_file.read(reinterpret_cast<char *>(&damage), sizeof(damage));
        read_file.read(reinterpret_cast<char *>(&critical), sizeof(critical));
        read_file.read(reinterpret_cast<char *>(&strength), sizeof(strength));
        read_file.read(reinterpret_cast<char *>(&defence), sizeof(defence));
        read_file.read(reinterpret_cast<char *>(&evasion), sizeof(evasion));
        read_file.read(reinterpret_cast<char *>(&agility), sizeof(agility));
        read_file.read(reinterpret_cast<char *>(&money), sizeof(money));
        read_file.close();

        ifstream file_to_task(folder_path + "/task.dat", ios::binary);
        while (true) {
            int id;
            bool finished;
            file_to_task.read(reinterpret_cast<char *>(&id), sizeof(id));
            file_to_task.read(reinterpret_cast<char *>(&finished), sizeof(finished));

            if (!file_to_task) { break; }
            tasks.push_back(Tasks[id]);
            Tasks[id].receive();
            if (finished) {
                Tasks[id].finish(true);
                Gamer.finishTask(Tasks[id]);
            }
        }
        file_to_task.close();
        ifstream file_to_skill(folder_path + "/skill.dat", ios::binary);
        int skill_size;
        file_to_skill.read(reinterpret_cast<char *>(&skill_size), sizeof(skill_size));
        skills.clear();
        for (size_t i = 0; i < skill_size; ++i) {
            int id;
            file_to_skill.read(reinterpret_cast<char *>(&id), sizeof(id));
            skills.push_back(Skills[id]);
        }
        file_to_skill.close();
        bag.load();
        TaskGivingNPC::load();
        fmt::print("存档读取成功！");
        return true;
    }
    fmt::print("没有存档！\n");
    return false;
}
