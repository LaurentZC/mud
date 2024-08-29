#include "../../includes/Pill.h"

#include <string>
#include <tuple>
#include "../../includes/Helper.h"
#include "../../fmt/include/fmt/core.h"

using namespace std;

Pill::Pill() = default;
Pill::Pill(const Type type, const Size size): type(type), size(size) { }

bool Pill::operator<(const Pill &other) const { return tie(type, size) < tie(other.type, other.size); }

string Pill::getPillName() const
{
    string name;
    switch (this->size) {
        case Size::SMALL:
            name = "����";
            break;
        case Size::MID:
            name = "�м�";
            break;
        case Size::BIG:
            name = "�߼�";
            break;
        default: break;
    }
    switch (this->type) {
        case Type::BLOOD_PILL:
            name += "��Ѫ��";
            return bloodPill(name);
        case Type::MANA_PILL:
            name += "��Ԫ��";
            return manaPill(name);
        default: break;
    }
    return name;
}

void Pill::usePill() const
{
    const string name = this->getPillName();
    // ���ݵ�ҩ���ͺʹ�С������Ӧ�Ļظ�����
    switch (size) {
        case Size::SMALL:
            fmt::print("�ҩ�ɹ����ظ�25%{}!\n", name == bloodPill(name) ? "����ֵ" : "Ԫ��");
        // �ָ�
            break;
        case Size::MID:
            fmt::print("�ҩ�ɹ����ظ�35%{}!\n", name == bloodPill(name) ? "����ֵ" : "Ԫ��");
        // �ָ�
            break;
        case Size::BIG:
            fmt::print("�ҩ�ɹ����ظ�45%{}!\n", name == bloodPill(name) ? "����ֵ" : "Ԫ��");
        // �ָ�
            break;
        default: ;
    }
}
