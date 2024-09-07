#include "Bag.h"

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
                fmt::print("{}. {}", i + 1, it->getName());
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
    fmt::print("回血丹:  \t 高级{}颗 \t 中级{}颗 \t 初级{}颗\n", pills[BigBloodPill], pills[MidBloodPill], pills[SmallBloodPill]);
    fmt::print("回元丹:  \t 初级{}颗 \t 中级{}颗 \t 高级{}颗\n", pills[BigManaPill], pills[MidManaPill], pills[SmallManaPill]);
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
            break;
        }
        if (choice == "a") {
            max_size = armors.size();
            break;
        }
        if (choice == "q")
            return;
        fmt::print("无效的输入！[w(武器) / a(防具) / q(放弃)]: ");
    }

    while (true) {
        fmt::print("你想装备哪件(请输入其编号, 0是退出):");
        int pos;
        while (true) {
            cin >> pos;
            if (pos == 0)
                return;
            if (0 < pos && pos < max_size) {
                break;
            }
            fmt::print("请输入对的编号\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    fmt::print("回血丹:  \t 高级{}颗 \t 中级{}颗 \t 初级{}颗", pills[BigBloodPill], pills[MidBloodPill], pills[SmallBloodPill]);
    fmt::print("回元丹:  \t 初级{}颗 \t 中级{}颗 \t 高级{}颗", pills[BigManaPill], pills[MidManaPill], pills[SmallManaPill]);
    // 选择丹药类型
    fmt::print("你想用什么丹药？[b(回血丹) / m(回元丹) / q(放弃使用)]: ");
    string type_choice;
    Pill::Type type;
    while (true) {
        cin >> type_choice;
        if (type_choice.length() > 1) {
            fmt::print("无效的输入！[b(回血丹) / m(回元丹) / q(放弃使用)]：");
            continue;
        }
        switch (type_choice[0]) {
            case 'b' :
                type = Pill::Type::BLOOD_PILL;
                break;
            case 'm' :
                type = Pill::Type::MANA_PILL;
                break;
            case 'q' :
                fmt::print("取消使用丹药。\n");
                return;
            default :
                fmt::print("无效指令！[b / m / q]：\n");
                continue;
        }
        break;
    }
    // 选择丹药大小
    fmt::print("选择丹药大小：[s(初级) / m(中级) / l(高级)]：");
    string size_choice;
    while (true) {
        cin >> size_choice;
        if (size_choice.length() > 1) {
            fmt::print("无效的输入！[s(初级) / m(中级) / l(高级)]：");
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
                fmt::print("无效指令！[s / m / l / q]：\n");
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

void Bag::save() const
{
    const string path = "../files/" + Gamer.getName() + "/Bag";
    filesystem::create_directories(path);
    if (!weapons.empty()) {
        for (const Weapon &weapon : weapons) {
            weapon.save();
        }
    }
    if (!armors.empty()) {
        for (const Armor &armor : armors) {
            armor.save();
        }
    }
    ofstream file(path + "/pill.dat", ios::binary);
    // 保存 map 大小
    if (!pills.empty()) {
        const size_t map_size = pills.size();
        file.write(reinterpret_cast<const char *>(&map_size), sizeof(map_size));

        // 保存每个 Pill 和对应的数量
        for (const auto &[pill, cnt] : pills) {
            pill.serialize(file);
            file.write(reinterpret_cast<const char *>(&cnt), sizeof(cnt));
        }
    }
    file.close();
}

void Bag::load()
{
    const string path = "../files/" + Gamer.getName() + "/Bag";

    ifstream file(path, ios::binary);

    vector<int> ids = Weapon::load();
    for (const auto &id : ids) {
        weapons.push_back(Weapons[id]);
    }
    ids = Armor::load();
    for (const auto &id : ids) {
        armors.push_back(Armors[id]);
    }
    // 读取 map 大小
    size_t map_size;
    file.read(reinterpret_cast<char *>(&map_size), sizeof(map_size));

    // 读取每个 Pill 和对应的数量
    for (size_t i = 0; i < map_size; ++i) {
        // 没写默认构造
        Pill pill {Pill::Type::BLOOD_PILL, Pill::Size::SMALL};
        pill.deserialize(file);
        int value;
        file.read(reinterpret_cast<char *>(&value), sizeof(value));
        pills[pill] = value;
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
