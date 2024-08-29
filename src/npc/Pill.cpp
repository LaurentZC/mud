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
            name = "初级";
            break;
        case Size::MID:
            name = "中级";
            break;
        case Size::BIG:
            name = "高级";
            break;
        default: break;
    }
    switch (this->type) {
        case Type::BLOOD_PILL:
            name += "回血丹";
            return bloodPill(name);
        case Type::MANA_PILL:
            name += "回元丹";
            return manaPill(name);
        default: break;
    }
    return name;
}

void Pill::usePill() const
{
    const string name = this->getPillName();
    // 根据丹药类型和大小进行相应的回复操作
    switch (size) {
        case Size::SMALL:
            fmt::print("嗑药成功，回复25%{}!\n", name == bloodPill(name) ? "生命值" : "元气");
        // 恢复
            break;
        case Size::MID:
            fmt::print("嗑药成功，回复35%{}!\n", name == bloodPill(name) ? "生命值" : "元气");
        // 恢复
            break;
        case Size::BIG:
            fmt::print("嗑药成功，回复45%{}!\n", name == bloodPill(name) ? "生命值" : "元气");
        // 恢复
            break;
        default: ;
    }
}
