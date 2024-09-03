#include "Fight.h"

#include <chrono>
#include <conio.h>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <windows.h>

#include "Helper.h"
#include "fmt/core.h"

extern Player Player;

Fight::Fight(const Enemy &enemy): enemy(enemy) { }

// 获得奖励
void Fight::gainTrophy() const
{
    Player.gainExp(enemy.getExperience());
    Player.gainMoney(enemy.getMoney());
    Player.gainArmor(enemy.getArmor());
    Player.gainWeapon(enemy.getWeapon());
    Player.gainSkill(enemy.getSkillId());
}

// 计算伤害
int calculateDamage(const int damage, const int defence)
{
    const double reduction_rate = static_cast<double>(defence) / (100.0 + static_cast<double>(defence));
    return static_cast<int>(reduction_rate * static_cast<double>(damage));
}

// 清空状态
void clearBuff(const std::vector<Skill>::iterator &skill)
{
    Player.setDamage(Player.getDamage() - skill->getAddDamage());
    Player.setDefence(Player.getDefence() - skill->getAddDamage());
    Player.setCritical(Player.getCritical() - skill->getAddCritical());
}

// 随机返回 true / false
bool achievePercent(const double probability)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::bernoulli_distribution d(probability);
    return d(gen);
}


void Fight::attack()
{
    if (achievePercent(Player.getCritical())) {
        enemy.decHp(calculateDamage(Player.getDamage() * 2, enemy.getDefence()));
        return;
    }
    enemy.decHp(calculateDamage(Player.getDamage(), enemy.getDefence()));
}

void Fight::useSkill() const
{
    Player.checkSkill();
    int pos;
    fmt::print("你想用哪个技能[请输入其编号，0是退出]: ");
    while (true) {
        std::cin >> pos;
        if (pos == 0)
            break;
        if (0 < pos && pos < Player.getSkills().size()) {
            break;
        }
        fmt::print("请输入对的编号: ");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    const auto skill = Player.getSkills()[pos];
    const auto check = Skills[skill.getId()].use();
    if (!check.has_value()) {
        fmt::print("元气不足，无法释放。\n");
    }
    if (check.value() != 0) {
        fmt::print("你对{}造成了{}点伤害。\n", enemy.getName(), check.value());
    }
}

// 弹反
bool ifSucceedDodge()
{
    if (achievePercent(Player.getEvasion())) {
        return true;
    }
    fmt::println("准备！！！");
    constexpr char target_key = 'k';   // 目标按键
    constexpr double time_limit = 0.3; // 时间限制，单位为秒
    double elapsed_time = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 5);

    // 生成随机数，准备时间
    const int random_seconds = dis(gen);
    while (elapsed_time < random_seconds) {
        if (_kbhit()) {
            // 检测是否有按键输入, 获取按下的按键
            if (const char ch = static_cast<char>(_getch()); ch == target_key) {
                fmt::println("太早了，失败！");
                return false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 暂停100毫秒
        elapsed_time += 0.1;                                         // 计算经过的时间
    }

    fmt::print("在 {} 秒内按下 '{}' 键！\n", time_limit, target_key);

    waitForLoad(100);
    for (size_t i = 0; i < 3; ++i) {
        if (_kbhit()) {
            // 检测是否有按键输入
            // 获取按下的按键
            if (const char ch = static_cast<char>(_getch()); ch == target_key) {
                fmt::print("闪身!!!");
                return true; // 退出程序
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 暂停100毫秒
    }

    fmt::print("时间到！你没有按下目标键。\n");
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
    system("pause");
    system("cls");
}

// 赢了返回true
bool Fight::fight()
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
        auto slowPrintDescription = [&description] {
            for (const auto &ch : description) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                fmt::print("{}", ch);
            }
        };

        description = "Round: ";
        slowPrintDescription();
        fmt::println("{}", round);

        auto showHp = [&description, &slowPrintDescription, this] {
            description = "玩家血量: ";
            slowPrintDescription();
            print(fg(fmt::color::red), "{} / {}\n", Player.getHp(), Player.getMaxHp());

            description = "敌人血量: ";
            slowPrintDescription();
            print(fg(fmt::color::red), "{} / {}\n", enemy.getHp(), enemy.getMaxHp());
        };

        std::string choice;
        while (round & 1) {
            fmt::print("[player]查看自身状态,[enemy]查看敌人属性,[attack]攻击,[skill]释放技能: ");
            std::cin >> choice;
            if (choice == "player") {
                Player.showPlayer();
            }
            else if (choice == "enemy") {
                enemy.showEnemy();
            }
            else if (choice == "skill") {
                useSkill();
                ++round;
            }
            else if (choice == "attack") {
                attack();
                ++round;
            }
            else {
                fmt::print("无效指令!\n");
            }
        }
        if (enemy.getHp() <= 0) {
            fmt::println("{}被打败了！", enemy.getName());
            success();
            for (const auto it = buff_skills.begin(); it != buff_skills.end();) {
                clearBuff(it);
            }
            gainTrophy();
            return true;
        }

        system("cls");
        showHp();
        if (round % 2 == 0) {
            fmt::print("敌方回合，请你选择防御[defence]或者尝试闪避[dodge]: ");
            while (choice != "defence" && choice != "dodge") {
                fmt::print("请输入[defence]或[dodge]: ");
                std::cin >> choice;
                if (choice == "defence" || choice == "dodge") {
                    break;
                }
            }
            if (choice == "defence") {
                const int damage = calculateDamage(enemy.getAttack(), Player.getDefence());
                fmt::print("你受到了{}点伤害", damage);
                Player.setHp(Player.getHp() - damage);
                ++round;
            }
            else {
                if (ifSucceedDodge()) {
                    fmt::println("闪避成功！");
                    ++round;
                }
                else {
                    Player.setHp(Player.getHp() - enemy.getAttack());
                    fmt::println("你受到{}点伤害，还剩{}点血量", enemy.getAttack(), Player.getHp());
                }
            }
        }

        if (Player.getHp() <= 0) {
            fmt::println("你被打败了！");
            defeat();
            return false;
        }
        for (auto &buff_skill : buff_skills) {
            buff_skill.setExistTime(buff_skill.getExistTime() - 1);
        }
    }
}
