//
// Created by 32186 on 24-8-22.
//

#include "../headers/Map.h"
#include "../headers/Helper.h"

using namespace std;


Map creatXingWuLou()
{
    Map xing_wu_lou("xing_wu_lou");

    auto rooms = xing_wu_lou.getMap();
    rooms[3][1].Setup("城门", "这座" + Place("城门") + "坚固如铁，上面雕刻着战斗场景和武器的图案。", "城门");

    rooms[2][1].Setup("门卫亭", "这里是" + Place("门卫亭") + "，看起来这些" + Minion("门卫") + "似乎正在摸鱼。", ENEMY);
    rooms[4][1].Setup("门卫亭", "这里是" + Place("门卫亭") + "，看起来这些" + Minion("门卫") + "似乎正在摸鱼。", ENEMY);

    rooms[1][2].Setup("青龙堂", "这里站着的人是陆洪的左膀右臂——" + Elite("青龙卫") + "，他看起来十分强大！", ELITE);
    rooms[5][2].Setup("白虎堂", "这里站着的人是陆洪的左膀右臂——" + Elite("白虎卫") + "，他看起来十分强大！", ELITE);

    rooms[2][2].Setup("青龙堂", "你在前往" + Place("青龙堂") + "的路上遇到了" + Minion("陆洪的手下") + "，请打败他们！", ENEMY);
    rooms[4][2].Setup("白虎堂", "你在前往" + Place("白虎堂") + "的路上遇到了" + Minion("陆洪的手下") + "，请打败他们！", ENEMY);

    rooms[3][2].Setup(EMPTY_ROOM, DEFAULT_DESCRIPTION, EMPTY_CONTENT);

    rooms[3][3].Setup("洪武楼", "只有" + Boss("陆洪") + "站在这里。", EMPTY_CONTENT);

    rooms[1][3].Setup("仓库", "这里是" + Boss("陆洪") + "的" + Place("仓库") + "，打开那个箱子看看有什么吧！");
    rooms[5][3].Setup("仓库", "这里是" + Boss("陆洪") + "的" + Place("仓库") + "，打开那个箱子看看有什么吧！");

    return xing_wu_lou;
}
