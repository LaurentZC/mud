#include "Skill.h"

#include "fmt/core.h"

using namespace std;

Skill::Skill(int i)
{
    switch (i) {
        case 0:
            name = "����ն";
            description = "�Ӷ����У���������֮�����𺳵��˲���ɾ޴��˺���";
            consumption = 30;
            damage = 150;
            type = 0; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 1:
            name = "��������";
            description = "�������Ѩ��Ѹ�ٻظ���������ֵ��";
            consumption = 20;
            damage = 0;
            type = 1; // �ָ���
            add_hp = 100;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 2:
            name = "��Ӱ��";
            description = "��������Ȱ���Ӱ���٣������޷�Ԥ�У��������һ����";
            consumption = 25;
            damage = 120;
            type = 0; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 3:
            name = "���ľ�";
            description = "�˹���Ϣ���𲽻ָ������뷨����";
            consumption = 15;
            damage = 0;
            type = 1; // �ָ���
            add_hp = 50;
            add_mp = 30;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 4:
            name = "��ջ���";
            description = "���ý�չ�������ʱ���ڴ����߷�������";
            consumption = 20;
            damage = 0;
            type = 2; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 40;
            add_damage = 0;
            add_critical = 0;
            break;
        case 5:
            name = "����ȭ";
            description = "ȫ��һ����ȭ����б�ը�����˺����ߡ�";
            consumption = 35;
            damage = 180;
            type = 0; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 6:
            name = "��Ѫ����";
            description = "���ϵ�ҩ�����ú�Ѹ�ٻָ����������뷨����";
            consumption = 40;
            damage = 0;
            type = 1; // �ָ���
            add_hp = 150;
            add_mp = 50;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 7:
            name = "������β";
            description = "���ٷ������������������β����";
            consumption = 28;
            damage = 130;
            type = 0; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 8:
            name = "��⻤��";
            description = "����ɢ������⣬��ǿ�������������������˺���";
            consumption = 25;
            damage = 0;
            type = 2; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 50;
            add_damage = 20;
            add_critical = 0;
            break;
        case 9:
            name = "����һ��";
            description = "������֮�ƹ������ˣ���ɾ޴���˺���";
            consumption = 30;
            damage = 160;
            type = 0; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 10:
            name = "������";
            description = "�������������ٻָ�������";
            consumption = 10;
            damage = 0;
            type = 1; // �ָ���
            add_hp = 0;
            add_mp = 80;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 11:
            name = "������";
            description = "��������������ǿ�������������ܵ����˺���";
            consumption = 20;
            damage = 0;
            type = 2; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 60;
            add_damage = 0;
            add_critical = 0;
            break;
        case 12:
            name = "������";
            description = "�����������ƶ�������������ƻ�����";
            consumption = 25;
            damage = 140;
            type = 0; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 13:
            name = "���аٱ�";
            description = "ʹ�����аٱ䣬��ʱ���������������ͱ����ʡ�";
            consumption = 30;
            damage = 0;
            type = 2; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 20;
            add_damage = 30;
            add_critical = 15;
            break;
        case 14:
            name = "������";
            description = "�����纮����������ֱ�ӹ������ˣ�����һ�����ʱ������ˡ�";
            consumption = 30;
            damage = 150;
            type = 0; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 0;
            add_damage = 0;
            add_critical = 0;
            break;
        case 15:
            name = "�����";
            description = "����������񹦣����������͹�����������ս������ʱ�䡣";
            consumption = 35;
            damage = 0;
            type = 2; // ������
            add_hp = 0;
            add_mp = 0;
            add_defence = 50;
            add_damage = 20;
            add_critical = 10;
            break;
        case 16:
            name = "ȫ������";
            description = "���İ��񣬽�ע����ȫ�������ڹ����ϣ����������������ͱ����ʣ�"
                    "���ǽ��ͷ�����";
            consumption = 0;
            damage = 0;
            type = 0;
            add_hp = 0;
            add_mp = 0;
            add_defence = -20;
            add_damage = 40;
            add_critical = 20;
            break;
        default:
            break;
    }
}

void Skill::display()
{
    if (type == 0) {
        fmt::print("{}\n{}\n", name, description);
        fmt::print("���ģ�{}���˺���{}\n", consumption, damage);
    }
    else if (type == 1) {
        fmt::print("{}\n{}\n", name, description);
        fmt::print("���ģ�{}\n", consumption);
        fmt::print("Ч�����ظ�{}��Ѫ�����ظ�{}��Ԫ��\n", add_hp, add_mp);
    }
    else if (type == 2) {
        fmt::print("{}\n{}\n", name, description);
        fmt::print("���ģ�{}\n", consumption);
        fmt::print("Ч��������{}������������{}�����ʣ�����{}������\n",
                   add_damage, add_critical, add_defence, add_defence);
    }
}

void Skill::getName() { fmt::print("{}", name); }

int Skill::getConsumption() const { return consumption; }
