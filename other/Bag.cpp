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
        fmt::println("�㻹û��������");
    }
    else {
        fmt::println("������ ");
        for (auto it = weapons.begin(); it != weapons.end(); ++it, ++i) {
            fmt::print("{}. ", i + 1);
            it->display();
            cout << "\t\n"[i % 5 == 0];
        }
    }

    i = 0;
    if (armors.empty()) {
        fmt::println("�㻹û�з��ߡ�");
    }
    else {
        fmt::println("���ߣ� ");
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
    cout << "�������������Ǽ���(weapon or armor):" << endl;
    string choice1;
    cin >> choice1;
    while (choice1 != "weapon" && choice1 != "armor") {
        if (choice1 != "weapon" && choice1 != "armor") {
            cout << "������armor �� weapon:" << endl;
            cin >> choice1;
        }
        else
            break;
    }
    if (choice1 == "weapon") {
        cout << "����Ҫֱ��װ���ϻ����Ȳ鿴(install or check)" << endl;
        string choice2;
        cin >> choice2;
        while (choice1 != "install" && choice1 != "check") {
            if (choice1 != "install" && choice1 != "check") {
                cout << "������install �� check:" << endl;
                cin >> choice1;
            }
            else
                break;
        }
        if (choice2 == "check") {
            while (true) {
                cout << "����鿴�ļ�����(����������,0���˳�)" << endl;
                int choice3;
                cin >> choice3;
                while (choice3 >= weapons.size() || choice3 < 0) {
                    cout << "��������ȷ�ı��" << endl;
                    cin >> choice3;
                }
                if (choice3 == 0)
                    return;;
                weapons[choice3].showAttributes();
                cout << "�Ƿ�Ҫװ����(yes or no)" << endl;
                string choice4;
                cin >> choice4;
                while (choice4 != "yes" && choice4 != "no") {
                    cout << "������yes �� no " << endl;
                    cin >> choice4;
                    if (choice4 == "yes" || choice4 == "no")
                        break;
                }
                if (choice4 == "yes") {
                    if (weapons[choice3].getMinStrength() > player.getStrength())
                        cout << "װ��ʧ�ܣ�����ֵ����" << endl;
                    else {
                        cout << "װ���ɹ���" << endl;
                        player.addWeapon(weapons[choice3]);
                    }
                }
            }
        }
        else {
            if (choice2 == "install") {
                while (true) {
                    cout << "����װ���ļ�����(����������,0���˳�)" << endl;
                    int choice3;
                    cin >> choice3;
                    while (choice3 >= weapons.size() || choice3 < 0) {
                        cout << "������Եı��" << endl;
                        cin >> choice3;
                    }
                    if (choice3 == 0)
                        return;
                    if (weapons[choice3].getMinStrength() > player.getStrength())
                        cout << "װ��ʧ�ܣ�����ֵ����" << endl;
                    else {
                        cout << "װ���ɹ���" << endl;
                        player.addWeapon(weapons[choice3]);
                    }
                }
            }
        }
    }
    else {
        cout << "����Ҫֱ��װ���ϻ����Ȳ鿴(install or check)" << endl;
        string choice2;
        cin >> choice2;
        while (choice1 != "install" && choice1 != "check") {
            if (choice1 != "install" && choice1 != "check") {
                cout << "������install �� check:" << endl;
                cin >> choice1;
            }
            else
                break;
        }
        if (choice2 == "check") {
            while (true) {
                cout << "����鿴�ļ�����(����������,0���˳�)" << endl;
                int choice3;
                cin >> choice3;
                while (choice3 >= armors.size() || choice3 < 0) {
                    cout << "��������ȷ�ı��" << endl;
                    cin >> choice3;
                }
                if (choice3 == 0)
                    return;
                armors[choice3].showAttributes();
                cout << "�Ƿ�Ҫװ����(yes or no)" << endl;
                string choice4;
                cin >> choice4;
                while (choice4 != "yes" && choice4 != "no") {
                    cout << "������yes �� no " << endl;
                    cin >> choice4;
                    if (choice4 == "yes" || choice4 == "no")
                        break;
                }
                if (choice4 == "yes") {
                    if (armors[choice3].getMinAgility() > player.getStrength())
                        cout << "װ��ʧ�ܣ�����ֵ����" << endl;
                    else {
                        cout << "װ���ɹ���" << endl;
                        player.addArmor(armors[choice3]);
                    }
                }
            }
        }
        else {
            while (true) {
                cout << "����鿴�ļ�����(����������,0���˳�)" << endl;
                cout << "����װ���ļ�����(�������Ӧ�ı��)" << endl;
                int choice3;
                cin >> choice3;
                while (choice3 >= armors.size() || choice3 < 0) {
                    cout << "������Եı��" << endl;
                    cin >> choice3;
                }
                if (choice3 == 0)
                    return;
                if (armors[choice3].getMinAgility() > player.getStrength())
                    cout << "װ��ʧ�ܣ�����ֵ����" << endl;
                else {
                    cout << "װ���ɹ���" << endl;
                    player.addArmor(armors[choice3]);
                }
            }
        }
    }
}

int Bag::useBloodPotion()
{
    cout << "���õ�Ѫƿ�У�" << endl;
    auto it = blood_potion.begin();
    for (; it != blood_potion.end(); ++it) {
        cout << it->first << ":" << it->second << "��" << endl;
    }
    cout << "�������ĸ�Ѫƿ��s,m,l),ȡ��������q" << endl;
    char choice;
    while (true) {
        cin >> choice;
        switch (choice) {
            case 's' :
                it = blood_potion.find("small");
                if (it->second == 0) {
                    cout << "û��СѪƿ������ʧ��!" << endl;
                    break;
                }
                cout << "����СѪƿ�ɹ����ظ�25%����ֵ!" << endl;
                it->second -= 1;
                return 1;
            case 'm' :
                it = blood_potion.find("medium");
                if (it->second == 0) {
                    cout << "û����Ѫƿ������ʧ��!" << endl;
                    break;
                }
                cout << "������Ѫƿ�ɹ����ظ�35%����ֵ!" << endl;
                it->second -= 1;
                return 2;
            case 'l' :
                it = blood_potion.find("large");
                if (it->second == 0) {
                    cout << "û�д�Ѫƿ������ʧ��!" << endl;
                    break;
                }
                cout << "���ô�Ѫƿ�ɹ����ظ�45%����ֵ!" << endl;
                it->second -= 1;
                return 3;
            case 'q' :
                cout << "�����κ�Ѫƿ�����ظ�Ѫ����" << endl;
                return 0;
            default :
                cout << "������s,m,l��q" << endl;
                break;
        }
    }
}

int Bag::useManaPotion()
{
    cout << "���õ���ƿ�У�" << endl;
    auto it = mana_potion.begin();
    for (it = mana_potion.begin(); it != mana_potion.end(); ++it) {
        cout << it->first << ":" << it->second << "��" << endl;
    }
    cout << "�������ĸ���ƿ��s,m,l),ȡ��������q" << endl;
    string input;
    while (true) {
        cin >> input;
        if (input.length() > 1) {
            fmt::print("��Ч��ָ������� [s/m/l/q]��");
            continue;
        }
        switch (input[0]) {
            case 's' :
                it = mana_potion.find("small");
                if (it->second == 0) {
                    cout << "û��С��ƿ������ʧ��!" << endl;
                    break;
                }
                cout << "����С��ƿ�ɹ����ظ�30%����ֵ!" << endl;
                it->second -= 1;
                return 1;
            case 'm' :
                it = mana_potion.find("medium");
                if (it->second == 0) {
                    cout << "û������ƿ������ʧ��!" << endl;
                    break;
                }
                cout << "��������ƿ�ɹ����ظ�50%����ֵ!" << endl;
                it->second -= 1;
                return 2;
            case 'l' :
                it = mana_potion.find("large");
                if (it->second == 0) {
                    cout << "û�д���ƿ������ʧ��!" << endl;
                    break;
                }
                cout << "���ô���ƿ�ɹ����ظ�100%����ֵ!" << endl;
                it->second -= 1;
                return 3;
            case 'q' :
                cout << "�����κ���ƿ�����ظ�����ֵ��" << endl;
                return 0;
            default :
                cout << "������s,m,l��q" << endl;
                break;
        }
    }
}

int Bag::addBloodPotion(const string &type, const int num)
{
    const auto it = blood_potion.find(type);
    if (it->second + num > 10) {
        cout << "�㳢�԰�����ƿ�ӷŽ�ȥ����ϧŬ���˰��컹��װ������" << endl;
        return 0;
    }
    it->second += num;
    cout << "�����" << num << "��Ѫƿ" << endl;
    return num;
}

int Bag::addManaPotion(const string &type, int num)
{
    const auto it = mana_potion.find(type);
    if (it->second + num > 10) {
        cout << "�㳢�԰�����ƿ�ӷŽ�ȥ����ϧŬ���˰��컹��װ������" << endl;
        return 0;
    }
    it->second += num;
    cout << "�����" << num << "����ƿ" << endl;
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
