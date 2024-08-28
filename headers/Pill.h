#pragma once

#include <string>

struct Pill
{
    enum class Type { NULL_TYPE, BLOOD_PILL, MANA_PILL }; // 回血丹，回蓝丹
    enum class Size { NULL_SIZE, BIG, MID, SMALL };       // 大、中、小号

    Type type {Type::NULL_TYPE};
    Size size {Size::NULL_SIZE};

    Pill();
    Pill(Type type, Size size);

    bool operator<(const Pill &other) const;
    [[nodiscard]] std::string getPillName() const;
    void usePill() const;
};

inline Pill BigBloodPill = {Pill::Type::BLOOD_PILL, Pill::Size::BIG};
inline Pill MidBloodPill = {Pill::Type::BLOOD_PILL, Pill::Size::MID};
inline Pill SmallBloodPill = {Pill::Type::BLOOD_PILL, Pill::Size::SMALL};
inline Pill BigManaPill = {Pill::Type::MANA_PILL, Pill::Size::BIG};
inline Pill MidManaPill = {Pill::Type::MANA_PILL, Pill::Size::MID};
inline Pill SmallManaPill = {Pill::Type::MANA_PILL, Pill::Size::SMALL};
