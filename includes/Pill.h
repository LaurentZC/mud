#pragma once

#include <string>

struct Pill
{
    enum class Type { BLOOD_PILL, MANA_PILL }; // 回血丹，回蓝丹
    enum class Size { BIG, MID, SMALL };       // 大、中、小号

    Type type;
    Size size;

    Pill(Type type, Size size);

    bool operator<(const Pill &other) const;
    [[nodiscard]] std::string getPillName() const;
    void usePill() const;

    void serialize(std::ofstream &file) const;

    void deserialize(std::ifstream &file);
};

inline const Pill BigBloodPill = {Pill::Type::BLOOD_PILL, Pill::Size::BIG};
inline const Pill MidBloodPill = {Pill::Type::BLOOD_PILL, Pill::Size::MID};
inline const Pill SmallBloodPill = {Pill::Type::BLOOD_PILL, Pill::Size::SMALL};
inline const Pill BigManaPill = {Pill::Type::MANA_PILL, Pill::Size::BIG};
inline const Pill MidManaPill = {Pill::Type::MANA_PILL, Pill::Size::MID};
inline const Pill SmallManaPill = {Pill::Type::MANA_PILL, Pill::Size::SMALL};
