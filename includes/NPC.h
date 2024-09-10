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
    std::string name;                   // 名字
    std::string description;            // 描述特征
    std::vector<std::string> dialogues; // 对白
};

class TaskGivingNPC final : public NPC
{
public:
    TaskGivingNPC(std::string name, std::string description, std::vector<std::string> dia, std::vector<int> task_id);
    void talk() override;
    static void save();
    static void load();
    [[nodiscard]] int getTaskId() const;

private:
    void giveReward() const;
    std::vector<int> task_id;
    bool if_give_task {true}; // 是否给予任务
};

class ShopKeeper final : public NPC
{
public:
    ShopKeeper();
    ShopKeeper(std::string name, std::string description, std::vector<std::string> dia, const std::vector<int> &weapons_id, const std::vector<int> &armors_id, const std::array<int, 6> &pill_num);

    void talk() override;

private:
    void setPillNum(const Pill &pill, int pill_num);
    void showGoods();
    void enterStore();
    void buy();
    void sell();
    void buyPills();
    void buyWeapon();
    void buyArmor();
    void sellArmor();
    void sellWeapon();
    [[nodiscard]] int getPillNum(const Pill &pill) const;

    std::vector<Weapon> weapons {{}};
    std::vector<Armor> armors {{}};
    // @formatter:off
    std::map<Pill, int> pills = {
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::BIG}, 10},
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::MID}, 10},
        {Pill{Pill::Type::BLOOD_PILL, Pill::Size::SMALL}, 10},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::BIG}, 10},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::MID}, 10},
        {Pill{Pill::Type::MANA_PILL, Pill::Size::SMALL}, 10}
    };
};

inline std::array<TaskGivingNPC, 4> TaskGivingNPCs = {
    {
        {"李白", "一位潇洒的剑客，身穿白色长袍，手持一把长剑，眼神中透着智慧与坚定。",
            {
                "年轻人，江湖险恶，切记要谨慎行事。\n",
                "我曾游历四方，见过无数风景，你若是想学习一些我的独门秘术，就去打败青龙卫吧，我可不教没有才能之人!\n",
                "剑术不仅仅是技巧，更是心境的修炼。你去帮我找一壶酒来，我便教你在战斗中保持专注，一击毙敌的秘法。\n",
                "陆洪死后，飞云商会的段霖借势而起，此人来头不小，武功高强，带着手下作恶多端，连我也不一定是他的对手。\n但是为了云霄城的百姓，我不能坐视不管，你若有心，便与我一同前去杀了段霖！\n但在那之前，我们需要先行攻破他的三个手下，分别是影刃卫，天霸卫和怒焰卫，你先去杀掉影刃卫，来证明你的实力，我可不想带着一个累赘\n",
                "你回来了，那你的实力已经毋庸置疑，接下来，且随我去杀掉天霸卫，那厮厉害的很，要多加小心\n",
                "现在只剩下怒焰卫了，杀了他，你我就能去打败段霖，为民除害！\n",
                "所有阻碍已经清除，你且去面对段霖，我为你抵挡住所有的杂兵\n"
            }, {11, 12, 13, 14, 15, 16}
        },
        {"小翠", "一位活泼的女侠，身材娇小，身上常备着一把短刀，性格开朗，乐于助人",
            {
                "虽然我个子小，但我的刀可不容小觑哦\n",
                "嘿！你也想在江湖中闯荡吗？我可以教你一些小技巧,这样，你去帮我教训一下白虎卫，回来之后，我便教你我的叶隐之术\n",
                "你终于来了，那可恶的陆洪，派手下来杀了我的父母，他们人多势众，我挡不住，我从不求人；\n但这次，求你去把那陆洪杀掉，他在位一天，这里的百姓就无一天安稳。\n你若能杀了他，我便将我的家传秘法给你，求你一定杀了他！\n"
            }, {9, 10}
        },
        {"老张", "一位年迈的药师，满头白发，面容和蔼，常常在城中摆摊，出售各种药材。",
            {
                "年轻人，身体是革命的本钱，记得多保重自己。\n",
                "你是刚来这座城吧，我是城里药房的老板，你若在外闯荡受了伤，可来我这回复些伤势；你还没去过城主府吗，最好先去见见，城主人挺好的，他会很乐意见你。\n",
                "你又来了啊，能请你帮我取来一颗定神丹吗，我年纪大了，需要药物辅助才能正常工作；当然，我会教你一个厉害的秘术\n",
                "如你所见，那可恶的陆洪派人来砸了我的药店，我什么都没做，只是不想帮助他们做能使人功力大涨的邪药\n城中百姓苦陆洪已久，你若能杀了他，为民除害，我便将我最厉害的秘法传给你\n",
                "陆洪死后，又来了个段霖，那人也是无恶不作，占据一方城池，仗着自己武功高强，拦截拦路的商队，我这里已经好久没有货了，你若能帮我巡回一些，我愿意支付相应的报酬\n",
                "多年过去，你已经成为武林高手，去吧，杀掉那段霖，有你这样的人在，哪怕再来10个段霖，我们也不害怕了\n"
            }, {4, 5, 6, 7, 8}
        },
        {"城主", "一位威严而智慧的领导者，年约四十，身材魁梧，面容刚毅。艾尔文的头发微微泛白，显示出他在治理城镇过程中积累的丰富经验。他的眼神深邃而坚定，透出对城镇未来的无限关怀。",
            {
                "欢迎来到云霄城\n",
                "你是外来的旅行者吧，如你所见，我们这座城的发展状况并不算好，隔壁武威城的陆洪仗着自己武功高强，带领手下四处抢劫，来往的商队常常被杀。\n可否请阁下帮我杀掉武威城里青龙卫，就是他经常带人去抢劫商队\n",
                "上次的任务你完成的很出色，我们正筹备进攻武威城，可除了陆洪自己，他还有个令人闻风丧胆的白虎卫，有他在，我们就难以进攻，可否请你再去杀掉白虎卫。\n",
                "白虎卫已死，时机已然成熟，英雄，请随我们一同前往武威城，杀掉陆洪，为民除害！\n",
                "我本以为，陆洪死后，这满城百姓能过上安稳日子，可谁料又来了个段霖。\n此人乃飞云商会的会长，却四处抢劫，无恶不作，百姓们渴望安定，无法再战，你若能拿下他，满城百姓都将感恩戴德\n"
            },{0, 1, 2, 3}
        }
    }
};

inline std::array<ShopKeeper, 2> ShopKeepers = {
    {
        {
            "铁匠老李","铁匠老李是一位年长的铁匠，满脸皱纹，手臂结实，常年在炉火旁工作。\n他在江湖上以锻造高质量武器而闻名，尤其擅长打造独特的刀剑。老张性格豪爽，乐于分享自己的锻造经验。",
            {"来吧，年轻人！只要你有心，我就能为你打造出一把无敌的武器！"},
            {1, 2, 3, 4, 5, 6},
            {1, 2, 3, 4, 7, 8, 12},
            {0, 0, 0, 0, 0, 0}
        },
        {
            "张小翠","张小翠是一位年轻的女商人，经营着一家名为“翠花阁”的小店。\n身材娇小，长发披肩，常常扎成两个可爱的马尾辫。她穿着一身简单却干净的青色衣裙，脸上总是挂着甜美的笑容，给人一种亲切的感觉。",
            {"你好呀！如果你需要药材或情报，翠花阁绝对是你的最佳选择！"},
            {},
            {},
            {25, 30, 50, 30, 40, 50}
        }
    }
};
// @formatter:on
