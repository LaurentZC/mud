#pragma once

#include "Area.h"

void movePlayerLocation(Area &map);

void changeMap(Area &map);

void handleQuit(Area &current_map, bool &quit);

void printMap(std::vector<std::vector<Room> > grid);

void playWuWeiCheng(Area &map);

void playShangHui(Area &map);
