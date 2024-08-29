#include "../../includes/Bag.h"

#include <algorithm>
#include <iostream>
#include <variant>

#include "../../includes/Helper.h"
#include "../../includes/Player.h"
#include "../../fmt/include/fmt/core.h"

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
                it->getName();
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

    fmt::print("��ĵ�ҩ�У�\n");
    fmt::print("��Ѫ���� \t �߼�{}�� \t �м�{}�� \t ����{}��", pills[BigBloodPill], pills[MidBloodPill], pills[SmallBloodPill]);
    fmt::print("��Ԫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��", pills[BigManaPill], pills[MidManaPill], pills[SmallManaPill]);
}

void Bag::useEquipment(const Player &player)
{
    display();
    fmt::print("����������[w]������[a]�����˳�[q]:\n");
    string choice;
    size_t max_size;
    while (true) {
        cin >> choice;
        if (choice.length() > 1) {
            fmt::print("��Ч�����룡[w(����) / a(����) / q(����)]��");
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
        fmt::print("��Ч�����룡[w(����) / a(����) / q(����)]��");
    }

    while (true) {
        fmt::print("����װ���ļ�(����������, 0���˳�):");
        int pos;
        while (true) {
            cin >> pos;
            if (pos == 0) return;
            if (0 < pos && pos < max_size) {
                break;
            }
            fmt::print("������Եı��\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        variant<vector<Weapon>, vector<Armor> > equipment = weapons;
        if (choice == "w") {
            equipment = std::move(weapons);
            auto &vec = get<vector<Weapon> >(equipment);
            vec[pos].showAttributes();
            if (vec[pos].getMinStrength() > player.getStrength()) {
                fmt::print("�������������ʹ�����������\n");
            }
            else {
                fmt::print("װ���ɹ���\n");
                swap(vec[0], vec[pos]);
            }
            weapons = std::move(vec);
        }
        else {
            equipment = std::move(armors);
            auto &vec = get<vector<Armor> >(equipment);
            vec[pos].showAttributes();
            if (vec[pos].getMinAgility() > player.getStrength()) {
                fmt::print("�������������ʹ�����������\n");
            }
            else {
                fmt::print("װ���ɹ���\n");
                swap(vec[0], vec[pos]);
            }
            armors = std::move(vec);
        }
    }
}

void Bag::usePill()
{
    fmt::print("��ĵ�ҩ�У�\n");
    fmt::print("��Ѫ���� \t �߼�{}�� \t �м�{}�� \t ����{}��", pills[BigBloodPill], pills[MidBloodPill], pills[SmallBloodPill]);
    fmt::print("��Ԫ���� \t ����{}�� \t �м�{}�� \t �߼�{}��", pills[BigManaPill], pills[MidManaPill], pills[SmallManaPill]);
    // ѡ��ҩ����
    fmt::print("������ʲô��ҩ��[b(��Ѫ��) / m(��Ԫ��) / q(����ʹ��)]��");
    string type_choice;
    Pill::Type type;
    while (true) {
        cin >> type_choice;
        if (type_choice.length() > 1) {
            fmt::print("��Ч�����룡[b(��Ѫ��) / m(��Ԫ��) / q(����ʹ��)]��");
            continue;
        }
        switch (type_choice[0]) {
            case 'b':
                type = Pill::Type::BLOOD_PILL;
                break;
            case 'm':
                type = Pill::Type::MANA_PILL;
                break;
            case 'q':
                fmt::print("ȡ��ʹ�õ�ҩ��\n");
                return;
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
        Pill::Size size;
        switch (size_choice[0]) {
            case 's':
                size = Pill::Size::SMALL;
                break;
            case 'm':
                size = Pill::Size::MID;
                break;
            case 'l':
                size = Pill::Size::BIG;
                break;
            case 'q':
                fmt::print("����ʹ�õ�ҩ��\n");
                return;
            default:
                fmt::print("��Чָ�[s / m / l / q]��\n");
                continue;
        }

        // ʹ��ѡ��ĵ�ҩ
        const Pill pill {type, size};
        const string name = pill.getPillName();
        if (pills[pill] == 0) {
            fmt::print("��û��{}!\n", name);
            return;
        }
        pills[pill] -= 1;
    }
}

int Bag::addPill(const Pill pill, const int num)
{
    auto &amount = pills[pill];
    if (amount + num > 10) {
        amount = 10;
        fmt::println("�㳢�԰����ĵ�ҩ�Ž�ȥ����ϧŬ���˰���ֻ��װ��10��");
        return 0;
    }
    amount += num;

    fmt::print("�����{}��{}��\n", num, pill.getPillName());
    return num;
}

void Bag::addArmor(const Armor &armor) { armors.emplace_back(armor); }

void Bag::addWeapon(const Weapon &weapon) { weapons.emplace_back(weapon); }

void Bag::removeArmor(const Armor &armor)
{
    const auto it = find_if(armors.begin(), armors.end(), [&](const Armor &arm) {
        return arm.getName() == armor.getName();
    });
    armors.erase(it);
}

void Bag::removeWeapon(const Weapon &weapon)
{
    const auto it = find_if(weapons.begin(), weapons.end(), [&](const Weapon &wea) {
        return wea.getName() == weapon.getName();
    });
    weapons.erase(it);
}
