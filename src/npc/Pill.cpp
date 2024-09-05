#include "Pill.h"

#include <fstream>
#include <string>

#include "Player.h"
#include "fmt/color.h"
#include "fmt/core.h"

using namespace std;

extern Player Player;

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
    const string name = this->getPillName();
    const bool temp = name == bloodPill(name);
    // 根据丹药类型和大小进行相应的回复操作
    switch (size) {
        case Size::SMALL :
            fmt::print("嗑药成功，回复25%{}!\n", temp ? "生命值" : "元气");
            if (temp)
                Player.setHp(static_cast<int>(Player.getHp() + Player.getMaxHp() * 0.25));
            else
                Player.setMp(static_cast<int>(Player.getMp() + Player.getMaxMp() * 0.25));
            break;
        case Size::MID :
            fmt::print("嗑药成功，回复35%{}!\n", temp ? "生命值" : "元气");
            if (temp)
                Player.setHp(static_cast<int>(Player.getHp() + Player.getMaxHp() * 0.35));
            else
                Player.setMp(static_cast<int>(Player.getMp() + Player.getMaxMp() * 0.35));
            break;
        case Size::BIG :
            fmt::print("嗑药成功，回复45%{}!\n", temp ? "生命值" : "元气");
            if (temp)
                Player.setHp(static_cast<int>(Player.getHp() + Player.getMaxHp() * 0.45));
            else
                Player.setMp(static_cast<int>(Player.getMp() + Player.getMaxMp() * 0.55));
            break;
    }
}

void Pill::serialize(ofstream &file) const
{
    const int type_save = static_cast<int>(type);
    const int size_save = static_cast<int>(size);
    file.write(reinterpret_cast<const char *>(&type_save), sizeof(type_save));
    file.write(reinterpret_cast<const char *>(&size_save), sizeof(size_save));
}

void Pill::deserialize(ifstream &file)
{
    int type_load;
    int size_load;
    file.read(reinterpret_cast<char *>(&type_load), sizeof(type_load));
    file.read(reinterpret_cast<char *>(&size_load), sizeof(size_load));
    type = static_cast<Type>(type_load);
    size = static_cast<Size>(size_load);
}
