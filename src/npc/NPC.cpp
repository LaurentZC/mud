#include "NPC.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Player.h"
#include "fmt/core.h"

extern Player Player;

void TaskGivingNPC::giveTask() const { Player.acceptTask(task); }

bool TaskGivingNPC::ifFinishTask() const { return task.ifTaskFinished(); }

void TaskGivingNPC::giveReward() const
{
    fmt::print("这是我的谢礼\n");
    fmt::println("获得了{}经验", task.getExperience());
    Player.gainExp(task.getExperience());
    fmt::println("获得了{}元钱", task.getExperience());
    Player.gainMoney(task.getMoney());
    Player.gainSkill(task.getSkillId());
}

void TaskGivingNPC::talk()
{
    system("cls");
    if (ifFinishTask() == true && if_give_reward == true) {
        fmt::print("感谢你帮助了我\n");
        giveReward();
        if_give_reward = false;
        return;
    }
    if (if_first_talk) {
        fmt::print("{} : 你是外来的旅人吧，能不能{}。[yes]接受,[no]拒绝:", name, task.getDescription());
        std::string choice;
        std::cin >> choice;
        while (choice != "yes" && choice != "no") {
            fmt::print("错误指令！\n");
            std::cin >> choice;
        }
        if (choice == "yes") {
            giveTask();
            if_first_talk = false;
        }
    }
    else {
        fmt::print("{}", dialogue);
    }
}

void ShopKeeper::showGoods()
{
    system("cls");
    fmt::print("武器: \n");
    for (auto &weapon : weapons) {
        weapon.showAttributes();
    }
    fmt::println("护甲:");
    for (auto &armor : armors) {
        armor.showAttributes();
    }
    fmt::println("药品: ");
    for (auto &[pill, count] : pills) {
        fmt::print("{} : {}", pill.getPillName(), count);
    }
}


void ShopKeeper::enterStore()
{
    while (true) {
        system("cls");
        fmt::print("你想买入[buy]还是卖出[sell],输入[out]退出:");
        std::string choice;
        std::cin >> choice;
        if (choice == "out") { break; }
        if (choice == "sell") {
            Player.openBag();
            sell();
        }
        else {
            showGoods();
            buy();
        }
        fmt::print("错误指令！\n");
    }
}

void ShopKeeper::buyPills() const
{
    fmt::print("你想什么类型的药品，回血丹[red]还是定神丹[blue]:");
    std::string choice2;
    std::cin >> choice2;
    while (choice2 != "red" && choice2 != "blue") {
        fmt::print("错误指令！\n");
        std::cin >> choice2;
    }

    fmt::print("你想要什么大小的药品，大[big]、中[mid]还是小[small]:");
    std::string choice3;
    std::cin >> choice3;
    while (choice3 != "big" && choice3 != "mid" && choice3 != "small") {
        fmt::print("错误指令！\n");
        std::cin >> choice3;
    }

    fmt::print("你想购买多少瓶(不超过10瓶)？:");
    std::string input;
    bool error = false;
    int quantity = 0;
    do {
        error = false;
        std::cin >> input;
        for (const auto c : input) {
            if (!isdigit(c)) {
                fmt::print("你输入了非数字。");
                error = true;
                break;
            }
        }
        if (!error) {
            quantity = stoi(input);
            if (quantity > 10) {
                fmt::print("不得购买超过10瓶");
                error = true;
            }
        }
    } while (error);

    Pill::Size size = {};
    int price_per_unit = 0;

    // 根据药品类型和大小设置价格
    if (choice2 == "red") {
        if (choice3 == "big") {
            price_per_unit = 100;
            size = Pill::Size::BIG;
        }
        else if (choice3 == "mid") {
            price_per_unit = 80;
            size = Pill::Size::MID;
        }
        else {
            price_per_unit = 50;
            size = Pill::Size::SMALL;
        }
    }
    else if (choice2 == "blue") {
        if (choice3 == "big") {
            price_per_unit = 200;
            size = Pill::Size::BIG;
        }
        else if (choice3 == "mid") {
            price_per_unit = 120;
            size = Pill::Size::MID;
        }
        else {
            price_per_unit = 60;
            size = Pill::Size::SMALL;
        }
    }

    int total_cost = price_per_unit * quantity;

    // 检查玩家是否有足够的钱
    if (Player.getMoney() < total_cost) {
        fmt::print("你的钱不够，无法购买。\n");
        return;
    }

    // 处理购买逻辑
    if (choice2 == "red") {
        const Pill red_pill = {Pill::Type::BLOOD_PILL, size};
        if (getPillNum(red_pill) < quantity) {
            fmt::print("没有这么多瓶药，购买失败！");
            return;
        }
        const int result = Player.gainPill(red_pill, quantity);
        total_cost = result * price_per_unit;
        Player.gainMoney(-total_cost); // 减少玩家的钱
        if (result == quantity) {
            fmt::print("你购买了{}瓶{}大小的回血丹，花费{}元。\n", input, choice3, total_cost);
        }
        else {
            fmt::print("你的背包有限，无法装下剩余的{}颗丹药。", quantity - result);
        }
    }
    else if (choice2 == "blue") {
        const auto blue_pill = Pill {Pill::Type::MANA_PILL, size};
        if (getPillNum(blue_pill) < quantity) {
            fmt::print("没有这么多瓶药，购买失败！");
            return;
        }
        int result = Player.gainPill(blue_pill, quantity);
        total_cost = result * price_per_unit;
        Player.gainMoney(-total_cost); // 减少玩家的钱
        if (result == quantity) {
            fmt::print("你购买了{}瓶{}大小的回元丹，花费{}元。\n", input, choice3, total_cost);
        }
        else {
            fmt::print("你的背包有限，无法装下剩余的{}颗丹药。", quantity - result);
        }
    }
}

void ShopKeeper::buyWeapon()
{
    fmt::print("你想购买哪件武器？请输入武器名称:\n");
    std::string weapon_name;
    std::cin >> weapon_name;

    // 查找玩家选择的武器
    const auto it = std::find_if(weapons.begin(), weapons.end(), [&](const Weapon &weapon) {
        return weapon.getName() == weapon_name;
    });

    if (it == weapons.end()) {
        fmt::print("未找到该武器，请检查名称。\n");
        return;
    }

    const Weapon &selected_weapon = *it;
    int weapon_price = selected_weapon.getMoney();

    // 检查玩家是否有足够的钱
    if (Player.getMoney() < weapon_price) {
        fmt::print("你的钱不够，无法购买{}。\n", selected_weapon.getName());
        return;
    }

    // 处理购买逻辑
    Player.gainMoney(weapon_price);    // 减少玩家的钱
    Player.buyWeapon(selected_weapon); //添加装备至背包
    fmt::print("你成功购买了{}，花费{}元。\n", selected_weapon.getName(), weapon_price);
    weapons.erase(it); //买完了商店里就没有了
}

void ShopKeeper::buyArmor()
{
    fmt::print("你想购买哪件护甲？请输入护甲名称:\n");
    std::string armor_name;
    std::cin >> armor_name;

    // 查找玩家选择的护甲
    const auto it = std::find_if(armors.begin(), armors.end(), [&](const Armor &armor) {
        return armor.getName() == armor_name;
    });

    if (it == armors.end()) {
        fmt::print("未找到该护甲，请检查名称。\n");
        return;
    }

    const Armor &selected_armor = *it;
    int armor_price = selected_armor.getMoney();

    // 检查玩家是否有足够的钱
    if (Player.getMoney() < armor_price) {
        fmt::print("你的钱不够，无法购买{}。\n", selected_armor.getName());
        return;
    }

    Player.gainMoney(-armor_price); // 减少玩家的钱
    Player.buyArmor(selected_armor);
    fmt::print("你成功购买了{}，花费{}元。\n", selected_armor.getName(), armor_price);
    armors.erase(it);
}


void ShopKeeper::buy()
{
    fmt::print("你想买什么，武器[weapon]、护甲[armor]还是药品[pill]:");
    std::string choice1;
    std::cin >> choice1;
    while (choice1 != "weapon" && choice1 != "armor" && choice1 != "pill") {
        fmt::print("错误指令！\n");
        std::cin >> choice1;
    }
    if (choice1 == "pill") {
        buyPills();
        return;
    }
    if (choice1 == "weapon") {
        buyWeapon();
        return;
    }
    if (choice1 == "armor") {
        buyArmor();
    }
}

void ShopKeeper::sellArmor()
{
    fmt::print("你想购卖哪件护甲？请输入护甲名称:\n");
    std::string armorName;
    std::cin >> armorName;
    // 查找玩家选择的护甲
    const auto it = std::find_if(armors.begin(), armors.end(), [&](const Armor &armor) {
        return armor.getName() == armorName;
    });

    if (it == armors.end()) {
        fmt::print("未找到该护甲，请检查名称。\n");
        return;
    }

    if (it == armors.begin()) {
        fmt::print("不能卖掉装备中的护甲。\n");
        return;
    }
    const Armor &selected_armor = *it;
    int armorPrice = selected_armor.getMoney();

    Player.gainMoney(static_cast<int>(armorPrice * 0.7));
    Player.sellArmor(selected_armor); //去掉背包里的装备
    fmt::print("卖掉了{}，得到了{}钱\n", selected_armor.getName(), armorPrice);
    armors.push_back(selected_armor); //卖给商店之后还可以再买回来
}

void ShopKeeper::sellWeapon()
{
    fmt::print("你想购买哪件武器？请输入武器名称:\n");
    std::string weapon_name;
    std::cin >> weapon_name;

    // 查找玩家选择的武器
    const auto it = std::find_if(weapons.begin(), weapons.end(), [&](const Weapon &weapon) {
        return weapon.getName() == weapon_name;
    });

    if (it == weapons.end()) {
        fmt::print("未找到该武器，请检查名称。\n");
        return;
    }

    if (it == weapons.begin()) {
        fmt::print("不能卖掉装备中的武器。\n");
        return;
    }

    const Weapon &selected_weapon = *it;
    int weapon_price = selected_weapon.getMoney();

    Player.gainMoney(Player.getMoney() + static_cast<int>(weapon_price * 0.7));
    Player.sellWeapon(selected_weapon);
    fmt::print("卖掉了{}，得到了{}钱\n", selected_weapon.getName(), weapon_price);
    weapons.push_back(selected_weapon);
}

void ShopKeeper::sell()
{
    fmt::print("你想卖什么，武器[weapon]、护甲[armor]");
    std::string choice1;
    std::cin >> choice1;
    while (choice1 != "weapon" && choice1 != "armor") {
        fmt::print("错误指令！\n");
        std::cin >> choice1;
    }
    if (choice1 == "armor") {
        sellArmor();
    }
    else {
        sellWeapon();
    }
}


void ShopKeeper::talk()
{
    system("cls");
    fmt::print("{} : {}", name, dialogue);
    fmt::print("要来看看我的店铺吗[yes]或[no]:");
    std::string choice;
    std::cin >> choice;
    while (choice != "yes" && choice != "no") {
        fmt::print("错误指令！\n");
        std::cin >> choice;
    }
    if (choice == "no")
        return;
    enterStore();
}

int ShopKeeper::getPillNum(const Pill &pill) const
{
    const auto it = pills.find(pill);
    return it != pills.end() ? it->second : 0; // 如果找到，返回数量，否则返回 0
}
