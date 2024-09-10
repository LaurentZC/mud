#include "Bag.h"

#include <Helper.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <variant>

#include "Player.h"
#include "fmt/core.h"

using namespace std;

extern Player Gamer;

void Bag::display()
{
    auto display_items = [](const auto &container, const string &label) {
        if (container.empty()) {
            fmt::print("你还没有{}。\n", label);
        }
        else {
            fmt::print("{}: \n", label);
            int i = 0;
            for (auto it = container.begin(); it != container.end(); ++it, ++i) {
                fmt::print("{} {}\t\t", i == 0 ? "装备中: " : to_string(i) + ".", it->getName());

                if ((i + 1) % 5 == 0) {
                    fmt::print("\n"); // 5个换行
                }
            }
            if (i % 5 != 0) {
                fmt::print("\n"); // 最后一行换行
            }
        }
    };

    fmt::print("\n\n");
    display_items(weapons, "武器");
    display_items(armors, "防具");

    fmt::print("你的丹药有: \n");
    print(fg(fmt::color::red), "回血丹:  \t 高级{}颗 \t 中级{}颗 \t 初级{}颗\n", pills[BigBloodPill], pills[MidBloodPill], pills[SmallBloodPill]);
    print(fg(fmt::color::blue), "回元丹:  \t 初级{}颗 \t 中级{}颗 \t 高级{}颗\n", pills[BigManaPill], pills[MidManaPill], pills[SmallManaPill]);
    fmt::print("\n");
}

void Bag::useEquipment()
{
    display();
    fmt::print("你想用武器[w]、防具[a]还是退出[q]:\n");
    string choice;
    size_t max_size;
    while (true) {
        cin >> choice;
        if (choice.length() > 1) {
            fmt::print("无效的输入！[w(武器) / a(防具) / q(放弃)]: ");
            continue;
        }
        if (choice == "w") {
            max_size = weapons.size();
            if (max_size == 1) {
                fmt::print("你没有多余的武器。\n");
                waitForAnyKey();
                return;
            }
            break;
        }
        if (choice == "a") {
            max_size = armors.size();
            if (max_size == 1) {
                fmt::print("你没有多余的护甲。\n");
                waitForAnyKey();
                return;
            }
            break;
        }
        if (choice == "q")
            return;
        fmt::print("无效的输入！[w(武器) / a(防具) / q(放弃)]: ");
    }

    while (true) {
        fmt::print("你想装备哪件(请输入其编号, 0是退出): ");
        string input;
        int pos;
        while (true) {
            cin >> input;
            if (!input.empty() || all_of(input.begin(), input.end(), ::isdigit)) {
                fmt::print("请输入对的编号\n");
                continue;
            }
            pos = stoi(input);
            if (pos == 0) { return; }
            if (0 < pos && pos < max_size) { break; }
            fmt::print("请输入对的编号\n");
        }

        variant<vector<Weapon>, vector<Armor> > equipment = weapons;
        if (choice == "w") {
            equipment = std::move(weapons);
            auto &vec = get<vector<Weapon> >(equipment);
            vec[pos].showAttributes();
            if (vec[pos].getMinStrength() > Gamer.getStrength()) {
                fmt::print("你的力量不足以使用这把武器。\n");
            }
            else {
                fmt::print("装备成功！\n");
                Gamer.removeWeapon(vec[0]);
                swap(vec[0], vec[pos]);
                Gamer.equipWeapon(vec[0]);
            }
            weapons = std::move(vec);
        }
        else {
            equipment = std::move(armors);
            auto &vec = get<vector<Armor> >(equipment);
            vec[pos].showAttributes();
            if (vec[pos].getMinAgility() > Gamer.getStrength()) {
                fmt::print("你的力量不足以使用这把武器。\n");
            }
            else {
                fmt::print("装备成功！\n");
                Gamer.removeArmor(vec[0]);
                swap(vec[0], vec[pos]);
                Gamer.equipArmor(vec[0]);
            }
            armors = std::move(vec);
        }
    }
}

void Bag::usePill()
{
    fmt::print("你的丹药有: \n");
    print(fg(fmt::color::red), "回血丹:  \t 高级{}颗 \t 中级{}颗 \t 初级{}颗 \n", pills[BigBloodPill], pills[MidBloodPill], pills[SmallBloodPill]);
    print(fg(fmt::color::blue), "回元丹:  \t 初级{}颗 \t 中级{}颗 \t 高级{}颗 \n", pills[BigManaPill], pills[MidManaPill], pills[SmallManaPill]);
    // 选择丹药类型
    fmt::print("你想用什么丹药？[red / blue / q(放弃)]: ");
    string type_choice;
    Pill::Type type;
    while (true) {
        cin >> type_choice;
        if (type_choice == "red") {
            type = Pill::Type::BLOOD_PILL;
            break;
        }

        if (type_choice == "blue") {
            type = Pill::Type::MANA_PILL;
            break;
        }
        if (type_choice == "q") {
            fmt::print("取消使用丹药。\n");
            return;
        }
        fmt::print("无效指令！[red / blue / q]: ");
    }

    // 选择丹药大小
    fmt::print("选择丹药大小：[s(初级) / m(中级) / l(高级) / q(放弃)]：");
    string size_choice;
    while (true) {
        cin >> size_choice;
        if (size_choice.length() > 1) {
            fmt::print("无效的输入！[s / m / l / q]：");
            continue;
        }
        Pill::Size size;
        switch (size_choice[0]) {
            case 's' :
                size = Pill::Size::SMALL;
                break;
            case 'm' :
                size = Pill::Size::MID;
                break;
            case 'l' :
                size = Pill::Size::BIG;
                break;
            case 'q' :
                fmt::print("放弃使用丹药。\n");
                return;
            default :
                fmt::print("无效指令！[s / m / l / q]: ");
                continue;
        }

        // 使用选择的丹药
        const Pill pill {type, size};
        const string name = pill.getPillName();
        if (pills[pill] == 0) {
            fmt::print("你没有{}!\n", name);
            return;
        }
        pills[pill] -= 1;
        pill.usePill();
        return;
    }
}

int Bag::addPill(const Pill pill, const int num)
{
    auto &amount = pills[pill];
    int temp = amount;
    if (amount + num > 10) {
        fmt::println("你尝试把最后的丹药放进去，可惜努力了半天只能装下10颗");
        amount = 10;
        temp = amount - temp;
    }
    else {
        amount += num;
        temp = num;
    }
    fmt::print("添加了{}个{}。\n", num, pill.getPillName());
    return temp;
}

std::vector<Weapon> &Bag::getWeapons() { return weapons; }

std::vector<Armor> &Bag::getArmors() { return armors; }

void Bag::save() const
{
    const string path = "../files/" + Gamer.getName() + "/Bag";
    filesystem::create_directories(path);
    ofstream weapon_file(path + "/weapon.dat", ios::binary);
    if (!weapons.empty()) {
        int weapon_size = static_cast<int>(weapons.size());
        weapon_file.write(reinterpret_cast<const char *>(&weapon_size), sizeof(weapon_size));
        for (const Weapon &weapon : weapons) {
            int id = weapon.getId();
            weapon_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
        }
    }
    weapon_file.close();
    ofstream armor_file(path + "/armor.dat", ios::binary);
    if (!armors.empty()) {
        int armor_size = static_cast<int>(weapons.size());
        armor_file.write(reinterpret_cast<const char *>(&armor_size), sizeof(armor_size));
        for (const auto &armor : armors) {
            int id = armor.getId();
            armor_file.write(reinterpret_cast<const char *>(&id), sizeof(id));
        }
    }
    armor_file.close();
    ofstream file(path + "/pill.dat", ios::binary);

    for (const auto &[pill, cnt] : pills) {
        file.write(reinterpret_cast<const char *>(&cnt), sizeof(cnt));
    }

    file.close();
}

void Bag::load()
{
    const string path1 = "../files/" + Gamer.getName() + "/Bag";

    ifstream weapon_file(path1 + "/weapon.dat", ios::binary);
    int weapon_size;
    weapon_file.read(reinterpret_cast<char *>(&weapon_size), sizeof(weapon_size));
    weapons.clear();
    for (size_t i = 0; i < weapon_size; ++i) {
        int id;
        weapon_file.read(reinterpret_cast<char *>(&id), sizeof(id));
        weapons.push_back(Weapons[id]);
    }
    weapon_file.close();

    ifstream armor_file(path1 + "/armor.dat", ios::binary);
    int armor_size;
    armor_file.read(reinterpret_cast<char *>(&armor_size), sizeof(armor_size));
    armors.clear();
    for (size_t i = 0; i < armor_size; ++i) {
        int id;
        armor_file.read(reinterpret_cast<char *>(&id), sizeof(id));
        armors.push_back(Armors[id]);
    }
    armor_file.close();


    const string path = "../files/" + Gamer.getName() + "/Bag/pill.dat";

    ifstream file(path, ios::binary);
    // 读取每个 Pill 和对应的数量
    for (auto &[pill, cnt] : pills) {
        file.read(reinterpret_cast<char *>(&cnt), sizeof(cnt));
    }
    file.close();
}

void Bag::addArmor(const Armor &armor) { armors.emplace_back(armor); }

void Bag::addWeapon(const Weapon &weapon) { weapons.emplace_back(weapon); }

void Bag::removeArmor(const Armor &armor)
{
    const auto it = find_if(armors.begin(), armors.end(), [&](const Armor &arm) {
        return arm.getName() == armor.getName();
    });
    if (it != armors.end())
        armors.erase(it);
}

void Bag::removeWeapon(const Weapon &weapon)
{
    const auto it = find_if(weapons.begin(), weapons.end(), [&](const Weapon &wea) {
        return wea.getName() == weapon.getName();
    });
    if (it != weapons.end())
        weapons.erase(it);
}
