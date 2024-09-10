#include <Fight.h>
#include <NPC.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <windows.h>

#include "Area.h"
#include "CreatMap.h"
#include "Helper.h"
#include "PlayMap.h"
#include "Player.h"
#include "fmt/core.h"

using namespace std;

Player Gamer;

Area MainCity = creatMainCity();
Area WuWeiCheng = creatWuWeiCheng();
Area ShangHui = creatShangHui();

class NoArchive final : public exception
{
public:
    [[nodiscard]] const char *what() const noexcept override { return "你还没有存档"; }
};

class AbandonLoad final : public exception { };

void creat()
{
    namespace fs = filesystem;
    fmt::print("欢迎来到剑影江湖。");
    fmt::print("请告诉我你的名字: ");
    string name;
    cin >> name;
    Gamer.setName(name);
    Gamer.save();
    system("cls");
    printSlowly(format(fg(fmt::color::light_sky_blue), "江湖，风起云涌，无数人浪迹天涯，闯荡江湖，只为追求那心中的侠客梦。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "殊不知，在整个江湖的背后，一直有一双大手在默默操控一切，他隐藏在江湖的阴暗面，是彻头彻尾的吸血鬼。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "他试图颠覆武林的秩序，夺取武林之主的宝座，以实现他对整个武林的绝对统治。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "武林中像来不缺少正义之士，而你，" + name + "，正意气风发，即将踏入江湖，势必要维护武林的安定。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "故事从此刻开始...\n"));

    printSlowly(format(fg(fmt::color::light_sky_blue), "这日，你来到了当地有名的大城市——云霄城，接下来的时间你决定在这里定居。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "初升的朝阳透过薄雾，洒下温暖的金色光辉，映照在云霄城的城墙上。你缓步走来，心中满是期待与紧张。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "远远望去，云霄城如同一颗璀璨的明珠，镶嵌在青山绿水之间，城墙高耸，巍峨壮观，仿佛在向世人宣告着它的威严与神秘。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "城门口，雕刻精美的石狮子静静守护，似乎在审视每一个踏入城中的人。你深吸一口气，感受到空气中弥漫着的江湖气息。\n"));
    printSlowly(format(fg(fmt::color::light_sky_blue), "一路走来已经有些累了，在赶路的过程中还受了点伤，听说这里药房的店主人很好，你准备先去那里看看。\n"));
}

void load()
{
    system("cls");
    namespace fs = filesystem;
    const fs::path path = "../files";
    int i = 0;
    vector<string> archive;
    for (const auto &entry : fs::directory_iterator(path)) {
        if (entry.path().filename().string() == "maps")
            continue;
        if (entry.is_directory()) {
            ++i;
            fmt::print("{}. {}\n", i, entry.path().filename().string());
            archive.push_back(entry.path().filename().string());
        }
    }
    if (i == 0) { throw NoArchive(); }
    fmt::print("你想读取那个存档[编号 / exit]: ");
    string choice;
    int index = 0;
    while (true) {
        cin >> choice;
        if (choice == "exit") { throw AbandonLoad(); }
        if (!choice.empty() && all_of(choice.begin(), choice.end(), ::isdigit)) {
            index = stoi(choice);
            if (index <= i) {
                Gamer.load(archive[index - 1]);
                break;
            }
            fmt::print("你没有这么多存档哦。请重新输入: ");
        }
        else { fmt::print("无效的指令，请输入编号: "); }
    }
}

void start()
{
    printTitle();
    fmt::print("\t\t\t新的开始[new]\t读取存档[load]\t退出游戏[quit]\n指令: ");
    string choice;
    while (true) {
        cin >> choice;
        if (choice == "new") {
            creat();
            return;
        }
        if (choice == "load") {
            try {
                load();
                system("cls");
                fmt::print("欢迎回到游戏。\n");
                return;
            }
            catch (const NoArchive &e) {
                system("cls");
                printTitle();
                fmt::print("\n{}\n", e.what());
                fmt::print("\t\t\t新的开始[new]\t读取存档[load]\t退出游戏[quit]\n指令: ");
            } catch (const AbandonLoad &) {
                system("cls");
                printTitle();
                fmt::print("\t\t\t新的开始[new]\t读取存档[load]\t退出游戏[quit]\n指令: ");
            }
        }
        else if (choice == "quit") { exit(0); }
        else if (choice == "debug") {
            Gamer.setName("test");
            Gamer.gainExp(20000);
            Gamer.setDamage(100000);
            Gamer.gainMoney(100000);
            Gamer.save();
            system("cls");
            return;
        }
        else { fmt::print("无效指令，请重新输入: "); }
    }
}

TaskGivingNPC &taskAccept()
{
    const auto &[c, x, y] = Gamer.position;
    if (x == 2 && y == 2)
        return TaskGivingNPCs[0];
    if (x == 2 && y == 4)
        return TaskGivingNPCs[1];
    if (x == 3 && y == 4)
        return TaskGivingNPCs[2];
    return TaskGivingNPCs[3];
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    start();
    auto &[c, x, y] = Gamer.position;
    Area current_map = MainCity;

    printMap(current_map.getArea());
    fmt::print("{}\n", current_map.getArea()[x][y].getDescription());
    while (true) {
        fmt::print("\n移动:  move \t 查看自身属性: self \t 打开背包: bag \t 和npc对话: chat \t 保存: save \t 退出: quit \n");
        fmt::print("指令: ");
        string command;
        cin >> command;
        if (command == "move") { movePlayerLocation(current_map, true); }
        else if (command == "self") {
            system("cls");
            Gamer.showPlayer();
            Gamer.checkTask();
            fmt::print("\n");
            if (!Gamer.checkSkill()) { fmt::print("你还没有技能。"); }
            if (Gamer.getPoints() != 0) {
                fmt::print("\n你还有{}点属性点，是否使用[y / n]: ", Gamer.getPoints());
                while (true) {
                    cin >> command;
                    if (command == "y" || command == "Y") {
                        Gamer.usePoint();
                        break;
                    }
                    if (command == "n" || command == "N") { break; }
                    fmt::print("无效指令，请输入[y / n]: ");
                }
            }
            waitForAnyKey();
            system("cls");
            printMap(current_map.getArea());
        }
        else if (command == "bag") {
            system("cls");
            Gamer.openBag();
            waitForAnyKey();
            system("cls");
            printMap(current_map.getArea());
        }
        else if (command == "chat") {
            if (x == 5 && y == 3) {
                changeMap(current_map);
                if (c == 1) {
                    playWuWeiCheng(current_map);
                }
                else if (c == 2) {
                    playShangHui(current_map);
                }
                system("cls");
                printMap(current_map.getArea());
                continue;
            }
            if (x == 4 && y == 2) {
                // 医院
                printSlowly(format(fg(fmt::color::green), "医生: 吆，小伙子受伤了？\n"));
                printSlowly(format(fg(fmt::color::green), "医生: 来让我给你看看，只要50元保证你神清气爽。\n"));
                fmt::print("你是否愿意支付50元接受治疗？[y / n]: ");
                while (true) {
                    cin >> command;
                    if (command == "y" || command == "Y") {
                        if (Gamer.getMoney() < 50) {
                            printSlowly(format(fg(fmt::color::green), "医生: 连50块钱都没有，穷鬼。\n"));
                            break;
                        }
                        Gamer.gainMoney(-50);
                        Gamer.setHp(Gamer.getMaxHp());
                        Gamer.setMp(Gamer.getMaxMp());
                        fmt::print("正在接受治疗，请稍候...\n");
                        waitForLoad(5000);
                        printSlowly(format(fg(fmt::color::green), "医生: 好了小伙子。\n"));
                        break;
                    }
                    if (command == "n" || command == "N") {
                        printSlowly(format(fg(fmt::color::green), "医生: 不治疗你来打扰我生意？快快离开。\n"));
                        break;
                    }
                    fmt::print("无效指令，请输入[y / n]: ");
                }
                system("cls");
                printMap(current_map.getArea());
            }
            else if (x == 3 && y == 2) {
                // 铁匠铺
                ShopKeepers[0].talk();
                system("cls");
                printMap(current_map.getArea());
            }
            else if (x == 4 && y == 4) {
                // 商店
                Tasks[12].finish();
                ShopKeepers[1].talk();
                system("cls");
                printMap(current_map.getArea());
            }
            else if (x == 1 && y == 3) {
                printSlowly(format(fg(fmt::color::green), "城主: 你是来找我修炼的还是想和我聊聊？\n"));
                fmt::print("[fight]和城主对战，[talk]和城主聊天: ");
                while (true) {
                    cin >> command;
                    if (command == "fight") {
                        printSlowly(format(fg(fmt::color::green), "城主: 好，且来城外让我看看你的水平。\n"));
                        fmt::print("正在加载...\n");
                        waitForLoad(1000);
                        Fight(Enemy::creatBoss(0)).fight([](const Player &gamer, const Enemy &enemy) {
                            if (gamer.getHp() <= 10 || enemy.getHp() <= 10) { }
                        });
                        printSlowly(format(fg(fmt::color::green), "城主：小子不错嘛。\n"));
                        break;
                    }
                    if (command == "talk") {
                        Tasks[4].finish();
                        taskAccept().talk();
                        break;
                    }
                    fmt::print("无效指令，请重新输入[fight / talk]: ");
                }
                system("cls");
                printMap(current_map.getArea());
            }
            else if (current_map.getArea()[x][y].getContent() == Room::Content::NPC) {
                taskAccept().talk();
            }
            else { fmt::print("这里没有npc。\n"); }
        }
        else if (command == "save") { Gamer.save(); }
        else if (command == "quit") {
            Gamer.save();
            fmt::print("感谢你的游玩。\n");
            waitForAnyKey();
            return 0;
        }
        else { fmt::print("无效的指令！\n"); }
    }
}
