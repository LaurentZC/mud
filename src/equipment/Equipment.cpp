#include "Equipment.h"

using namespace std;

#include <fmt/core.h>

#include <utility>

Equipment::Equipment() = default;
Equipment::Equipment(std::string name, std::string description, const int money) : name(std::move(name)), description(std::move(description)), money(money) { }
Equipment::Equipment(Equipment &&) noexcept = default;
Equipment &Equipment::operator=(Equipment &&) noexcept = default;
Equipment::~Equipment() = default;

string Equipment::getName() const { return name; }
int Equipment::getMoney() const { return money; }

Weapon::Weapon() = default;

Weapon::Weapon(const Weapon &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->damage = other.damage;
    this->critical = other.critical;
    this->min_strength_to_equip = other.min_strength_to_equip;
}

Weapon &Weapon::operator=(const Weapon &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->damage = other.damage;
    this->critical = other.critical;
    this->min_strength_to_equip = other.min_strength_to_equip;
    return *this;
}

Weapon::Weapon(Weapon &&) noexcept = default;
Weapon &Weapon::operator=(Weapon &&) noexcept = default;

void Weapon::showAttributes() const
{
    fmt::println("����: {}", name);
    fmt::println("{}", description);
    fmt::println("�۸�: {}", money);
    fmt::println("�˺�: {}", damage);
    fmt::println("������: {}", critical);
    fmt::println("��С����Ҫ��: {}", min_strength_to_equip);
}

Armor::Armor() = default;

Armor::Armor(const Armor &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->add_max_hp = add_max_hp;
    this->add_max_mp = add_max_mp;
    this->defence = defence;
    this->evasion = evasion;
}

Armor &Armor::operator=(const Armor &other)
{
    this->name = other.name;
    this->description = other.description;
    this->money = other.money;
    this->add_max_hp = add_max_hp;
    this->add_max_mp = add_max_mp;
    this->defence = defence;
    this->evasion = evasion;
    return *this;
}

Armor::Armor(Armor &&) noexcept = default;
Armor &Armor::operator=(Armor &&) noexcept = default;

void Armor::showAttributes() const
{
    fmt::println("����: {}", name);
    fmt::println("{}", description);
    fmt::println("�۸�: {}", money);
    fmt::println("���ӵ��������ֵ: {}", add_max_hp);
    fmt::println("���ӵ������ֵ: {}", add_max_mp);
    fmt::println("��С����Ҫ��: {}", min_agility_to_equip);
}

int Weapon::getMinStrength() const { return min_strength_to_equip; }

int Armor::getMinAgility() const { return min_agility_to_equip; }

Armor::Armor(int i)
{
    switch (i) {
        case 0:
            name = "�����ؼ�";
            description = "��̵����ƻ��ף��ʺ��¸ҵ�սʿ��";
            money = 150;
            add_max_hp = 50;
            add_max_mp = 0;
            min_agility_to_equip = 10;
            defence = 15;
            evasion = 5;
            break;
        case 1:
            name = "���ĳ���";
            description = "�������ط��ĵĳ��ۣ���ǿԪ����";
            money = 200;
            add_max_hp = 0;
            add_max_mp = 30;
            min_agility_to_equip = 5;
            defence = 5;
            evasion = 10;
            break;
        case 2:
            name = "Ƥ�ﻤ��";
            description = "���Ļ��磬�ṩ����Ժͻ���������";
            money = 100;
            add_max_hp = 20;
            add_max_mp = 0;
            min_agility_to_equip = 8;
            defence = 8;
            evasion = 6;
            break;
        case 3:
            name = "����ɮ��";
            description = "���ż򵥣���������������������Ч����";
            money = 250;
            add_max_hp = 30;
            add_max_mp = 20;
            min_agility_to_equip = 12;
            defence = 7;
            evasion = 10;
            break;
        case 4:
            name = "�ƺ�����";
            description = "������ëװ�Σ�����ʹ���ߵ�����������";
            money = 280;
            add_max_hp = 10;
            add_max_mp = 10;
            min_agility_to_equip = 14;
            defence = 4;
            evasion = 20;
            break;
        case 5:
            name = "��ɽѩ����";
            description = "��ѩ��Ƥ�Ƴɣ��ṩ��ǿ�ı����ͷ���������";
            money = 400;
            add_max_hp = 30;
            add_max_mp = 20;
            min_agility_to_equip = 15;
            defence = 20;
            evasion = 4;
            break;
        case 6:
            name = "�����澭��ȹ";
            description = "��˵�еĻ�ȹ��������������ص�������";
            money = 600;
            add_max_hp = 50;
            add_max_mp = 40;
            min_agility_to_equip = 12;
            defence = 8;
            evasion = 15;
            break;
        case 7:
            name = "�׻�ս��";
            description = "���ð׻�Ƥ������ӵ�м��ߵķ��������ʺ�����֮ʿ��";
            money = 350;
            add_max_hp = 30;
            add_max_mp = 0;
            min_agility_to_equip = 10;
            defence = 15;
            evasion = 2;
            break;
        case 8:
            name = "���භ��";
            description = "����������ͼ��������鶯���ʺ�׷������͡�";
            money = 420;
            add_max_hp = 15;
            add_max_mp = 30;
            min_agility_to_equip = 15;
            defence = 5;
            evasion = 30;
            break;
        case 9:
            name = "���˿��";
            description = "�����˿֯�ɵļ��£�������ʣ����������ˡ�";
            money = 500;
            add_max_hp = 80;
            add_max_mp = 40;
            min_agility_to_equip = 22;
            defence = 30;
            evasion = 15;
            break;
        case 10:
            name = "���ۻ���";
            description = "��˵���������������Ļ��ף�ӵ�������ױȵķ�������";
            money = 1000;
            add_max_hp = 200;
            add_max_mp = 0;
            min_agility_to_equip = 10;
            defence = 60;
            evasion = 10;
            break;
        case 11:
            name = "��ڤ����";
            description = "������ڤ֮�ص��������磬���������������������������";
            money = 800;
            add_max_hp = 50;
            add_max_mp = 70;
            min_agility_to_equip = 20;
            defence = 20;
            evasion = 30;
            break;
        case 12:
            name = "��������";
            description = "������������������������޿�ƥ�У��ʺ�����սʿ��";
            money = 1100;
            add_max_hp = 250;
            add_max_mp = 0;
            min_agility_to_equip = 23;
            defence = 70;
            evasion = 5;
            break;
        case 13:
            name = "�߲�����";
            description = "�òʷ����ë��֯���ɣ�����ӯ�־߱�ǿ��ķ�������";
            money = 1400;
            add_max_hp = 100;
            add_max_mp = 60;
            min_agility_to_equip = 25;
            defence = 45;
            evasion = 60;
            break;
        case 14:
            name = "�ػ�֮��";
            description = "�������ػ�֮��ıӻ������ף��������ߵķ�����";
            money = 1500;
            add_max_hp = 220;
            add_max_mp = 80;
            min_agility_to_equip = 28;
            defence = 80;
            evasion = 10;
            break;
        default:
            break;
    }
}

Weapon::Weapon(int i)
{
    switch (i) {
        case 0:
            name = "��潣";
            description = "��������ˮ����������磬�������������ࡣ";
            money = 300;
            damage = 50;
            min_strength_to_equip = 10;
            critical = 15;
            break;
        case 1:
            name = "�����ؽ�";
            description = "���������ɣ������ޱȣ�Ψ�о������ַ��ܼ�Ԧ��";
            money = 800;
            damage = 120;
            min_strength_to_equip = 30;
            critical = 5;
            break;
        case 2:
            name = "���߽�";
            description = "�������ߣ��鶯��䣬���й���Ī�⣬����׽����";
            money = 500;
            damage = 70;
            min_strength_to_equip = 15;
            critical = 20;
            break;
        case 3:
            name = "�򹷹�";
            description = "ؤ���洫����������ƽ�����棬ȴ���������";
            money = 400;
            damage = 60;
            min_strength_to_equip = 10;
            critical = 10;
            break;
        case 4:
            name = "˪����";
            description = "������ѩ���������ˣ�ն����ͬ�������硣";
            money = 600;
            damage = 90;
            min_strength_to_equip = 20;
            critical = 18;
            break;
        case 5:
            name = "�Ż���";
            description = "������оŻ�������֮���������������ʮ�㡣";
            money = 700;
            damage = 100;
            min_strength_to_equip = 25;
            critical = 12;
            break;
        case 6:
            name = "���潣";
            description = "����������ȼ�գ���˵����ȼ��һ��а��";
            money = 650;
            damage = 85;
            min_strength_to_equip = 18;
            critical = 20;
            break;
        case 7:
            name = "���콣";
            description = "���������������������������ԡ����첻����˭�����桱��";
            money = 1200;
            damage = 150;
            min_strength_to_equip = 28;
            critical = 25;
            break;
        case 8:
            name = "�����䵶";
            description = "�������£���������Ӱ��ת���������������Է�����";
            money = 500;
            damage = 75;
            min_strength_to_equip = 12;
            critical = 22;
            break;
        case 9:
            name = "����ǹ";
            description = "ǹ��֮����������磬ǹ������������˷���";
            money = 1000;
            damage = 130;
            min_strength_to_equip = 35;
            critical = 15;
            break;
        case 10:
            name = "ľ��";
            description = "��ͨ��ľ�����ʺϳ�ѧ��ʹ�á�";
            money = 10;
            damage = 10;
            min_strength_to_equip = 5;
            critical = 0;
            break;
        default:
            break;
    }
}
