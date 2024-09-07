#pragma once

#include <map>
#include <vector>

#include "Equipment.h"
#include "Pill.h"
#include "Task.h"

class NPC
{
public:
    NPC();
    NPC(std::string name, std::string description, std::vector<std::string> dialogue);
    virtual ~NPC();
    virtual void talk() = 0;

protected:
    std::string name;                  // 名字
    std::string description;           // 描述特征
    std::vector<std::string> dialogues; // 对白
};

class TaskGivingNPC final : public NPC
{
public:
    TaskGivingNPC(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &task_id);

    void talk() override;

private:
    void giveTask() const;
    void giveReward() const;
    [[nodiscard]] bool ifFinishTask() const;
    std::vector<Task> tasks;
    int task_index {};
    bool if_give_reward {true}; // 是否给予奖励
    bool if_give_task {true};   // 是否给予任务
};

class ShopKeeper final : public NPC
{
public:
    ShopKeeper(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &weapons_id, const std::vector<int> &armors_id);

    void talk() override;
    [[nodiscard]] int getPillNum(const Pill &pill) const;

private:
    void setPillNum(const Pill &pill, int pill_num);
    void showGoods();
    void buy();
    void sell();
    void enterStore();
    void buyPills();
    void buyWeapon();
    void buyArmor();
    void sellArmor();
    void sellWeapon();

    std::vector<Weapon> weapons;
    std::vector<Armor> armors;
    // @formatter:off
    std::map<Pill, int> pills = {
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::BIG}, 0},
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::MID}, 0},
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::SMALL}, 0},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::BIG}, 0},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::MID}, 0},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::SMALL}, 0}
    };

};

inline const std::array<TaskGivingNPC, 5> TaskGivingNPCs = {
    {
        {"李白", "一位潇洒的剑客，身穿白色长袍，手持一把长剑，眼神中透着智慧与坚定。",
            {
                "年轻人，江湖险恶，切记要谨慎行事。",
                "我曾游历四方，见过无数风景，你若是想学习一些我的独门秘术，就去打败城门口闹事的哪些家伙吧，我可不教没有才能之人!",
                "剑术不仅仅是技巧，更是心境的修炼。你去帮我找一壶酒来，我便教你在战斗中保持专注，一击毙敌的秘法。"
            }, {}},
        {"小翠", "一位活泼的女侠，身材娇小，身上常备着一把短刀，性格开朗，乐于助人",
            {"虽然我个子小，但我的刀可不容小觑哦",
                "嘿！你也想在江湖中闯荡吗？我可以教你一些小技巧,这样，你去给我带来一颗回元丹，不要普通商人那里购买的，而是特制的，找回来之后，我便教你我的叶隐之术",
                "你终于来了，那可恶的陆洪，派手下来杀了我的父母，他们人多势众，我挡不住，我从不求人；但这次，求你去把那陆洪杀掉，他在位一天，这里的百姓就无一天安稳。\n你若能杀了他，我便将我的家传宝剑给你，求你一定杀了他！"
            }, {}},
        {" 老张", "一位年迈的药师，满头白发，面容和蔼，常常在城中摆摊，出售各种药材。",
            {"年轻人，身体是革命的本钱，记得多保重自己。",
                "你是刚来这座城吧，我是城里药房的老板，你若在外闯荡受了伤，可来我这回复些伤势；正巧今天我有事相求，你若不嫌，就帮我去寻来一株人参草，我会教你一个在战斗中保命的秘术作为报酬",
                "你又来了啊，能请你帮我取来一颗定神丹吗，我年纪大了，需要药物辅助才能正常工作；当然，我会再教你一个更厉害的秘术", "如你所见，那可恶的陆洪派人来砸了我的药店，我什么都没做，只是不想帮助他们做能使人功力大涨的邪药，城中百姓苦陆洪已久，你若能杀了他，为民除害，我便将我最厉害的秘法传给你",
                "陆洪死后，又来了个段霖，那人也是无恶不作，占据一方城池，仗着自己武功高强，拦截拦路的商队，我这里已经好久没有货了，你若能帮我巡回一些，我愿意支付相应的报酬", "多年过去，你已经成为武林高手，去吧，杀掉那段霖，有你这样的人在，哪怕再来10个段霖，我们也不害怕了"
            }, {}},
        {"", "", {}, {}},
        {"", "", {}, {}}
    }
};
// @formatter:on
