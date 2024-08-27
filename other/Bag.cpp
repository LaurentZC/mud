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
            fmt::println("�㻹û��" + label + "��");
        }
        else {
            fmt::println(label + "�� ");
            int i = 0;
            for (auto it = container.begin(); it != container.end(); ++it, ++i) {
                fmt::print("{}. ", i + 1);
                it->display();
                if ((i + 1) % 5 == 0) {
                    fmt::print("\n"); // 5������
                }
            }
            if (i % 5 != 0) {
                fmt::print("\t"); // ���һ�л���
            }
        }
    };

    display_items(weapons, "����");
    display_items(armors, "����");

    fmt::println("��ĵ�ҩ�У�");
    fmt::print("��Ѫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��", pill_container[PillType::BLOOD_PILL][PillSize::SMALL], pill_container[PillType::BLOOD_PILL][PillSize::MID], pill_container[PillType::BLOOD_PILL][PillSize::BIG]);
    fmt::print("��Ԫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��", pill_container[PillType::MANA_PILL][PillSize::SMALL], pill_container[PillType::MANA_PILL][PillSize::MID], pill_container[PillType::MANA_PILL][PillSize::BIG]);
}

void Bag::useEquipment(const Player &player)
{
    display();
    cout << "�������������Ƿ���:" << endl;
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
                        swap(weapons[0], weapons[choice3]);
                    }
                }
            }
        }
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
                    swap(weapons[0], weapons[choice3]);
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
                        swap(armors[0], armors[choice3]);
                    }
                }
            }
        }
        while (true) {
            cout << "����鿴�ļ�����(����������, 0���˳�)" << endl;
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
                swap(armors[0], armors[choice3]);
            }
        }
    }
}

int Bag::usePill()
{
    auto &blood_pill = pill_container[PillType::BLOOD_PILL];
    auto &mana_pill = pill_container[PillType::MANA_PILL];

    fmt::println("��ĵ�ҩ�У�");
    fmt::print("��Ѫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��", blood_pill[PillSize::SMALL], blood_pill[PillSize::MID], blood_pill[PillSize::BIG]);
    fmt::print("��Ԫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��", mana_pill[PillSize::SMALL], mana_pill[PillSize::MID], mana_pill[PillSize::BIG]);

    fmt::print("������ʲô��ҩ��[s(����) / m(�м�) / l(�߼�) / q(����ʹ��)]��");
    string choice;
    while (true) {
        cin >> choice;
        if (choice.length() > 1) {
            fmt::print("��Ч�����룡[s(����) / m(�м�) / l(�߼�) / q(����ʹ��)]��");
        }
        switch (choice[0]) {
            case 's' :
                if (blood_pill[PillSize::SMALL] == 0) {
                    cout << "��û�г�����Ѫ��!" << endl;
                    break;
                }
                cout << "�ҩ�ɹ����ظ�25%����ֵ!" << endl;
                blood_pill[PillSize::SMALL] -= 1;
                return 1;
            case 'm' :
                if (blood_pill[PillSize::MID] == 0) {
                    cout << "û���м���Ѫ��!" << endl;
                    break;
                }
                cout << "�ҩ�ɹ����ظ�35%����ֵ!" << endl;
                blood_pill[PillSize::MID] -= 1;
                return 2;
            case 'l' :
                if (blood_pill[PillSize::BIG] == 0) {
                    cout << "û�и߼���Ѫ��!" << endl;
                    break;
                }
                cout << "�ҩ�ɹ����ظ�45%����ֵ!" << endl;
                blood_pill[PillSize::BIG] -= 1;
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

int Bag::addPill(const PillType type, const PillSize size, const int num)
{
    auto &amount = pill_container[type][size];
    if (amount + num > 10) {
        amount = 10;
        fmt::println("�㳢�԰����ĵ�ҩ�Ž�ȥ����ϧŬ���˰���ֻ��װ��10��");
        return 0;
    }
    amount += num;
    string pill;
    if (size == PillSize::BIG) {
        pill += "�߼�";
    }
    else if (size == PillSize::MID) {
        pill += "�м�";
    }
    else {
        pill += "����";
    }
    pill += type == PillType::BLOOD_PILL ? "��Ѫ��" : "��Ԫ��";
    fmt::println("�����{}��{}��", num, pill);
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
