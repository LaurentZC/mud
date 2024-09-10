#pragma once

#include <array>
#include <string>

class Task
{
public:
    Task();
    Task(int id, std::string n, std::string desc, int exp, int skill_id_, int m);
    Task(const Task &other);
    Task(Task &&other) noexcept;
    Task & operator=(const Task &other);
    Task & operator=(Task &&other) noexcept;

    // 完成任务
    void finish();
    void finish(bool if_finished);
    void showTask() const;
    void receive();
    void save(std::ofstream &file) const;
    [[nodiscard]] int getId() const;
    [[nodiscard]] int getSkillId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] int getExperience() const;
    [[nodiscard]] int getMoney() const;
    [[nodiscard]] bool ifTaskFinished() const;
    [[nodiscard]] bool ifReceived() const;
    bool operator==(const Task &other) const;

private:
    int id {};               // id
    std::string name;        // 名字
    std::string description; // 任务描述
    int experience {};       // 完成后的经验
    int skill_id {};         // 获得的技能Id
    int money {};            // 钱
    bool if_finished {};     // 是否完成
    bool if_received {};     // 是否接过任务
};

// @formatter:off
inline std::array<Task, 17> Tasks = {
    {
        {0, "杀掉青龙卫", "此人作恶多端，在城主的委托下，你觉得杀了他为民除害",
            600, -1, 700},
        {1, "杀掉白虎卫", "城主准备率兵攻打武威城，可碍于白虎卫的存在，不敢进攻，杀掉他为城主开辟道路",
            900, -1, 1000,},
        {2, "跟随城主杀掉陆洪", "时机已到，跟随城主杀掉陆洪，为民除害",
            1200, -1, 1200},
        {3, "杀掉段霖", "刚平息了陆洪，又来了个段霖，但是不管来多少坏人，你都能将其制服",
            2500, -1, 3000},
        {4,"会见城主","初次来到云霄城，先去城主府找一下城主吧",
            100,-1,200},
        {5,"取得定神丹","帮老张取一颗定神丹来，据说在武威城里能找到",
            400,1,800},
        {6,"为老张杀掉陆洪","忍无可忍就无需再忍，为了老张，杀掉陆洪",
            500,4,600},
        {7,"找回货物","老张的货物被人抢去了，去帮他找回来",
            600,7,1000},
        {8,"老张的最后心愿","杀掉段霖，为民除害",
            2000,-1,1500},
        {9,"教训白虎卫","帮小翠教训白虎卫",
            500,2,300},
        {10,"为小翠杀掉陆洪","陆洪杀了小翠的父母，去帮她报仇",
            800,11,900},
        {11,"杀掉青龙卫","李白有个独门秘术，杀掉青龙卫，证明自己的能力",
            600,5,700},
        {12,"给李白买壶酒","交给李白一壶酒，他会教你在战斗中保持专注的方法",
            200,15,300},
        {13,"杀掉影刃卫","为跟随李白一同杀掉段霖，去杀掉影刃卫证明自己的实力",
            1000,10,1000},
        {14,"杀掉天霸卫","李白认可了你的实力，接下来跟随李白，杀掉天霸卫",
            1200,-1,1300},
        {15,"杀掉怒焰卫","只剩下怒焰卫了，杀了他后再去杀掉段霖吧",
            1400,-1,1500},
        {16,"杀掉段霖","李白正为你抵挡所有的杂兵，去杀了段霖吧",
            2500,-1,3000},
    }
};
// @formatter:on
