#include "NPC.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

#include "Helper.h"
#include "Player.h"
#include "fmt/core.h"

extern Player Gamer;

using namespace std;

void TaskGivingNPC::giveTask() const { Gamer.acceptTask(tasks[task_index]); }

bool TaskGivingNPC::ifFinishTask() const { return tasks[task_index].ifTaskFinished(); }

void TaskGivingNPC::giveReward() const
{
    fmt::print("这是我的谢礼\n");
    fmt::println("获得了{}经验", tasks[task_index].getExperience());
    Gamer.gainExp(tasks[task_index].getExperience());
    fmt::println("获得了{}元钱", tasks[task_index].getExperience());
    Gamer.gainMoney(tasks[task_index].getMoney());
    fmt::print("习得{}技能", Tasks[tasks[task_index].getSkillId()].getName());
    Gamer.gainSkill(tasks[task_index].getSkillId());
}

NPC::NPC() = default;

NPC::NPC(std::string name, std::string description, std::vector<std::string> dialogues): name(std::move(name)), description(std::move(description)), dialogues(std::move(dialogues)) { }

NPC::~NPC() = default;

TaskGivingNPC::TaskGivingNPC(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &task_id): NPC(std::move(name), std::move(description), std::move(dia))
{
    for (const int id : task_id) {
        if (id == -1) { break; }
        tasks.push_back(Tasks[id]);
    }
}

void TaskGivingNPC::talk()
{
    for (task_index = 0; task_index < tasks.size(); ++task_index) {
        if (!tasks[task_index].ifTaskFinished()) { break; }
    }
    if (ifFinishTask() == true && if_give_reward == true) {
        fmt::print("感谢你帮助了我\n");
        giveReward();
        Gamer.removeTask(tasks[task_index]);
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
        printSlowly(format(fg(fmt::color::green), dialogues[task_index + 1]));
        fmt::print("\n");
        std::string choice;
        std::cin >> choice;
        fmt::print("是否接受请求[yes / no]: ");
        while (choice != "yes" && choice != "no") {
            fmt::print("错误指令，请重新输入[yes / no]: ");
            std::cin >> choice;
        }
        if (choice == "yes") {
            giveTask();
            if_give_task = false; // 上一个任务没完成时不能接受新任务
            fmt::print("你已经接受了这份任务，快点查看一下[self]。");
            return;
        }
    }
    // 所有任务都完成
    fmt::print("{} : ", name);
    printSlowly(format(fg(fmt::color::green), dialogues[0]));
    fmt::print("\n");
}


void ShopKeeper::setPillNum(const Pill &pill, const int pill_num)
{
    const auto it = pills.find(pill);
    it->second -= pill_num;
}

void ShopKeeper::showGoods()
{
    if (weapons.size() != 1 && armors.size() != 1) {
        fmt::print("武器: \n");
        for (auto &weapon : weapons) {
            weapon.showAttributes();
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        fmt::println("护甲:");
        for (auto &armor : armors) {
            armor.showAttributes();
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        return;
    }
    fmt::println("药品: ");
    int i = 1;
    for (auto &[pill, count] : pills) {
        fmt::print("{} : {}", pill.getPillName(), count);
        cout << "\t\n"[i % 3 == 0];
        ++i;
    }
}

void ShopKeeper::enterStore()
{
    while (true) {
        fmt::print("你想买点什么东西[buy]，还是卖点什么呢[sell]？输入[out]退出:");
        string choice;
        cin >> choice;
        if (choice == "out") { break; }
        if (choice == "sell") {
            Gamer.showBag();
            sell();
            continue;
        }
        if (choice == "buy") {
            showGoods();
            buy();
            continue;
        }
        fmt::print("错误指令，请重新输入: ");
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
        fmt::print("错误指令！请重新输入: ");
        cin >> pill_type;
    }

    fmt::print("你想要什么大小的药品，大[big]、中[mid]还是小[small]: ");
    string pill_size;
    cin >> pill_size;
    while (pill_size != "big" && pill_size != "mid" && pill_size != "small") {
        fmt::print("错误指令，请重新输入: ");
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
    if (Gamer.getMoney() < total_cost) {
        fmt::print("你的钱不够，无法购买。\n");
        return;
    }

    // 处理购买逻辑
    if (getPillNum(pill_buy) < quantity) {
        fmt::print("没有这么多瓶药，购买失败！");
        return;
    }
    int result = Gamer.gainPill(pill_buy, quantity);
    total_cost = result * price_per_unit;
    Gamer.gainMoney(-total_cost); // 减少玩家的钱
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
    if (weapons.empty()) {
        fmt::print("没有武器可买");
        return;
    }
    fmt::print("你想购买哪件武器？请输入武器名称: ");
    string weapon_name;
    cin >> weapon_name;
    weapon_name = format(fg(fmt::color::cyan), weapon_name);
    auto it = weapons.begin();
    while (true) {
        // 查找玩家选择的武器
        it = find_if(weapons.begin(), weapons.end(), [&](const Weapon &weapon) {
            return weapon.getName() == weapon_name;
        });

        if (it == weapons.end()) {
            fmt::print("未找到该武器，请检查名称后重新输入: ");
            continue;
        }
        break;
    }
    const Weapon &selected_weapon = *it;
    int weapon_price = selected_weapon.getMoney();

    // 检查玩家是否有足够的钱
    if (Gamer.getMoney() < weapon_price) {
        fmt::print("你的钱不够，无法购买{}。\n", selected_weapon.getName());
        return;
    }

    // 处理购买逻辑
    Gamer.gainMoney(weapon_price);    // 减少玩家的钱
    Gamer.buyWeapon(selected_weapon); //添加装备至背包
    fmt::print("你成功购买了{}，花费{}元。\n", selected_weapon.getName(), weapon_price);
    weapons.erase(it); //买完了商店里就没有了
}

void ShopKeeper::buyArmor()
{
    if (armors.empty()) {
        fmt::print("没有护甲可买");
        return;
    }
    fmt::print("你想购买哪件护甲？请输入护甲名称: ");

    auto it = armors.begin();
    while (true) {
        string armor_name;
        cin >> armor_name;
        armor_name = format(fg(fmt::color::light_green), armor_name);
        // 查找玩家选择的护甲
        it = find_if(armors.begin(), armors.end(), [&](const Armor &armor) {
            return armor.getName() == armor_name;
        });

        if (it == armors.end()) {
            fmt::print("未找到该护甲，请检查名称后重新输入: ");
            continue;
        }
        break;
    }
    const Armor &selected_armor = *it;
    int armor_price = selected_armor.getMoney();

    // 检查玩家是否有足够的钱
    if (Gamer.getMoney() < armor_price) {
        fmt::print("你的钱不够，无法购买{}。\n", selected_armor.getName());
        return;
    }

    Gamer.gainMoney(-armor_price); // 减少玩家的钱
    Gamer.buyArmor(selected_armor);
    fmt::print("你成功购买了{}，花费{}元。\n", selected_armor.getName(), armor_price);
    armors.erase(it);
}


void ShopKeeper::buy()
{
    if (weapons.size() != 1 && armors.size() != 1) {
        fmt::print("你想买什么，武器[weapon]、护甲[armor]、退出[quit]: ");
        string choice;
        cin >> choice;
        while (choice != "weapon" && choice != "armor" && choice != "quit") {
            fmt::print("错误指令，请重新输入: ");
            cin >> choice;
        }
        if (choice == "weapon") {
            buyWeapon();
            return;
        }
        if (choice == "armor") {
            buyArmor();
            return;
        }
        if (choice == "quit") {
            print(fg(fmt::color::green), "欢迎下次光临。");
            return;
        }
    }
    buyPills();
}

void ShopKeeper::sellArmor()
{
    fmt::print("你想购卖哪件护甲？请输入护甲名称: ");
    string armor_name;
    cin >> armor_name;
    // 查找玩家选择的护甲
    const auto it = find_if(armors.begin(), armors.end(), [&](const Armor &armor) {
        return armor.getName() == format(fg(fmt::color::light_green), "{}", armor_name);
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
    int armor_price = selected_armor.getMoney();

    Gamer.gainMoney(static_cast<int>(armor_price * 0.7));
    Gamer.sellArmor(selected_armor); //去掉背包里的装备
    fmt::print("卖掉了{}，得到了{}钱\n", selected_armor.getName(), armor_price);
    armors.push_back(selected_armor); //卖给商店之后还可以再买回来
}

void ShopKeeper::sellWeapon()
{
    fmt::print("你想购买哪件武器？请输入武器名称:\n");
    string weapon_name;
    cin >> weapon_name;

    // 查找玩家选择的武器
    const auto it = find_if(weapons.begin(), weapons.end(), [&](const Weapon &weapon) {
        return weapon.getName() == format(fg(fmt::color::cyan), "{}", weapon_name);
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

    Gamer.gainMoney(Gamer.getMoney() + static_cast<int>(weapon_price * 0.7));
    Gamer.sellWeapon(selected_weapon);
    fmt::print("卖掉了{}，得到了{}钱\n", selected_weapon.getName(), weapon_price);
    weapons.push_back(selected_weapon);
}

void ShopKeeper::sell()
{
    fmt::print("你想卖什么，武器[weapon]、护甲[armor]");
    string choice;
    cin >> choice;
    while (choice != "weapon" && choice != "armor") {
        fmt::print("错误指令，请重新输入: ");
        cin >> choice;
    }
    if (choice == "armor") {
        sellArmor();
    }
    else {
        sellWeapon();
    }
}

ShopKeeper::ShopKeeper() = default;

ShopKeeper::ShopKeeper(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &weapons_id, const std::vector<int> &armors_id, const std::array<int, 6> &pill_num): NPC(std::move(name), std::move(description), std::move(dia))
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
    int i = 0;
    for (auto it = pills.begin(); it != pills.end(); ++it, ++i) {
        it->second = pill_num[i];
    }
}

void ShopKeeper::talk()
{
    print(fg(fmt::color::green), "{} : {}\n", name, dialogues[0]);
    fmt::print("要来看看我的店铺吗[yes]或[no]: ");
    string choice;
    cin >> choice;
    while (choice != "yes" && choice != "no") {
        fmt::print("错误指令，请重新输入: ");
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
