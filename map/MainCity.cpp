#include "Constant.h"
#include "CreatMap.h"
#include "Helper.h"
using namespace std;

// 主城
//  X        X       城主府      X         X
//  X       居民区     空       居民区       X
//  X       铁匠铺     空       任务地点     X
//  X       医院     出生地      商店        X
//  X        X       城 门      X          X

void creatMainCity(Area &main_city)
{
    auto &rooms = main_city.getArea();
    auto setup_room = [&rooms](const int x, const int y, const string &name, const string &description, const RoomContent content) {
        rooms[x][y].setup(name, description, content);
    };
    setup_room(3, 2, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 3, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 4, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 1, "城门", "这里是" + place("城门") + "，门口有一辆马夫，可以载你去其他地方。", RoomContent::NPC);
    setup_room(2, 2, "医馆", "这里是" + place("医馆") + "，这位医生医术十分精湛，你可以从这里治疗或购买药品。", RoomContent::NPC);
    setup_room(4, 2, "商店", "这里是" + place("杂货商店") + "，你可以从这里购买一些物品。", RoomContent::NPC);
    setup_room(2, 3, "铁匠铺", "这里是" + place("铁匠铺") + "，看起来师傅正在打造一把剑。", RoomContent::NPC);
    setup_room(4, 3, "居民区", "这里的人们叽叽喳喳的在讨论着什么，要不前去问问把。", RoomContent::NPC);
    setup_room(2, 4, "居民区", place("居民区") + "这里居住了一些人。", RoomContent::NPC);
    setup_room(4, 4, "居民区", place("居民区") + "这里居住了一些人。", RoomContent::NPC);
    setup_room(3, 5, "城主府", "这里便是" + place("城主府") + "了，城主看起来愁眉苦脸的。", RoomContent::NPC);
}

