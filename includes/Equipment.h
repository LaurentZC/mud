#pragma once

#include <array>
#include <string>

#include "fmt/color.h"

// 装备
class Equipment
{
public:
    Equipment();
    Equipment(int id, std::string name, std::string description, int money);
    Equipment(const Equipment &other);
    Equipment(Equipment &&other) noexcept;
    Equipment &operator=(const Equipment &other);
    Equipment &operator=(Equipment &&other) noexcept;

    virtual ~Equipment();

    virtual void showAttributes() const = 0;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getMoney() const;

    [[nodiscard]] int getId() const;
    bool operator==(const Equipment &other) const;
    bool operator!=(const Equipment &other) const;

protected:
    int id {};                  // id
    std::string name {};        // 名字
    std::string description {}; // 描述
    int money {};               // 购买价格
};

// 武器
class Weapon final : public Equipment
{
public:
    Weapon();
    Weapon(int id, std::string name, std::string description, int money, int damage, double critical, int min_strength_to_equip);
    Weapon(const Weapon &other);
    Weapon(Weapon &&other) noexcept;
    Weapon &operator=(const Weapon &other);
    Weapon &operator=(Weapon &&other) noexcept;

    void showAttributes() const override;
    [[nodiscard]] int getMinStrength() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] double getCritical() const;

private:
    int damage {};                // 伤害
    double critical {};           // 暴击率
    int min_strength_to_equip {}; // 装备的最小力量点数要求
};

// 防具
class Armor final : public Equipment
{
public:
    Armor();
    Armor(int id, std::string name, std::string description, int money, int add_max_hp, int add_max_mp, double evasion, int defence, int min_agility_to_equip);

    Armor(const Armor &other);

    Armor(Armor &&other) noexcept;

    Armor & operator=(const Armor &other);

    Armor & operator=(Armor &&other) noexcept;

    void showAttributes() const override;
    [[nodiscard]] int getMinAgility() const;
    [[nodiscard]] int getAddMaxHp() const;
    [[nodiscard]] int getAddMaxMp() const;
    [[nodiscard]] double getEvasion() const;
    [[nodiscard]] int getDefence() const;

private:
    int add_max_hp {};
    int add_max_mp {};
    double evasion {};           // 闪避率
    int defence {};              // 防御力
    int min_agility_to_equip {}; // 装备的最小敏捷点数要求
};

inline auto WeaponColor = [](const std::string &text) { return format(fg(fmt::color::cyan), "{}", text); };
// @formatter:off
inline const std::array<Weapon, 11> Weapons = {
    {
        {0, WeaponColor("桃木剑"), "普通的木剑，适合初学者使用。",
            10, 10, 0.05, 0},
        {1, WeaponColor("青锋剑"), "剑身如秋水，剑锋如青虹，传闻能削铁如泥。",
            300, 50, 0.10, 1},
        {2, WeaponColor("打狗棍"), "丐帮祖传武器，看似平凡无奇，却是威力无穷。",
            400, 60, 0.10, 3},
        {3, WeaponColor("金蛇剑"), "剑身如蛇，灵动多变，出招诡异莫测，难以捉摸。",
            500, 70, 0.12, 5},
        {4, WeaponColor("银月弯刀"), "刀如弯月，出招如月影流转，刀光如银，难以防范。",
            500, 75, 0.12, 5},
        {5, WeaponColor("霜寒刀"), "刀光如雪，寒气逼人，斩敌如同冰封世界。",
            600, 90, 0.15, 8},
        {6, WeaponColor("赤焰剑"), "剑身如烈焰燃烧，传说中能燃尽一切邪恶。",
            650, 95, 0.15, 10},
        {7, WeaponColor("九环大刀"), "刀身带有九环，挥舞之间震耳欲聋，霸气十足。",
            700, 100, 0.20, 12},
        {8, WeaponColor("玄铁重剑"), "以玄铁铸成，沉重无比，唯有绝世高手方能驾驭。",
            800, 120, 0.25, 15},
        {9, WeaponColor("霸王枪"), "枪中之王，气势如虹，枪出如龙，威震八方。",
            1000, 130, 0.25, 18},
        {10, WeaponColor("倚天剑"), "天下神器，剑中至宝，江湖传言“倚天不出，谁与争锋”。",
            1200, 150, 0.30, 20}
    }
};
// @formatter:on

inline auto ArmorColor = [](const std::string &text) { return format(fg(fmt::color::light_green), "{}", text); };
// @formatter:off
inline const std::array<Armor, 15> Armors = {
    {
        {0, ArmorColor("钢铁胸甲"), "坚固的铁制护甲，适合勇敢的战士。",
            150, 50, 0, 0.05, 5, 0},
        {1, ArmorColor("符文长袍"), "带有神秘符文的长袍，增强元气。",
            150, 0, 50, 0.05, 5, 0},
        {2, ArmorColor("皮革护肩"), "轻便的护肩，提供灵活性和基本保护。",
            200, 50, 0, 0.08, 8, 1},
        {3, ArmorColor("少林僧衣"), "穿着简单，能显著提升内力的修炼效果。",
            250, 50, 20, 0.12, 8, 1},
        {4, ArmorColor("云海翎袍"), "带有羽毛装饰，增加使用者的闪避能力。",
            280, 60, 20, 0.14, 10, 3},
        {5, ArmorColor("天山雪豹甲"), "由雪豹皮制成，提供极强的保护和反击能力。",
            300, 60, 20, 0.15, 10, 3},
        {6, ArmorColor("九阴真经护裙"), "传说中的护裙，赋予持有者神秘的力量。",
            500, 70, 40, 0.15, 15, 5},
        {7, ArmorColor("白虎战甲"), "采用白虎皮制作，拥有极高的防御力，适合正义之士。",
            550, 70, 40, 0.15, 20, 5},
        {8, ArmorColor("流燕斗篷"), "背后有流燕图案，轻便灵动，适合追风的侠客。",
            420, 80, 40, 0.15, 30, 8},
        {9, ArmorColor("天蚕丝甲"), "由天蚕丝织成的甲衣，轻便舒适，防御力惊人。",
            500, 80, 40,0.22, 30, 8},
        {10, ArmorColor("龙鳞护甲"), "传说中龙族遗留下来的护甲，拥有无与伦比的防御力。",
            700, 100, 60, 0.25, 40, 10},
        {11, ArmorColor("幽冥披风"), "来自幽冥之地的神秘披风，赋予佩戴者如幽灵般的闪避能力。",
            800, 100, 70, 0.25, 50, 10},
        {12, ArmorColor("玄铁重铠"), "以玄铁打造的重铠，防御力无可匹敌，适合重型战士。",
            1100, 150, 70, 0.25, 60, 15},
        {13, ArmorColor("七彩羽衣"), "用彩凤的羽毛编织而成，既轻盈又具备强大的防御力。",
            1400, 180, 80, 0.30, 70, 15},
        {14, ArmorColor("守护之铠"), "寄托着守护之神的庇护的铠甲，具有至高的防御力",
            2000, 200, 100, 0.35, 80, 20}
    }
};
// @formatter:on
