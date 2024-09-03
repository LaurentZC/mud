#include "Fight.h"
#include <chrono>
#include <conio.h>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <windows.h>
#include "fmt/core.h"

namespace fmt {
    using byte = unsigned char; // Ensure fmt::byte is used
}

using namespace std;

extern Player Player;

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
int Fight::calculateDamage(const int damage, const int defence)
{
    const double reduction_rate = static_cast<double>(defence) / (100.0 + static_cast<double>(defence));
    return static_cast<int>(reduction_rate * static_cast<double>(damage));
}

// 随机返回 true / false
bool achievePercent(const double probability)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::bernoulli_distribution d(probability);
    return d(gen);
}

// 弹反
int ifSucceedDodge()
{
    fmt::println("准备！！！");
    constexpr char target_key = 'k';   // 目标按键
    constexpr double time_limit = 0.3; // 时间限制，单位为秒
    double elapsed_time = 0;
    std::random_device rd;                     // 获取随机数种子
    std::mt19937 gen(rd());                    // 使用 Mersenne Twister 算法
    std::uniform_int_distribution<> dis(3, 5); // 定义范围 [3, 5]

    // 生成随机数
    const int random_seconds = dis(gen);
    while (elapsed_time < random_seconds) {
        if (_kbhit()) {
            // 检测是否有按键输入, 获取按下的按键
            if (const char ch = static_cast<char>(_getch()); ch == target_key) {
                fmt::println("太早了，失败！");
                return 0;
            }
        }
        this_thread::sleep_for(std::chrono::milliseconds(100)); // 暂停100毫秒
        elapsed_time += 0.1;                                    // 计算经过的时间
    }
    fmt::print("在 {} 秒内按下 '{}' 键！\n", time_limit, target_key);
    elapsed_time = 0;
    int l;
    while (elapsed_time < time_limit) {
        for (l = 0; l < 10; ++l) {
            fmt::print("=");
        }

        fmt::print("\n");
        if (_kbhit()) {
            // 检测是否有按键输入
            // 获取按下的按键
            if (const char ch = static_cast<char>(_getch()); ch == target_key) {
                fmt::print("闪身!!!");
                return 1; // 退出程序
            }
        }
        this_thread::sleep_for(std::chrono::milliseconds(100)); // 暂停100毫秒
        elapsed_time += 0.1;                                    // 计算经过的时间
        l = elapsed_time * 30.0;
    }

    fmt::print("时间到！你没有按下目标键。\n");
    return 0;
}

Fight::Fight(Enemy &enemy): enemy(enemy)
{
    int round = 1;
    while (Player.getHp() > 0 && enemy.getHp() > 0) {
        for (auto it = buff_skills.begin(); it != buff_skills.end(); ++it) {
            if (it->getExistTime() == 0) {
                Player.setDamage(Player.getDamage() + it->getAddDamage());
                Player.setDefence(Player.getDefence() + it->getAddDamage());
                Player.setCritical(Player.getCritical() + it->getAddCritical());
                fmt::println("{}失效了！", it->getName());
                buff_skills.erase(it);
            }
        }
        string description = "Round";
        for (int i = 0; i < description.length(); ++i) {
            this_thread::sleep_for(chrono::milliseconds(50));
            fmt::print("{}", description[i]);
        }
        fmt::println("{}", round);

        description = "玩家血量：";
        for (int i = 0; i < description.length(); ++i) {
            this_thread::sleep_for(std::chrono::milliseconds(50));
            fmt::print("{}", description[i]);
        }
        fmt::println("{}", Player.getHp());

        description = "敌人血量：";
        for (int i = 0; i < description.length(); ++i) {
            this_thread::sleep_for(std::chrono::milliseconds(50));
            fmt::print("{}", description[i]);
        }
        fmt::println("{}", enemy.getHp());

        fmt::println("[player]查看自身状态,[enemy]查看敌人属性,[attack]攻击,[skill]释放技能,[help]查看教程");
        string choice1;
        while (true) {
            cin >> choice1;
            if (choice1.length() > 1) {
                fmt::print("无效的输入！[player]查看自身状态,[enemy]查看敌人属性,[attack]攻击,[skill]释放技能,[help]查看教程: ");
                continue;
            }
            if (choice1 == "player") {
                Player.showPlayer();
                continue;
            }
            if (choice1 == "enemy") {
                enemy.showEnemy();
                continue;
            }
            if (choice1 == "skill") {
                int temp = Player.useSkill();
                if (temp == 0) { continue; }
                if (Player.getSkills()[0].getType() == Skill::Type::GAIN) {
                    const auto &skills = Player.getSkills();
                    buff_skills.push_back(skills[0]); //把增益型技能放在数组中，以便在持续时间结束把它删除
                    Player.setDamage(Player.getDamage() + skills[0].getAddDamage());
                    Player.setDefence(Player.getDefence() + skills[0].getAddDamage());
                    Player.setCritical(Player.getCritical() + skills[0].getAddCritical());
                    Player.setMp(Player.getMp() - skills[0].getConsumption());
                    break;
                }
                if (Player.getSkills()[0].getType() == Skill::Type::RESTORATIVE) {
                    Player.setHp(Player.getHp() + Player.getSkills()[0].getAddHp());
                    Player.setMp(Player.getMp() - Player.getSkills()[0].getConsumption());
                    break;
                }
                if (Player.getSkills()[0].getType() == Skill::Type::AGGRESSIVE) {
                    Player.setMp(Player.getMp() - Player.getSkills()[0].getConsumption());
                    enemy.setHp(enemy.getHp() - calculateDamage(Player.getSkills()[0].getDamage(), enemy.getDefence()));
                    break;
                }
            }
            if (choice1 == "attack") {
                if (achievePercent(Player.getCritical())) {
                    enemy.setHp(enemy.getHp() - calculateDamage(Player.getDamage() * 2, enemy.getDefence()));
                    break;
                }
                enemy.setHp(enemy.getHp() - calculateDamage(Player.getDamage(), enemy.getDefence()));
                break;
            }
            if (choice1 == "help") {
                fmt::println("游戏帮助：");
                fmt::print("输入player查看自身状态,enemy查看敌人属性,attack攻击，skill释放技能,己方攻击后到对方的回合\n攻击后一段时间，会提示敌人出招，此时有若在较短时间内按下防御K键，则能弹开对手的攻击，为自己创造机会！\n");
            }
            fmt::print("输入player查看自身状态,enemy查看敌人属性,attack攻击，skill释放技能,help查看教程：");
        }
        if (enemy.getHp() <= 0) {
            fmt::println("{}被打败了！", enemy.getName());
            this_thread::sleep_for(chrono::seconds(1));
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
            break;
        }
        system("cls");
        fmt::println("敌方回合，请你选择防御(defence)或者尝试闪避(dodge)");
        string choice2;
        while (choice2 != "defence" && choice2 != "dodge") {
            fmt::print("请输入defence或dodge\n");
            cin >> choice2;
            if (choice2 == "defence" || choice2 == "dodge") {
                break;
            }
        }
        if (choice2 == "defence") {
            int damage = calculateDamage(enemy.getAttack(), Player.getDefence());
            fmt::print("你受到了{}点伤害", damage);
            Player.setHp(Player.getHp() - damage);
            fmt::print("剩余血量：{}", Player.getHp());
        }
        else if (choice2 == "dodge") {
            if (ifSucceedDodge() == 0) {
                if (achievePercent(Player.getEvasion())) {
                    fmt::println("闪避成功!");
                }
                else {
                    Player.setHp(Player.getHp() - enemy.getAttack());
                    fmt::println("你受到{}点伤害，还剩{}点血量", enemy.getAttack(), Player.getHp());
                }
            }
            else {
                fmt::println("闪避成功，不受到伤害！");
            }
        }
        if (Player.getHp() <= 0) {
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
            fmt::println("按下任意键从上一存档开始");
            system("pause");
            //此处读档
            system("cls");
            break;
        }
        for (auto &buff_skill : buff_skills) {
            buff_skill.setExistTime(buff_skill.getExistTime() - 1);
        }
        ++round;
    }
    for (auto &buff_skill : buff_skills) {
        Player.setDamage(Player.getDamage() + buff_skill.getAddDamage());
        Player.setDefence(Player.getDefence() + buff_skill.getAddDamage());
        Player.setCritical(Player.getCritical() + buff_skill.getAddCritical());
    }
    gainTrophy();
}
