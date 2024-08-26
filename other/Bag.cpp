#include "Bag.h"
#include <iostream>
#include "Player.h"
#include "fmt/core.h"

using namespace std;

Bag::Bag() = default;

void Bag::display()
{
    int i = 0;
    if (weapons.empty()) {
        fmt::println("你还没有武器。");
    }
    else {
        fmt::println("武器： ");
        for (auto it = weapons.begin(); it != weapons.end(); ++it, ++i) {
            fmt::print("{}. ", i + 1);
            it->display();
            cout << "\t\n"[i % 5 == 0];
        }
    }

    i = 0;
    if (armors.empty()) {
        fmt::println("你还没有防具。");
    }
    else {
        fmt::println("防具： ");
        for (auto it = weapons.begin(); it != weapons.end(); ++it, ++i) {
            fmt::print("{}. ", i + 1);
            it->display();
            cout << "\t\n"[i % 5 == 0];
        }
    }
}

void Bag::useEquipment(Player &player)
{
    display();
    cout << "你想用武器还是甲胄(weapon or armor):" << endl;
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
                        player.addWeapon(weapons[choice3]);
                    }
                }
            }
        }
        else {
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
                        player.addWeapon(weapons[choice3]);
                    }
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
                        player.addArmor(armors[choice3]);
                    }
                }
            }
        }
        else {
            while (true) {
                cout << "你想查看哪件甲胄(请输入其编号,0是退出)" << endl;
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
                    player.addArmor(armors[choice3]);
                }
            }
        }
    }
}

int Bag::useBloodPotion()
{
    cout << "可用的血瓶有：" << endl;
    auto it = blood_potion.begin();
    for (; it != blood_potion.end(); ++it) {
        cout << it->first << ":" << it->second << "个" << endl;
    }
    cout << "你想用哪个血瓶（s,m,l),取消请输入q" << endl;
    char choice;
    while (true) {
        cin >> choice;
        switch (choice) {
            case 's' :
                it = blood_potion.find("small");
                if (it->second == 0) {
                    cout << "没有小血瓶，饮用失败!" << endl;
                    break;
                }
                cout << "饮用小血瓶成功，回复25%生命值!" << endl;
                it->second -= 1;
                return 1;
            case 'm' :
                it = blood_potion.find("medium");
                if (it->second == 0) {
                    cout << "没有中血瓶，饮用失败!" << endl;
                    break;
                }
                cout << "饮用中血瓶成功，回复35%生命值!" << endl;
                it->second -= 1;
                return 2;
            case 'l' :
                it = blood_potion.find("large");
                if (it->second == 0) {
                    cout << "没有大血瓶，饮用失败!" << endl;
                    break;
                }
                cout << "饮用大血瓶成功，回复45%生命值!" << endl;
                it->second -= 1;
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

int Bag::useManaPotion()
{
    cout << "可用的蓝瓶有：" << endl;
    auto it = mana_potion.begin();
    for (it = mana_potion.begin(); it != mana_potion.end(); ++it) {
        cout << it->first << ":" << it->second << "个" << endl;
    }
    cout << "你想用哪个蓝瓶（s,m,l),取消请输入q" << endl;
    string input;
    while (true) {
        cin >> input;
        if (input.length() > 1) {
            fmt::print("无效的指令，请输入 [s/m/l/q]：");
            continue;
        }
        switch (input[0]) {
            case 's' :
                it = mana_potion.find("small");
                if (it->second == 0) {
                    cout << "没有小蓝瓶，饮用失败!" << endl;
                    break;
                }
                cout << "饮用小蓝瓶成功，回复30%法力值!" << endl;
                it->second -= 1;
                return 1;
            case 'm' :
                it = mana_potion.find("medium");
                if (it->second == 0) {
                    cout << "没有中蓝瓶，饮用失败!" << endl;
                    break;
                }
                cout << "饮用中蓝瓶成功，回复50%法力值!" << endl;
                it->second -= 1;
                return 2;
            case 'l' :
                it = mana_potion.find("large");
                if (it->second == 0) {
                    cout << "没有大蓝瓶，饮用失败!" << endl;
                    break;
                }
                cout << "饮用大蓝瓶成功，回复100%法力值!" << endl;
                it->second -= 1;
                return 3;
            case 'q' :
                cout << "喝下任何蓝瓶，不回复法力值！" << endl;
                return 0;
            default :
                cout << "请输入s,m,l或q" << endl;
                break;
        }
    }
}

int Bag::addBloodPotion(const string &type, const int num)
{
    const auto it = blood_potion.find(type);
    if (it->second + num > 10) {
        cout << "你尝试把最后的瓶子放进去，可惜努力了半天还是装不下了" << endl;
        return 0;
    }
    it->second += num;
    cout << "添加了" << num << "个血瓶" << endl;
    return num;
}

int Bag::addManaPotion(const string &type, int num)
{
    const auto it = mana_potion.find(type);
    if (it->second + num > 10) {
        cout << "你尝试把最后的瓶子放进去，可惜努力了半天还是装不下了" << endl;
        return 0;
    }
    it->second += num;
    cout << "添加了" << num << "个蓝瓶" << endl;
    return num;
}

void Bag::addArmor(const Armor &armor) { armors.push_back(armor); }

void Bag::addWeapon(const Weapon &weapon) { weapons.push_back(weapon); }

void Bag::removeArmor(const Armor &armor)
{
    auto it = armors.begin();
    for (it = armors.begin(); it != armors.end(); ++it) {
        if (it->getName() == armor.getName())
            break;
    }
    armors.erase(it);
}

void Bag::removeWeapon(const Weapon &weapon)
{
    auto it = weapons.begin();
    for (it = weapons.begin(); it != weapons.end(); ++it) {
        if (it->getName() == weapon.getName())
            break;
    }
    weapons.erase(it);
}
