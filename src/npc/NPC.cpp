#include "NPC.h"

#include <algorithm>
#include <fstream>
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

void TaskGivingNPC::giveReward() const
{
    fmt::print("这是我的谢礼: \n");
    fmt::print("获得了{}经验\t", Tasks[task_id[0]].getExperience());
    Gamer.gainExp(Tasks[task_id[0]].getExperience());
    fmt::print("获得了{}元钱\n", Tasks[task_id[0]].getExperience());
    Gamer.gainMoney(Tasks[task_id[0]].getMoney());
    if (Tasks[task_id[0]].getSkillId() != -1)
        print(fg(fmt::color::yellow), "习得{}技能", Skills[Tasks[task_id[0]].getSkillId()].getName());
    Gamer.gainSkill(Tasks[task_id[0]].getSkillId());
}

NPC::NPC() = default;

NPC::NPC(std::string name, std::string description, std::vector<std::string> dialogues): name(std::move(name)), description(std::move(description)), dialogues(std::move(dialogues)) { }

NPC::~NPC() = default;

TaskGivingNPC::TaskGivingNPC(std::string name, std::string description, std::vector<std::string> dia, std::vector<int> task_id): NPC(std::move(name), std::move(description), std::move(dia)), task_id(std::move(task_id)) { }

void TaskGivingNPC::talk()
{
    if (task_id.empty()) {
        // 所有任务都完成
        print(fg(fmt::color::green), "{}: ", name);
        printSlowly(format(fg(fmt::color::green), dialogues[0]));
        fmt::print("\n");
        return;
    }
    if (Tasks[task_id[0]].ifTaskFinished()) {
        fmt::print("感谢你帮助了我\n");
        giveReward();
        Gamer.removeTask(Tasks[task_id[0]]);
        task_id.erase(task_id.begin());
        dialogues.erase(dialogues.begin() + 1);
        if_give_task = true;
        return;
    }
    if (Tasks[task_id[0]].ifReceived()) {
        fmt::print("你当前应该有别的事情要做。\n");
        return;
    }
    //如果有任务要给

    print(fg(fmt::color::green), "{}: ", name);
    printSlowly(format(fg(fmt::color::green), dialogues[1]));
    fmt::print("\n");
    std::string choice;
    fmt::print("是否接受请求[yes / no]: ");
    std::cin >> choice;
    while (choice != "yes" && choice != "no") {
        fmt::print("错误指令，请重新输入[yes / no]: ");
        std::cin >> choice;
    }
    if (choice == "yes") {
        Gamer.acceptTask(Tasks[task_id[0]]);
        Tasks[task_id[0]].receive();
        fmt::print("你已经接受了这份任务，快点查看一下[self]。\n");
    }
    waitForAnyKey();
}

void TaskGivingNPC::save()
{
    const string path = "../files/" + Gamer.getName() + "/npc.dat";
    ofstream file(path, ios::binary);
    for (auto &npc : TaskGivingNPCs) {
        size_t count = npc.task_id.size();
        file.write(reinterpret_cast<char *>(&count), sizeof(count));
    }
}

void TaskGivingNPC::load()
{
    const string path = "../files/" + Gamer.getName() + "/npc.dat";
    ifstream file(path, ios::binary);
    for (auto &npc : TaskGivingNPCs) {
        size_t count;
        file.read(reinterpret_cast<char *>(&count), sizeof(count));
        while (npc.task_id.size() > count) {
            npc.task_id.erase(npc.task_id.begin());
            npc.dialogues.erase(npc.dialogues.begin() + 1);
        }
    }
}

int TaskGivingNPC::getTaskId() const { return task_id[0]; }

ShopKeeper::ShopKeeper() = default;

ShopKeeper::ShopKeeper(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &weapons_id, const std::vector<int> &armors_id, const std::array<int, 6> &pill_num): NPC(std::move(name), std::move(description), std::move(dia))
{
    for (const int id : armors_id) {
        if (id == -1) { break; }
        armors.push_back(Armors[id]);
    }
    for (const int id : weapons_id) {
        if (id == -1) { break; }
        weapons.push_back(Weapons[id]);
    }
    int i = 0;
    for (auto it = pills.begin(); it != pills.end(); ++it, ++i) { it->second = pill_num[i]; }
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

void ShopKeeper::setPillNum(const Pill &pill, const int pill_num)
{
    const auto it = pills.find(pill);
    it->second -= pill_num;
}

void ShopKeeper::enterStore()
{
    while (true) {
        fmt::print("你想买点什么东西[buy]，还是卖点什么呢[sell]？输入[out]退出:");
        string choice;
        cin >> choice;
        if (choice == "out") { break; }
        if (choice == "buy") {
            showGoods();
            buy();
            continue;
        }
        if (choice == "sell") {
            Gamer.showBag();
            sell();
            continue;
        }
        fmt::print("错误指令，请重新输入: ");
    }
}

void ShopKeeper::showGoods()
{
    if (weapons.size() != 1 && armors.size() != 1) {
        fmt::print("武器: \n");
        int i = 0;
        for (auto &weapon : weapons) {
            if (i != 0)
                fmt::print("{}.", i);
            weapon.showAttributes();
            this_thread::sleep_for(chrono::milliseconds(50));
            ++i;
        }
        i = 0;
        fmt::println("护甲:");
        for (auto &armor : armors) {
            if (i != 0)
                fmt::print("{}.", i);
            armor.showAttributes();
            this_thread::sleep_for(chrono::milliseconds(50));
            ++i;
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
            print(fg(fmt::color::green), "欢迎下次光临。\n");
            return;
        }
    }
    buyPills();
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
                fmt::print("不得购买超过10瓶。\n");
            else
                break;
        }
        else
            fmt::print("你输入的不是数字，请重新输入: ");
    }

    int total_cost = price_per_unit * quantity;

    // 检查玩家是否有足够的钱
    if (Gamer.getMoney() < total_cost) {
        fmt::print("你的钱不够，无法购买。\n");
        return;
    }

    // 处理购买逻辑
    if (getPillNum(pill_buy) < quantity) {
        fmt::print("没有这么多瓶药，购买失败！\n");
        return;
    }
    int result = Gamer.gainPill(pill_buy, quantity);
    total_cost = result * price_per_unit;
    Gamer.gainMoney(-total_cost); // 减少玩家的钱
    if (result == quantity) {
        fmt::print("你购买了{}瓶{}，花费{}元。\n", input, pill_buy.getPillName(), total_cost);
    }
    else {
        fmt::print("你的背包有限，无法装下剩余的{}颗丹药，共装下了{}颗丹药。\n", quantity - result, result);
    }
    setPillNum(pill_buy, result); //减少商户的丹药
}

void ShopKeeper::buyWeapon()
{
    if (weapons.empty()) {
        fmt::print("没有武器可买。\n");
        return;
    }
    string input;
    int pos;
    fmt::print("你想买哪件(请输入其编号, 0是退出): ");
    while (true) {
        cin >> input;
        if (input.empty() && !all_of(input.begin(), input.end(), ::isdigit)) {
            fmt::print("请输入对的编号: ");
            continue;
        }
        pos = stoi(input);
        if (pos == 0)
            return;
        if (0 < pos && pos < weapons.size()) {
            break;
        }
        fmt::print("请输入对的编号: ");
    }

    const Weapon &selected_weapon = weapons[pos];
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
    weapons.erase(weapons.begin() + pos); //买完了商店里就没有了
}

void ShopKeeper::buyArmor()
{
    if (armors.empty()) {
        fmt::print("没有护甲可买。\n");
        return;
    }
    string input;
    int pos;
    fmt::print("你想买哪件(请输入其编号, 0是退出): ");
    while (true) {
        cin >> input;
        if (input.empty() && !all_of(input.begin(), input.end(), ::isdigit)) {
            fmt::print("请输入对的编号: ");
            continue;
        }
        pos = stoi(input);
        if (pos == 0)
            return;
        if (0 < pos && pos < weapons.size()) {
            break;
        }
        fmt::print("请输入对的编号: ");
    }

    const Armor &selected_armor = armors[pos];
    int armor_price = selected_armor.getMoney();

    // 检查玩家是否有足够的钱
    if (Gamer.getMoney() < armor_price) {
        fmt::print("你的钱不够，无法购买{}。\n", selected_armor.getName());
        return;
    }

    Gamer.gainMoney(-armor_price); // 减少玩家的钱
    Gamer.buyArmor(selected_armor);
    fmt::print("你成功购买了{}，花费{}元。\n", selected_armor.getName(), armor_price);
    armors.erase(armors.begin() + pos);
}

void ShopKeeper::sell()
{
    fmt::print("你想卖什么，武器[weapon]、护甲[armor]、退出[out]: ");
    string choice;
    cin >> choice;
    while (choice != "weapon" && choice != "armor" && choice != "out") {
        fmt::print("错误指令，请重新输入: ");
        cin >> choice;
    }
    if (choice == "armor") { sellArmor(); }
    else if (choice == "out") { return; }
    else { sellWeapon(); }
}

void ShopKeeper::sellArmor()
{
    if (Gamer.getArmors().empty() || Gamer.getArmors().size() == 1) {
        fmt::print("无装备可卖\n");
        return;
    }
    string input;
    int pos;
    fmt::print("你想卖哪件(请输入其编号, 0是退出): ");
    while (true) {
        cin >> input;
        if (input.empty() && !all_of(input.begin(), input.end(), ::isdigit)) {
            fmt::print("请输入对的编号: ");
            continue;
        }
        pos = stoi(input);
        if (pos == 0) {
            return;
        }
        if (0 < pos && pos < Gamer.getArmors().size()) {
            break;
        }
        fmt::print("请输入对的编号: ");
    }

    const Armor &selected_armor = Gamer.getArmors()[pos];
    int armor_price = selected_armor.getMoney();

    Gamer.gainMoney(static_cast<int>(armor_price * 0.7));
    Gamer.sellArmor(selected_armor); //去掉背包里的装备
    fmt::print("卖掉了{}，得到了{}钱\n", selected_armor.getName(), armor_price);
    armors.push_back(selected_armor); //卖给商店之后还可以再买回来
}

void ShopKeeper::sellWeapon()
{
    if (Gamer.getWeapons().empty() || Gamer.getWeapons().size() == 1) {
        fmt::print("无装备可卖\n");
        return;
    }
    string input;
    int pos;
    fmt::print("你想买哪件(请输入其编号, 0是退出):");
    while (true) {
        cin >> input;
        if (input.empty() && !all_of(input.begin(), input.end(), ::isdigit)) {
            fmt::print("请输入对的编号: ");
            continue;
        }
        pos = stoi(input);
        if (pos == 0)
            return;
        if (0 < pos && pos < Gamer.getWeapons().size()) {
            break;
        }
        fmt::print("请输入对的编号\n");
    }

    const Weapon &selected_weapon = Gamer.getWeapons()[pos - 1];
    int weapon_price = selected_weapon.getMoney();

    Gamer.gainMoney(Gamer.getMoney() + static_cast<int>(weapon_price * 0.7));
    Gamer.sellWeapon(selected_weapon);
    fmt::print("卖掉了{}，得到了{}钱\n", selected_weapon.getName(), weapon_price);
    weapons.push_back(selected_weapon);
}
