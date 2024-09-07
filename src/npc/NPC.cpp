#include "NPC.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "Helper.h"
#include "Player.h"
#include "fmt/core.h"

extern Player Player;

using namespace std;

void TaskGivingNPC::giveTask() const { Player.acceptTask(tasks[task_index]); }

bool TaskGivingNPC::ifFinishTask() const { return tasks[task_index].ifTaskFinished(); }

void TaskGivingNPC::giveReward() const
{
    fmt::print("这是我的谢礼\n");
    fmt::println("获得了{}经验", tasks[task_index].getExperience());
    Player.gainExp(tasks[task_index].getExperience());
    fmt::println("获得了{}元钱", tasks[task_index].getExperience());
    Player.gainMoney(tasks[task_index].getMoney());
    fmt::print("习得{}技能", Tasks[tasks[task_index].getSkillId()].getName());
    Player.gainSkill(tasks[task_index].getSkillId());
}

NPC::NPC() = default;

NPC::NPC(std::string name, std::string description, std::vector<std::string> dialogues): name(std::move(name)), description(std::move(description)), dialogues(std::move(dialogues)) { }

NPC::~NPC() = default;

TaskGivingNPC::TaskGivingNPC(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &task_id): NPC(std::move(name), std::move(description), std::move(dia))
{
    for (const int id : task_id) {
        if (id == -1) {
            break;
        }
        tasks.push_back(Tasks[id]);
    }
}

void TaskGivingNPC::talk()
{
    system("cls");
    if (ifFinishTask() == true && if_give_reward == true) {
        fmt::print("感谢你帮助了我\n");
        giveReward();
        Player.removeTask(tasks[task_index]);
        //最后一个任务做完，就不能再给奖励和发任务了
        if (task_index == tasks.size() - 1) {
            if_give_reward = false;
            if_give_task = false;
        }
        task_index++;
        if_give_task = true;
        return;
    }
    //如果有任务要给
    if (if_give_task == true) {
        fmt::print("{} : ", name);
        printSlowly(dialogues[task_index + 1], 50);
        fmt::print("\n");
        std::string choice;
        std::cin >> choice;
        fmt::print("是否接受请求[yes],[no]");
        while (choice != "yes" && choice != "no") {
            fmt::print("错误指令！\n");
            std::cin >> choice;
        }
        if (choice == "yes") {
            giveTask();
            if_give_task = false; //上一个任务没完成时不能接受新任务
            return;
        }
    }
    //所有任务都完成
    fmt::print("{} : ", name);
    printSlowly(dialogues[0], 50);
    fmt::print("\n");
}


void ShopKeeper::setPillNum(const Pill &pill, const int pill_num)
{
    const auto it = pills.find(pill);
    it->second -= pill_num;
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
        string choice;
        cin >> choice;
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

void ShopKeeper::buyPills()
{
    fmt::print("你想什么类型的药品，");
    print(fg(fmt::color::red), "回血丹");
    fmt::print("[red]还是");
    print(fg(fmt::color::blue), "回元丹");
    fmt::print("[blue]: ");

    string pill_type;
    cin >> pill_type;
    while (pill_type != "red" && pill_type != "blue") {
        fmt::print("错误指令！\n");
        cin >> pill_type;
    }

    fmt::print("你想要什么大小的药品，大[big]、中[mid]还是小[small]:");
    string pill_size;
    cin >> pill_size;
    while (pill_size != "big" && pill_size != "mid" && pill_size != "small") {
        fmt::print("错误指令！\n");
        cin >> pill_size;
    }

    Pill pill_buy {Pill::Type::BLOOD_PILL, Pill::Size::BIG};
    int price_per_unit = 0;
    // 根据药品类型和大小设置价格
    if (pill_type == "blue") {
        pill_buy.type = Pill::Type::MANA_PILL;
    }

    if (pill_size == "big") {
        price_per_unit = 100;
    }
    else if (pill_size == "mid") {
        price_per_unit = 80;
        pill_buy.size = Pill::Size::MID;
    }
    else {
        price_per_unit = 50;
        pill_buy.size = Pill::Size::SMALL;
    }

    fmt::print("你想购买多少瓶(不超过10瓶)？:");
    string input;
    int quantity = 0;
    while (true) {
        cin >> input;
        if (!input.empty() && all_of(input.begin(), input.end(), ::isdigit)) {
            quantity = stoi(input);
            if (quantity > 10)
                fmt::print("不得购买超过10瓶");
            else
                break;
        }
        else
            fmt::print("你输入的不是数字，请重新输入。");
    }

    int total_cost = price_per_unit * quantity;

    // 检查玩家是否有足够的钱
    if (Player.getMoney() < total_cost) {
        fmt::print("你的钱不够，无法购买。\n");
        return;
    }

    // 处理购买逻辑
    if (getPillNum(pill_buy) < quantity) {
        fmt::print("没有这么多瓶药，购买失败！");
        return;
    }
    int result = Player.gainPill(pill_buy, quantity);
    total_cost = result * price_per_unit;
    Player.gainMoney(-total_cost); // 减少玩家的钱
    if (result == quantity) {
        fmt::print("你购买了{}瓶{}，花费{}元。\n", input, pill_buy.getPillName(), total_cost);
    }
    else {
        fmt::print("你的背包有限，无法装下剩余的{}颗丹药，共装下了{}颗丹药。", quantity - result, result);
    }
    setPillNum(pill_buy, result); //减少商户的丹药
}

void ShopKeeper::buyWeapon()
{
    fmt::print("你想购买哪件武器？请输入武器名称:\n");
    string weapon_name;
    cin >> weapon_name;

    // 查找玩家选择的武器
    const auto it = find_if(weapons.begin(), weapons.end(), [&](const Weapon &weapon) {
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
    string armor_name;
    cin >> armor_name;

    // 查找玩家选择的护甲
    const auto it = find_if(armors.begin(), armors.end(), [&](const Armor &armor) {
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
    string choice1;
    cin >> choice1;
    while (choice1 != "weapon" && choice1 != "armor" && choice1 != "pill") {
        fmt::print("错误指令！\n");
        cin >> choice1;
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
    string armorName;
    cin >> armorName;
    // 查找玩家选择的护甲
    const auto it = find_if(armors.begin(), armors.end(), [&](const Armor &armor) {
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
    string weapon_name;
    cin >> weapon_name;

    // 查找玩家选择的武器
    const auto it = find_if(weapons.begin(), weapons.end(), [&](const Weapon &weapon) {
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
    string choice1;
    cin >> choice1;
    while (choice1 != "weapon" && choice1 != "armor") {
        fmt::print("错误指令！\n");
        cin >> choice1;
    }
    if (choice1 == "armor") {
        sellArmor();
    }
    else {
        sellWeapon();
    }
}


ShopKeeper::ShopKeeper(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &weapons_id, const std::vector<int> &armors_id): NPC(std::move(name), std::move(description), std::move(dia))
{
    for (const int id : armors_id) {
        if (id == -1) {
            break;
        }
        armors.push_back(Armors[id]);
    }
    for (const int id : weapons_id) {
        if (id == -1) {
            break;
        }
        weapons.push_back(Weapons[id]);
    }
}

void ShopKeeper::talk()
{
    system("cls");
    fmt::print("{} : {}", name, dialogues[0]);
    fmt::print("要来看看我的店铺吗[yes]或[no]:");
    string choice;
    cin >> choice;
    while (choice != "yes" && choice != "no") {
        fmt::print("错误指令！\n");
        cin >> choice;
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
