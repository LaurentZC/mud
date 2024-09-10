#include "Pill.h"

#include <fstream>
#include <string>

#include "Player.h"
#include "fmt/color.h"
#include "fmt/core.h"

using namespace std;

extern Player Gamer;

string bloodPill(const string &text) { return format(fg(fmt::color::red), "{}", text); }

string manaPill(const string &text) { return format(fg(fmt::color::blue), "{}", text); }

Pill::Pill(const Type type, const Size size): type(type), size(size) { }

bool Pill::operator<(const Pill &other) const { return tie(type, size) < tie(other.type, other.size); }

string Pill::getPillName() const
{
    string name;
    switch (this->size) {
        case Size::SMALL :
            name = "初级";
            break;
        case Size::MID :
            name = "中级";
            break;
        case Size::BIG :
            name = "高级";
            break;
        default :
            break;
    }
    switch (this->type) {
        case Type::BLOOD_PILL :
            name += "回血丹";
            return bloodPill(name);
        case Type::MANA_PILL :
            name += "回元丹";
            return manaPill(name);
        default :
            break;
    }
    return name;
}

void Pill::usePill() const
{
    const auto use_type = this->type;
    const bool temp = use_type == Type::BLOOD_PILL;
    // 根据丹药类型和大小进行相应的回复操作
    switch (size) {
        case Size::SMALL :
            fmt::print("{}嗑药成功，回复25%{}!\n", this->getPillName(), temp ? "生命值" : "元气");
            if (temp)
                Gamer.setHp(static_cast<int>(Gamer.getHp() + Gamer.getMaxHp() * 0.25));
            else
                Gamer.setMp(static_cast<int>(Gamer.getMp() + Gamer.getMaxMp() * 0.25));
            break;
        case Size::MID :
            fmt::print("{}嗑药成功，回复35%{}!\n", this->getPillName(), temp ? "生命值" : "元气");
            if (temp)
                Gamer.setHp(static_cast<int>(Gamer.getHp() + Gamer.getMaxHp() * 0.35));
            else
                Gamer.setMp(static_cast<int>(Gamer.getMp() + Gamer.getMaxMp() * 0.35));
            break;
        case Size::BIG :
            fmt::print("{}嗑药成功，回复45%{}!\n", this->getPillName(), temp ? "生命值" : "元气");
            if (temp)
                Gamer.setHp(static_cast<int>(Gamer.getHp() + Gamer.getMaxHp() * 0.45));
            else
                Gamer.setMp(static_cast<int>(Gamer.getMp() + Gamer.getMaxMp() * 0.55));
            break;
    }
}
