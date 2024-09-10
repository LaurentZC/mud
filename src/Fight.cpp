#include "Fight.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <conio.h>
#include <functional>
#include <iostream>
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include <windows.h>

#include "Helper.h"
#include "fmt/core.h"

extern Player Gamer;

Fight::Fight(const Enemy &enemy): enemy(enemy) { }
Fight::Fight(Enemy &&enemy): enemy(std::move(enemy)) { }

// 获得奖励
void Fight::gainTrophy() const
{
    Gamer.gainExp(enemy.getExperience());
    Gamer.gainMoney(enemy.getMoney());
    if (enemy.getArmor() != -1 &&
        find(Gamer.getArmors().begin(), Gamer.getArmors().end(), Armors[enemy.getArmor()]) == Gamer.getArmors().end()) {
        Gamer.gainArmor(enemy.getArmor());
        fmt::print("你获得了一件新的防具: {}\n", Armors[enemy.getArmor()].getName());
    }
    if (enemy.getWeapon() != -1 &&
        find(Gamer.getWeapons().begin(), Gamer.getWeapons().end(), Weapons[enemy.getWeapon()]) == Gamer.getWeapons().end()) {
        Gamer.gainWeapon(enemy.getWeapon());
        fmt::print("你获得了一件新的武器: {}\n", Weapons[enemy.getWeapon()].getName());
    }
    if (enemy.getSkillId() != -1 &&
        find(Gamer.getSkills().begin(), Gamer.getSkills().end(), Skills[enemy.getSkillId()]) == Gamer.getSkills().end()) {
        Gamer.gainSkill(enemy.getSkillId());
        fmt::print("你观察" + enemy.getName() + "陷入顿悟\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        fmt::print("你习得了一个新的技能: {}\n", Skills[enemy.getSkillId()].getName());
    }
    waitForAnyKey();
}

// 计算伤害
int calculateDamage(const int damage, const int defence)
{
    const double reduction_rate = static_cast<double>(defence) / (100.0 + static_cast<double>(defence));
    return static_cast<int>((1 - reduction_rate) * static_cast<double>(damage));
}

// 清状态
void clearBuff(const std::vector<Skill>::iterator &skill)
{
    Gamer.setDamage(Gamer.getDamage() - skill->getAddDamage());
    Gamer.setDefence(Gamer.getDefence() - skill->getAddDamage());
    Gamer.setCritical(Gamer.getCritical() - skill->getAddCritical());
}

void Fight::attackEnemy()
{
    int damage = 0;
    if (achievePercent(Gamer.getCritical())) {
        damage = calculateDamage(Gamer.getDamage() * 2, enemy.getDefence());
        enemy.decHp(damage);
        fmt::print("你对{}造成了{}点暴击伤害。\n", enemy.getName(), damage);
        return;
    }
    damage = calculateDamage(Gamer.getDamage(), enemy.getDefence());
    enemy.decHp(damage);
    fmt::print("你对{}造成了{}点伤害。\n", enemy.getName(), damage);
}

void Fight::attackPlayer(const int defence) const
{
    int damage = 0;
    if (achievePercent(enemy.getCritical())) {
        damage = calculateDamage(enemy.getDamage() * 2, defence);
        Gamer.setHp(Gamer.getHp() - damage);
        fmt::print("{}对你造成了{}点暴击伤害。\n", enemy.getName(), damage);
        return;
    }
    damage = calculateDamage(enemy.getDamage(), defence);
    Gamer.setHp(Gamer.getHp() - damage);
    fmt::print("{}对你造成了{}点伤害。\n", enemy.getName(), damage);
}

bool Fight::useSkill()
{
    if (!Gamer.checkSkill()) {
        fmt::println("你没有习得任何技能！");
        return false;
    }
    std::string input;
    int pos;
    fmt::print("你想用哪个技能[请输入其编号，0是退出]: ");
    while (true) {
        std::cin >> input;
        if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) {
            pos = std::stoi(input);
            if (pos == 0) {
                fmt::print("放弃使用技能。\n");
                return false;
            }
            if (pos <= Gamer.getSkills().size()) { break; }
        }
        fmt::print("请输入对的编号: ");
    }
    const auto skill = Gamer.getSkills()[pos - 1];
    const auto check = Skills[skill.getId()].use();
    if (!check.has_value()) {
        fmt::print("元气不足，无法释放。\n");
        return false;
    }
    if (check.value() != 0) {
        fmt::print("你对{}造成了{}点伤害。\n", enemy.getName(), check.value() + Gamer.getDamage());
        Gamer.setMp(Gamer.getMp() - check.value());
        enemy.decHp(check.value());
    }
    return true;
}

// 弹反
std::atomic<bool> KeyPressed(false);
std::atomic<bool> EndTread(false);

void listenForKey(const char key_to_detect)
{
    while (!KeyPressed && !EndTread) {
        if (_kbhit()) {
            if (const char ch = static_cast<char>(_getch()); ch == key_to_detect) {
                KeyPressed = true;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool ifSucceedDodge()
{
    KeyPressed = false;
    EndTread = false;
    if (achievePercent(Gamer.getEvasion())) { return true; }
    constexpr char target_key = 'k'; // 目标按键
    constexpr int time_limit = 90;   // 时间限制，单位毫秒

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(1, 3);
    const std::chrono::seconds sec(dis(gen));

    fmt::print("出现进度条后，在结束前按下 '{}' 键！\n", target_key);

    std::thread press(listenForKey, target_key);
    const auto start = std::chrono::steady_clock::now();
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (KeyPressed) {
            EndTread = true;
            press.join();
            fmt::print("失败: 按键太早.\n");
            return false;
        }
        // @formatter:off
        if (auto elapsed = std::chrono::steady_clock::now() - start;
            std::chrono::duration_cast<std::chrono::seconds>(elapsed) > sec) {
            // @formatter:on
            EndTread = true;
            press.join();
            break;
        }
    }
    EndTread = false;
    fmt::println("开始！");
    // 启动进度条线程
    std::thread load_thread(waitForLoad, time_limit);
    // 启动按键监听线程
    std::thread key_listener(listenForKey, target_key);
    // 等待线程结束
    load_thread.join();
    EndTread = true;
    key_listener.join();

    if (KeyPressed) {
        fmt::println("闪身！");
        return true;
    }
    fmt::println("超时: 失败");
    return false;
}

void success()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    fmt::print(R"(
                  |       ||                |||
                 |||||||||||          |     ||
                ||| || |||||      ||||||    ||
               |||  |||||||        ||||| |  ||
              ||  |  ||||||        || || || ||
             ||  ||| |||||         ||||| || |||||
                 ||                ||||| ||||||||
                ||     ||||        || ||||||||
               |||  ||||||         |  ||||  ||
              ||||      |||||      ||||||   ||||
             || ||||||||||||||    |||||| |||||||
            ||  ||||||  ||        ||  ||  ||||
           ||   ||  ||  ||        ||  ||    ||
                ||   |  ||        |   ||    || |||
               |||      ||       || |||||||||||||||
               |||    | ||       |   |||||
               ||     ||||      ||   ||
                       ||:
    )");
    system("pause");
    system("cls");
}

void defeat()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    fmt::print(R"(
                                         |                                        ||
                       ||                |||                    |||               |||
              |   ||   |||                ||              ||     ||                ||
              |||  ||  ||                 || |||          |||    ||                || ||
               ||  || |||||||             ||  |||         |||    ||               ||||||
                      |||||          |||| ||  ||         || ||   || |||         ||||||
            ||   ||||||  ||       ||||||| ||||||        ||  ||||||||||||           ||  ||
            |||||||| |||||||       |  |||||||||        ||||||||| ||           ||||||||||||
             ||   |   || ||        || |||| |  ||       |||||     ||            ||||||  |||
               | ||||  |||          ||||   |||||       |  ||     || |          ||  || |||
              || ||||  || |||        |||   ||||          |||||||||||||          |||||||
              |||| | |||||||||       ||||   ||          ||||  ||||  |           | ||||
             ||||  |||  ||          || || ||||          || |||||||||||           |||||||
            ||||  ||    ||         ||   |||| ||  |      ||||| |||   ||          || || ||||
            |||  |||    ||        ||   ||||  ||| |    |||||   ||    |         |||  ||  ||||||
             |   ||     ||       ||   |||     ||||     ||     ||  |||       ||||   ||   ||||||
                     |||||                     |||             ||||||      |||     ||
                      |||                       ||                                 ||
                       ||                                                          ||:
    )");
    waitForAnyKey();
    system("cls");
}


// 赢了返回true
void Fight::fight(const std::function<void(Player &, Enemy &)> &func)
{
    system("cls");
    int round = 1;
    while (true) {
        for (auto it = buff_skills.begin(); it != buff_skills.end();) {
            if (it->getExistTime() == 0) {
                clearBuff(it);
                fmt::println("{}失效了！", it->getName());
                it = buff_skills.erase(it); // erase 返回新的迭代器
            }
            else {
                ++it;
            }
        }

        std::string description;

        auto showDescription = [&description] {
            SetConsoleOutputCP(CP_UTF8);
            std::wcout.imbue(std::locale(""));

            for (const auto &c : description) {
                std::cout << c << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 延迟
            }
        };

        description = "\nRound: ";
        fmt::print(description);
        fmt::println("{}", round);

        auto showHp = [&description, &showDescription, this] {
            description = Gamer.getName() + "血量: ";
            showDescription();
            print(fg(fmt::color::red), "{} / {}\n", Gamer.getHp(), Gamer.getMaxHp());

            description = enemy.getName() + "血量: ";
            showDescription();
            print(fg(fmt::color::red), "{} / {}\n", enemy.getHp(), enemy.getMaxHp());
        };

        showHp();
        std::string choice;
        while (round & 1) {
            fmt::print("[player]查看自身状态, [enemy]查看敌人属性, [attack]攻击, [skill]释放技能, [pill]使用丹药: ");
            std::cin >> choice;
            if (choice == "player") { Gamer.showPlayer(); }
            else if (choice == "enemy") { enemy.showEnemy(); }
            else if (choice == "skill") { if (useSkill()) { ++round; } }
            else if (choice == "attack") {
                attackEnemy();
                ++round;
            }
            else if (choice == "pill") {
                Gamer.usePill();
            }
            else { fmt::print("无效指令!\n"); }
        }
        if (enemy.getHp() <= 0) {
            fmt::println("{}被打败了！", enemy.getName());
            success();
            for (auto it = buff_skills.begin(); it != buff_skills.end(); ++it) {
                clearBuff(it);
            }
            gainTrophy();
            return;
        }

        showHp();
        if (round % 2 == 0) {
            fmt::print("敌方回合，请你选择防御[defence]或者尝试闪避[dodge]: ");
            std::cin >> choice;
            while (choice != "defence" && choice != "dodge") {
                fmt::print("请输入[defence]或[dodge]: ");
                std::cin >> choice;
                if (choice == "defence" || choice == "dodge") {
                    break;
                }
            }
            if (choice == "defence") {
                attackPlayer(Gamer.getDefence());
                ++round;
            }
            else {
                if (ifSucceedDodge())
                    fmt::println("闪避成功！");
                else
                    attackPlayer(0);

                ++round;
            }
        }

        if (Gamer.getHp() <= 0) {
            fmt::println("你被打败了！");
            defeat();
            restart();
        }
        func(Gamer, enemy);
        for (auto &buff_skill : buff_skills) {
            buff_skill.setExistTime(buff_skill.getExistTime() - 1);
        }
    }
}
