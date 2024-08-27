#include "Constant.h"
#include "CreatMap.h"
#include "Helper.h"

using namespace std;

//   X      X      X    X      X
//   X      X     npc   X      X
// 武器仓库  X     陆洪   X    丹药仓库
// 青龙堂   小怪    空   小怪   白虎堂
//   X    门卫亭  城门  门卫亭    X

void creatWuWeiCheng(Area &wu_wei_cheng)
{
    auto &rooms = wu_wei_cheng.getArea();

    auto setup_room = [&rooms](const int x, const int y, const string &name, const string &description, const RoomContent content) {
        rooms[x][y].setup(name, description, content);
    };

    setup_room(3, 1, "城门", "这座" + place("城门") + "坚固如铁，上面雕刻着战斗场景和武器的图案。", RoomContent::GATE);
    setup_room(2, 1, "门卫亭", "这里是" + place("门卫亭") + "，看起来这些" + minion("门卫") + "似乎正在摸鱼。", RoomContent::MONSTER);
    setup_room(4, 1, "门卫亭", "这里是" + place("门卫亭") + "，看起来这些" + minion("门卫") + "似乎正在摸鱼。", RoomContent::MONSTER);
    setup_room(1, 2, "青龙堂", "这里站着的人是陆洪的左膀右臂——" + elite("青龙卫") + "，他看起来十分强大！", RoomContent::ELITE);
    setup_room(5, 2, "白虎堂", "这里站着的人是陆洪的左膀右臂——" + elite("白虎卫") + "，他看起来十分强大！", RoomContent::ELITE);
    setup_room(2, 2, "青龙堂", "你在前往" + place("青龙堂") + "的路上遇到了" + minion("陆洪的手下") + "，请打败他们！", RoomContent::MONSTER);
    setup_room(4, 2, "白虎堂", "你在前往" + place("白虎堂") + "的路上遇到了" + minion("陆洪的手下") + "，请打败他们！", RoomContent::MONSTER);
    setup_room(3, 2, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 3, "洪武楼", "只有" + boss("陆洪") + "站在这里。", RoomContent::BOSS);
    setup_room(1, 3, "仓库", "这里是" + boss("陆洪") + "的" + place("仓库") + "，打开那个箱子看看有什么吧！", RoomContent::CHEST);
    setup_room(5, 3, "仓库", "这里是" + boss("陆洪") + "的" + place("仓库") + "，打开那个箱子看看有什么吧！", RoomContent::CHEST);
    setup_room(3, 4, "囚禁室", "这里关押着一个人，上前看看怎么回事把。", RoomContent::NPC);
}
