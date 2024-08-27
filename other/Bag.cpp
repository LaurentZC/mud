#include "Bag.h"
#include <iostream>
#include "Player.h"
#include "fmt/core.h"

using namespace std;

Bag::Bag() = default;

void Bag::display()
{
    auto display_items = [](const auto &container, const std::string &label) {
        if (container.empty()) {
            fmt::println("你还没有" + label + "。");
        }
        else {
            fmt::println(label + "： ");
            int i = 0;
            for (auto it = container.begin(); it != container.end(); ++it, ++i) {
                fmt::print("{}. ", i + 1);
                it->display();
                if ((i + 1) % 5 == 0) {
                    fmt::print("\n"); // 5个换行
                }
            }
            if (i % 5 != 0) {
                fmt::print("\t"); // 最后一行换行
            }
        }
    };

    display_items(weapons, "武器");
    display_items(armors, "防具");

    fmt::println("你的丹药有：");
    fmt::print("回血丹： \t 初级{}颗 \t 中级{}颗 \t 高级{}颗", pill_container[PillType::BLOOD_PILL][PillSize::SMALL], pill_container[PillType::BLOOD_PILL][PillSize::MID], pill_container[PillType::BLOOD_PILL][PillSize::BIG]);
    fmt::print("回元丹： \t 初级{}颗 \t 中级{}颗 \t 高级{}颗", pill_container[PillType::MANA_PILL][PillSize::SMALL], pill_container[PillType::MANA_PILL][PillSize::MID], pill_container[PillType::MANA_PILL][PillSize::BIG]);
}

void Bag::useEquipment(const Player &player)
{
    display();
    cout << "你想用武器还是防具:" << endl;
    string choice1;
    cin >> choice1;
    while (choice1 != "weapon" && choice1 != "armor") {
        if (choice1 != "weapon" && choice1 != "armor") {
            cout << "请输入armor 或 weapon:" << endl;
            cin >> choice1;
        }
        else
            break;
    }
    if (choice1 == "weapon") {
        cout << "你想要直接装备上还是先查看(install or check)" << endl;
        string choice2;
        cin >> choice2;
        while (choice1 != "install" && choice1 != "check") {
            if (choice1 != "install" && choice1 != "check") {
                cout << "请输入install 或 check:" << endl;
                cin >> choice1;
            }
            else
                break;
        }
        if (choice2 == "check") {
            while (true) {
                cout << "你想查看哪件武器(请输入其编号,0是退出)" << endl;
                int choice3;
                cin >> choice3;
                while (choice3 >= weapons.size() || choice3 < 0) {
                    cout << "请输入正确的编号" << endl;
                    cin >> choice3;
                }
                if (choice3 == 0)
                    return;;
                weapons[choice3].showAttributes();
                cout << "是否要装备上(yes or no)" << endl;
                string choice4;
                cin >> choice4;
                while (choice4 != "yes" && choice4 != "no") {
                    cout << "请输入yes 或 no " << endl;
                    cin >> choice4;
                    if (choice4 == "yes" || choice4 == "no")
                        break;
                }
                if (choice4 == "yes") {
                    if (weapons[choice3].getMinStrength() > player.getStrength())
                        cout << "装备失败，能力值不足" << endl;
                    else {
                        cout << "装备成功！" << endl;
                        swap(weapons[0], weapons[choice3]);
                    }
                }
            }
        }
        if (choice2 == "install") {
            while (true) {
                cout << "你想装备哪件武器(请输入其编号,0是退出)" << endl;
                int choice3;
                cin >> choice3;
                while (choice3 >= weapons.size() || choice3 < 0) {
                    cout << "请输入对的编号" << endl;
                    cin >> choice3;
                }
                if (choice3 == 0)
                    return;
                if (weapons[choice3].getMinStrength() > player.getStrength())
                    cout << "装备失败，能力值不足" << endl;
                else {
                    cout << "装备成功！" << endl;
                    swap(weapons[0], weapons[choice3]);
                }
            }
        }
    }
    else {
        cout << "你想要直接装备上还是先查看(install or check)" << endl;
        string choice2;
        cin >> choice2;
        while (choice1 != "install" && choice1 != "check") {
            if (choice1 != "install" && choice1 != "check") {
                cout << "请输入install 或 check:" << endl;
                cin >> choice1;
            }
            else
                break;
        }
        if (choice2 == "check") {
            while (true) {
                cout << "你想查看哪件甲胄(请输入其编号,0是退出)" << endl;
                int choice3;
                cin >> choice3;
                while (choice3 >= armors.size() || choice3 < 0) {
                    cout << "请输入正确的编号" << endl;
                    cin >> choice3;
                }
                if (choice3 == 0)
                    return;
                armors[choice3].showAttributes();
                cout << "是否要装备上(yes or no)" << endl;
                string choice4;
                cin >> choice4;
                while (choice4 != "yes" && choice4 != "no") {
                    cout << "请输入yes 或 no " << endl;
                    cin >> choice4;
                    if (choice4 == "yes" || choice4 == "no")
                        break;
                }
                if (choice4 == "yes") {
                    if (armors[choice3].getMinAgility() > player.getStrength())
                        cout << "装备失败，能力值不足" << endl;
                    else {
                        cout << "装备成功！" << endl;
                        swap(armors[0], armors[choice3]);
                    }
                }
            }
        }
        while (true) {
            cout << "你想查看哪件甲胄(请输入其编号, 0是退出)" << endl;
            cout << "你想装备哪件武器(请输入对应的编号)" << endl;
            int choice3;
            cin >> choice3;
            while (choice3 >= armors.size() || choice3 < 0) {
                cout << "请输入对的编号" << endl;
                cin >> choice3;
            }
            if (choice3 == 0)
                return;
            if (armors[choice3].getMinAgility() > player.getStrength())
                cout << "装备失败，能力值不足" << endl;
            else {
                cout << "装备成功！" << endl;
                swap(armors[0], armors[choice3]);
            }
        }
    }
}

int Bag::usePill()
{
    auto &blood_pill = pill_container[PillType::BLOOD_PILL];
    auto &mana_pill = pill_container[PillType::MANA_PILL];

    fmt::println("你的丹药有：");
    fmt::print("回血丹： \t 初级{}颗 \t 中级{}颗 \t 高级{}颗", blood_pill[PillSize::SMALL], blood_pill[PillSize::MID], blood_pill[PillSize::BIG]);
    fmt::print("回元丹： \t 初级{}颗 \t 中级{}颗 \t 高级{}颗", mana_pill[PillSize::SMALL], mana_pill[PillSize::MID], mana_pill[PillSize::BIG]);

    fmt::print("你想用什么丹药？[s(初级) / m(中级) / l(高级) / q(放弃使用)]：");
    string choice;
    while (true) {
        cin >> choice;
        if (choice.length() > 1) {
            fmt::print("无效的输入！[s(初级) / m(中级) / l(高级) / q(放弃使用)]：");
        }
        switch (choice[0]) {
            case 's' :
                if (blood_pill[PillSize::SMALL] == 0) {
                    cout << "你没有初级回血丹!" << endl;
                    break;
                }
                cout << "嗑药成功，回复25%生命值!" << endl;
                blood_pill[PillSize::SMALL] -= 1;
                return 1;
            case 'm' :
                if (blood_pill[PillSize::MID] == 0) {
                    cout << "没有中级回血丹!" << endl;
                    break;
                }
                cout << "嗑药成功，回复35%生命值!" << endl;
                blood_pill[PillSize::MID] -= 1;
                return 2;
            case 'l' :
                if (blood_pill[PillSize::BIG] == 0) {
                    cout << "没有高级回血丹!" << endl;
                    break;
                }
                cout << "嗑药成功，回复45%生命值!" << endl;
                blood_pill[PillSize::BIG] -= 1;
                return 3;
            case 'q' :
                cout << "喝下任何血瓶，不回复血量！" << endl;
                return 0;
            default :
                cout << "请输入s,m,l或q" << endl;
                break;
        }
    }
}

int Bag::addPill(const PillType type, const PillSize size, const int num)
{
    auto &amount = pill_container[type][size];
    if (amount + num > 10) {
        amount = 10;
        fmt::println("你尝试把最后的丹药放进去，可惜努力了半天只能装下10颗");
        return 0;
    }
    amount += num;
    string pill;
    if (size == PillSize::BIG) {
        pill += "高级";
    }
    else if (size == PillSize::MID) {
        pill += "中级";
    }
    else {
        pill += "初级";
    }
    pill += type == PillType::BLOOD_PILL ? "回血丹" : "回元丹";
    fmt::println("添加了{}个{}。", num, pill);
    return num;
}

void Bag::addArmor(const Armor &armor) { armors.push_back(armor); }

void Bag::addWeapon(const Weapon &weapon) { weapons.push_back(weapon); }

void Bag::removeArmor(const Armor &armor)
{
    auto it = armors.begin();
    for (; it != armors.end(); ++it) {
        if (it->getName() == armor.getName())
            break;
    }
    armors.erase(it);
}

void Bag::removeWeapon(const Weapon &weapon)
{
    auto it = weapons.begin();
    for (; it != weapons.end(); ++it) {
        if (it->getName() == weapon.getName())
            break;
    }
    weapons.erase(it);
}
