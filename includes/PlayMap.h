#pragma once

#include "Area.h"

void movePlayerLocation(Area &map, int &x, int &y);

void handleQuit(Area &current_map, bool &quit, int &x, int &y);

void changeMap(Area &map, int &x, int &y);

void printMap(std::vector<std::vector<Room> > grid);

void playWuWeiCheng(Area &map, int &x, int &y);

void playShangHui(Area &map, int &x, int &y);
