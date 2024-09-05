#include "Player.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "Helper.h"
#include "fmt/core.h"

using namespace std;

void Player::showPlayer() const
{
    fmt::print("\n\n当前人物属性:\n");
    fmt::print("姓名: {} \t 等级: {}\n", name, level);
    fmt::print("经验: {} / {}\n", experience, level_up_exp);

    print(fg(fmt::color::red), "血量: {} / {}\n", hp, max_hp);
    print(fg(fmt::color::blue), "元气: {} / {}\n", mp, max_mp);

    fmt::print("攻击力: {} \t 暴击率: {}\n", damage, critical);

    fmt::print("防御力: {} \t 闪避率: {}\n", defence);

    fmt::print("健康点数: {} \t 攻击点数: {} \t 敏捷点数: {}\n", health, strength, agility);

    fmt::print("金钱: {}\n", money);
}

void Player::checkSkill() const
{
    if (skills.begin() == skills.end()) {
        fmt::println("你没有习得任何技能！");
        return;
    }
    fmt::println("你习得的技能有: ");
    int i = 0;
    for (auto it = skills.begin(); it != skills.end(); ++it, ++i) {
        fmt::print("{}. {}", i + 1, it->getName());
        if ((i + 1) % 5 == 0) {
            fmt::print("\n"); // 5个换行
        }
    }
    if (i % 5 != 0) {
        fmt::print("\n"); // 最后一行换行
    }
}

void Player::checkTask() const
{
    if (skills.begin() == skills.end()) {
        fmt::print("你当前没有任务。");
        return;
    }
    for (auto task : tasks) {
        task.showTask();
    }
}

void Player::openBag() const { bag->display(); }

void Player::usePoint()
{
    fmt::print("请选择你想要加点的选项: \n");
    while (true) {
        fmt::print("健康点数[health] \t 攻击点数 [strength] \t 敏捷点数[agility]\n");
        string choice;
        cin >> choice;
        if (choice == "health") {
            hp += 10;
            mp += 10;
            ++health;
            --points;
            break;
        }
        if (choice == "strength") {
            damage += 5;
            defence += 5;
            ++strength;
            --points;
            break;
        }
        if (choice == "agility") {
            critical += 0.01;
            evasion += 0.01;
            ++agility;
            --points;
            break;
        }
        fmt::print("输入错误，请重新输入:");
    }
}

void Player::gainWeapon(const int index) const { bag->addWeapon(Weapons[index]); }

void Player::gainArmor(const int index) const { bag->addArmor(Armors[index]); }

void Player::gainSkill(const int index) { skills.push_back(Skills[index]); }
void Player::gainPill(const Pill pill, const int index) const { bag->addPill(pill, index); }

void Player::acceptTask(const Task &task) { tasks.push_back(task); }

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
    points = level - temp_level;
    fmt::print("{} \t {} \t", name, level);
    print(fg(fmt::color::green), "{} / {}\n", experience - *it, level_up_exp);
    if (points > 0) {
        level_up_exp = ExpNeeded[level] - ExpNeeded[level - 1];
        fmt::print("恭喜，你升到了{}级！\n", level);
        fmt::print("你有{}点技能点可用，请及时查看！\n", points);
    }
}

int Player::getLevel() const { return level; }

int Player::getMaxHp() const { return max_hp; }
void Player::setMaxHp(const int max_hp) { this->max_hp = max_hp; }

int Player::getMaxMp() const { return max_mp; }
void Player::setMaxMp(const int max_mp) { this->max_mp = max_mp; }

int Player::getHp() const { return hp; }
void Player::setHp(const int hp) { this->hp = hp; }

int Player::getMp() const { return mp; }
void Player::setMp(const int mp) { this->mp = mp; }

int Player::getHealth() const { return health; }
void Player::setHealth(const int health) { this->health = health; }

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
void Player::gainMoney(const int money) { this->money += money; }

vector<Skill> &Player::getSkills() { return skills; }

void Player::save() const
{
    // 玩家创建一个新的文件夹
    const string folder_path = "../../files/" + name;
    filesystem::create_directories(folder_path);
    //创建了一个fileToPlayer的文件输出流对象，以二进制写入SavePlayer.txt
    ofstream out_file(folder_path + "/Player.dat", ios::binary);

    if (!out_file.is_open()) {
        fmt::print("无法打开保存文件！\n");
        fmt::print("不能成功保存！\n");
    }
    // 保存 name 长度和内容
    const size_t name_length = name.size();
    out_file.write(reinterpret_cast<const char *>(&name_length), sizeof(name_length));
    out_file.write(name.c_str(), name_length);

    // 将玩家信息写入 Player.dat
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
    for (const auto &skill : skills) {
        skill.save();
    }
    for (const auto &task : tasks) {
        task.save();
    }
    bag->save();
    fmt::print("成功保存！\n");
}

bool Player::load(Player &player)
{
    if (string folder_path = "../../files/" + name; filesystem::exists(folder_path) && filesystem::is_directory(folder_path)) {
        ifstream file_to_player(folder_path + "/Player.dat", ios::binary);
        // 读取 name 长度和内容
        size_t name_length;
        file_to_player.read(reinterpret_cast<char *>(&name_length), sizeof(name_length));
        name.resize(name_length);
        file_to_player.read(&name[0], name_length);

        // 从 Player.dat 中读取其他属性
        file_to_player.read(reinterpret_cast<char *>(&level), sizeof(level));
        file_to_player.read(reinterpret_cast<char *>(&experience), sizeof(experience));
        file_to_player.read(reinterpret_cast<char *>(&level_up_exp), sizeof(level_up_exp));
        file_to_player.read(reinterpret_cast<char *>(&points), sizeof(points));
        file_to_player.read(reinterpret_cast<char *>(&max_hp), sizeof(max_hp));
        file_to_player.read(reinterpret_cast<char *>(&max_mp), sizeof(max_mp));
        file_to_player.read(reinterpret_cast<char *>(&hp), sizeof(hp));
        file_to_player.read(reinterpret_cast<char *>(&mp), sizeof(mp));
        file_to_player.read(reinterpret_cast<char *>(&health), sizeof(health));
        file_to_player.read(reinterpret_cast<char *>(&damage), sizeof(damage));
        file_to_player.read(reinterpret_cast<char *>(&critical), sizeof(critical));
        file_to_player.read(reinterpret_cast<char *>(&strength), sizeof(strength));
        file_to_player.read(reinterpret_cast<char *>(&defence), sizeof(defence));
        file_to_player.read(reinterpret_cast<char *>(&evasion), sizeof(evasion));
        file_to_player.read(reinterpret_cast<char *>(&agility), sizeof(agility));
        file_to_player.read(reinterpret_cast<char *>(&money), sizeof(money));
        file_to_player.close();

        ifstream file_to_task(folder_path + "/task.dat", ios::binary);
        while (true) {
            int id;
            file_to_task.read(reinterpret_cast<char *>(&id), sizeof(id));
            if (!file_to_task) {
                break;
            }
            player.tasks.push_back(Tasks[id]);
        }
        file_to_task.close();
        ifstream file_to_skill(folder_path + "/skill.dat", ios::binary);
        while (true) {
            int id;
            file_to_skill.read(reinterpret_cast<char *>(&id), sizeof(id));
            if (!file_to_skill) {
                break;
            }
            player.skills.push_back(Skills[id]);
        }
        file_to_skill.close();
        bag->load();
        fmt::print("存档读取成功！");
        return true;
    }
    fmt::print("没有存档！\n");
    return false;
}
