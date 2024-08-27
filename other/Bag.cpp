#include "Bag.h"
#include <iostream>
#include "Helper.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

Bag::Bag() = default;

void Bag::display()
{
    auto display_items = [](const auto &container, const string &label) {
        if (container.empty()) {
            fmt::print("�㻹û��{}��\n", label);
        }
        else {
            fmt::print("{}��\n", label);
            int i = 0;
            for (auto it = container.begin(); it != container.end(); ++it, ++i) {
                fmt::print("{}. ", i + 1);
                it->display();
                if ((i + 1) % 5 == 0) {
                    fmt::print("\n"); // 5������
                }
            }
            if (i % 5 != 0) {
                fmt::print("\n"); // ���һ�л���
            }
        }
    };


    display_items(weapons, "����");
    display_items(armors, "����");

    fmt::println("��ĵ�ҩ�У�");
    fmt::print("��Ѫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��",
               pill_container[PillType::BLOOD_PILL][PillSize::SMALL],
               pill_container[PillType::BLOOD_PILL][PillSize::MID],
               pill_container[PillType::BLOOD_PILL][PillSize::BIG]);
    fmt::print("��Ԫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��",
               pill_container[PillType::MANA_PILL][PillSize::SMALL],
               pill_container[PillType::MANA_PILL][PillSize::MID],
               pill_container[PillType::MANA_PILL][PillSize::BIG]);
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

auto getPillName(const PillSize size, const PillType type)
{
    string name;
    switch (size) {
        case PillSize::SMALL:
            name = "����";
            break;
        case PillSize::MID:
            name = "�м�";
            break;
        case PillSize::BIG:
            name = "�߼�";
            break;
    }
    switch (type) {
        case PillType::BLOOD_PILL:
            name += "��Ѫ��";
            return bloodPill(name);
        case PillType::MANA_PILL:
            name += "��Ԫ��";
            return manaPill(name);
    }
    return name;
}

int Bag::usePill()
{
    auto &blood_pill = pill_container[PillType::BLOOD_PILL];
    auto &mana_pill = pill_container[PillType::MANA_PILL];

    fmt::print("��ĵ�ҩ�У�\n");
    fmt::print("��Ѫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��\n",
               blood_pill[PillSize::SMALL],
               blood_pill[PillSize::MID],
               blood_pill[PillSize::BIG]);
    fmt::print("��Ԫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��\n",
               mana_pill[PillSize::SMALL],
               mana_pill[PillSize::MID],
               mana_pill[PillSize::BIG]);
    // ѡ��ҩ����
    fmt::print("������ʲô��ҩ��[b(��Ѫ��) / m(��Ԫ��) / q(����ʹ��)]��");
    string type_choice;
    PillType type;
    while (true) {
        cin >> type_choice;
        if (type_choice.length() > 1) {
            fmt::print("��Ч�����룡[b(��Ѫ��) / m(��Ԫ��) / q(����ʹ��)]��");
            continue;
        }
        switch (type_choice[0]) {
            case 'b':
                type = PillType::BLOOD_PILL;
                break;
            case 'm':
                type = PillType::MANA_PILL;
                break;
            case 'q':
                fmt::print("ȡ��ʹ�õ�ҩ��\n");
                return 0;
            default:
                fmt::print("��Чָ�[b / m / q]��\n");
                continue;
        }
        break;
    }
    // ѡ��ҩ��С
    fmt::print("ѡ��ҩ��С��[s(����) / m(�м�) / l(�߼�)]��");
    string size_choice;
    while (true) {
        cin >> size_choice;
        if (size_choice.length() > 1) {
            fmt::print("��Ч�����룡[s(����) / m(�м�) / l(�߼�)]��");
            continue;
        }
        PillSize size;
        switch (size_choice[0]) {
            case 's':
                size = PillSize::SMALL;
                break;
            case 'm':
                size = PillSize::MID;
                break;
            case 'l':
                size = PillSize::BIG;
                break;
            case 'q':
                fmt::print("����ʹ�õ�ҩ��\n");
                return 0;
            default:
                fmt::print("��Чָ�[s / m / l / q]��\n");
                continue;
        }

        // ʹ��ѡ��ĵ�ҩ
        auto &selected_pill = pill_container[type];
        auto name = getPillName(size, type);
        if (selected_pill[size] == 0) {
            fmt::print("��û��{}!\n", name);
            continue;
        }
        // ���ݵ�ҩ���ͺʹ�С������Ӧ�Ļظ�����
        switch (size) {
            case PillSize::SMALL:
                fmt::print("�ҩ�ɹ����ظ�25%{}!\n", name == bloodPill(name) ? "����ֵ" : "Ԫ��");
                break;
            case PillSize::MID:
                fmt::print("�ҩ�ɹ����ظ�35%{}!\n", name == bloodPill(name) ? "����ֵ" : "Ԫ��");
                break;
            case PillSize::BIG:
                fmt::print("�ҩ�ɹ����ظ�45%{}!\n", name == bloodPill(name) ? "����ֵ" : "Ԫ��");
                break;
        }
        selected_pill[size] -= 1;
        return size == PillSize::SMALL ? 1 : size == PillSize::MID ? 2 : 3;
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

    fmt::println("�����{}��{}��", num, getPillName(size, type));
    return num;
}

void Bag::addArmor(const Armor &armor) { armors.emplace_back(armor); }

void Bag::addWeapon(const Weapon &weapon) { weapons.emplace_back(weapon); }

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
