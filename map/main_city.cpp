#include "../headers/CreatMap.h"

using namespace std;

//  X        X       城主府      X         X
//  X       居民区     空       居民区       X
//  X       铁匠铺     空       任务地点     X
//  X       医院     出生地      商店        X
//  X        X       城 门      X          X

void creatMainCity(Area &main_city)
{
    auto &rooms = main_city.getArea();

    auto setupRoom = [&rooms](const int x, const int y, const string &name, const string &description, const Content content) {
        rooms[x][y].Setup(name, description, content);
    };

    setupRoom(3, 2, EMPTY_ROOM, DEFAULT_DESCRIPTION, Content::EMPTY);
    setupRoom(3, 3, EMPTY_ROOM, DEFAULT_DESCRIPTION, Content::EMPTY);
    setupRoom(3, 4, EMPTY_ROOM, DEFAULT_DESCRIPTION, Content::EMPTY);

    setupRoom(3, 1, "城门", "这里是" + place("城门") + "，门口有一辆马夫，可以载你去其他地方。", Content::NPC);

    setupRoom(2, 2, "医馆", "这里是" + place("医馆") + "，这位医生医术十分精湛，你可以从这里治疗或购买药品。", Content::NPC);

    setupRoom(4, 2, "商店", "这里是" + place("杂货商店") + "，你可以从这里购买一些物品。", Content::NPC);

    setupRoom(2, 3, "铁匠铺", "这里是" + place("铁匠铺") + "，看起来师傅正在打造一把剑。", Content::NPC);

    setupRoom(4, 3, "居民区", "这里的人们叽叽喳喳的在讨论着什么，要不前去问问把。", Content::NPC);

    setupRoom(2, 4, "居民区", place("居民区") + "这里居住了一些人。", Content::NPC);
    setupRoom(4, 4, "居民区", place("居民区") + "这里居住了一些人。", Content::NPC);

    setupRoom(3, 5, "城主府", "这里便是" + place("城主府") + "了，城主看起来愁眉苦脸的。", Content::NPC);
}
