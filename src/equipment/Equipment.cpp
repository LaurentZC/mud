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
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("伤害: {}", damage);
    fmt::println("暴击率: {}", critical);
    fmt::println("最小力量要求: {}", min_strength_to_equip);
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
    fmt::println("名字: {}", name);
    fmt::println("{}", description);
    fmt::println("价格: {}", money);
    fmt::println("增加的最大生命值: {}", add_max_hp);
    fmt::println("增加的最大法力值: {}", add_max_mp);
    fmt::println("最小敏捷要求: {}", min_agility_to_equip);
}

int Weapon::getMinStrength() const { return min_strength_to_equip; }

int Armor::getMinAgility() const { return min_agility_to_equip; }

Armor::Armor(int i)
{
    switch (i) {
        case 0:
            name = "钢铁胸甲";
            description = "坚固的铁制护甲，适合勇敢的战士。";
            money = 150;
            add_max_hp = 50;
            add_max_mp = 0;
            min_agility_to_equip = 10;
            defence = 15;
            evasion = 5;
            break;
        case 1:
            name = "符文长袍";
            description = "带有神秘符文的长袍，增强元气。";
            money = 200;
            add_max_hp = 0;
            add_max_mp = 30;
            min_agility_to_equip = 5;
            defence = 5;
            evasion = 10;
            break;
        case 2:
            name = "皮革护肩";
            description = "轻便的护肩，提供灵活性和基本保护。";
            money = 100;
            add_max_hp = 20;
            add_max_mp = 0;
            min_agility_to_equip = 8;
            defence = 8;
            evasion = 6;
            break;
        case 3:
            name = "少林僧衣";
            description = "穿着简单，能显著提升内力的修炼效果。";
            money = 250;
            add_max_hp = 30;
            add_max_mp = 20;
            min_agility_to_equip = 12;
            defence = 7;
            evasion = 10;
            break;
        case 4:
            name = "云海翎袍";
            description = "带有羽毛装饰，增加使用者的闪避能力。";
            money = 280;
            add_max_hp = 10;
            add_max_mp = 10;
            min_agility_to_equip = 14;
            defence = 4;
            evasion = 20;
            break;
        case 5:
            name = "天山雪豹甲";
            description = "由雪豹皮制成，提供极强的保护和反击能力。";
            money = 400;
            add_max_hp = 30;
            add_max_mp = 20;
            min_agility_to_equip = 15;
            defence = 20;
            evasion = 4;
            break;
        case 6:
            name = "九阴真经护裙";
            description = "传说中的护裙，赋予持有者神秘的力量。";
            money = 600;
            add_max_hp = 50;
            add_max_mp = 40;
            min_agility_to_equip = 12;
            defence = 8;
            evasion = 15;
            break;
        case 7:
            name = "白虎战甲";
            description = "采用白虎皮制作，拥有极高的防御力，适合正义之士。";
            money = 350;
            add_max_hp = 30;
            add_max_mp = 0;
            min_agility_to_equip = 10;
            defence = 15;
            evasion = 2;
            break;
        case 8:
            name = "流燕斗篷";
            description = "背后有流燕图案，轻便灵动，适合追风的侠客。";
            money = 420;
            add_max_hp = 15;
            add_max_mp = 30;
            min_agility_to_equip = 15;
            defence = 5;
            evasion = 30;
            break;
        case 9:
            name = "天蚕丝甲";
            description = "由天蚕丝织成的甲衣，轻便舒适，防御力惊人。";
            money = 500;
            add_max_hp = 80;
            add_max_mp = 40;
            min_agility_to_equip = 22;
            defence = 30;
            evasion = 15;
            break;
        case 10:
            name = "龙鳞护甲";
            description = "传说中龙族遗留下来的护甲，拥有无与伦比的防御力。";
            money = 1000;
            add_max_hp = 200;
            add_max_mp = 0;
            min_agility_to_equip = 10;
            defence = 60;
            evasion = 10;
            break;
        case 11:
            name = "幽冥披风";
            description = "来自幽冥之地的神秘披风，赋予佩戴者如幽灵般的闪避能力。";
            money = 800;
            add_max_hp = 50;
            add_max_mp = 70;
            min_agility_to_equip = 20;
            defence = 20;
            evasion = 30;
            break;
        case 12:
            name = "玄铁重铠";
            description = "以玄铁打造的重铠，防御力无可匹敌，适合重型战士。";
            money = 1100;
            add_max_hp = 250;
            add_max_mp = 0;
            min_agility_to_equip = 23;
            defence = 70;
            evasion = 5;
            break;
        case 13:
            name = "七彩羽衣";
            description = "用彩凤的羽毛编织而成，既轻盈又具备强大的防御力。";
            money = 1400;
            add_max_hp = 100;
            add_max_mp = 60;
            min_agility_to_equip = 25;
            defence = 45;
            evasion = 60;
            break;
        case 14:
            name = "守护之铠";
            description = "寄托着守护之神的庇护的铠甲，具有至高的防御力";
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
            name = "青锋剑";
            description = "剑身如秋水，剑锋如青虹，传闻能削铁如泥。";
            money = 300;
            damage = 50;
            min_strength_to_equip = 10;
            critical = 15;
            break;
        case 1:
            name = "玄铁重剑";
            description = "以玄铁铸成，沉重无比，唯有绝世高手方能驾驭。";
            money = 800;
            damage = 120;
            min_strength_to_equip = 30;
            critical = 5;
            break;
        case 2:
            name = "金蛇剑";
            description = "剑身如蛇，灵动多变，出招诡异莫测，难以捉摸。";
            money = 500;
            damage = 70;
            min_strength_to_equip = 15;
            critical = 20;
            break;
        case 3:
            name = "打狗棍";
            description = "丐帮祖传武器，看似平凡无奇，却是威力无穷。";
            money = 400;
            damage = 60;
            min_strength_to_equip = 10;
            critical = 10;
            break;
        case 4:
            name = "霜寒刀";
            description = "刀光如雪，寒气逼人，斩敌如同冰封世界。";
            money = 600;
            damage = 90;
            min_strength_to_equip = 20;
            critical = 18;
            break;
        case 5:
            name = "九环大刀";
            description = "刀身带有九环，挥舞之间震耳欲聋，霸气十足。";
            money = 700;
            damage = 100;
            min_strength_to_equip = 25;
            critical = 12;
            break;
        case 6:
            name = "赤焰剑";
            description = "剑身如烈焰燃烧，传说中能燃尽一切邪恶。";
            money = 650;
            damage = 85;
            min_strength_to_equip = 18;
            critical = 20;
            break;
        case 7:
            name = "倚天剑";
            description = "天下神器，剑中至宝，江湖传言“倚天不出，谁与争锋”。";
            money = 1200;
            damage = 150;
            min_strength_to_equip = 28;
            critical = 25;
            break;
        case 8:
            name = "银月弯刀";
            description = "刀如弯月，出招如月影流转，刀光如银，难以防范。";
            money = 500;
            damage = 75;
            min_strength_to_equip = 12;
            critical = 22;
            break;
        case 9:
            name = "霸王枪";
            description = "枪中之王，气势如虹，枪出如龙，威震八方。";
            money = 1000;
            damage = 130;
            min_strength_to_equip = 35;
            critical = 15;
            break;
        case 10:
            name = "木棍";
            description = "普通的木棍，适合初学者使用。";
            money = 10;
            damage = 10;
            min_strength_to_equip = 5;
            critical = 0;
            break;
        default:
            break;
    }
}
