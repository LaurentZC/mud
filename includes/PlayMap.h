#pragma once

#include "Area.h"

void movePlayerLocation(Area &map);

void movePlayerLocation(Area &map, bool);

void changeMap(Area &map);

void handleQuit(Area &current_map, bool &quit);

void printMap(const std::vector<std::vector<Room> > &grid);

void playWuWeiCheng(Area &map);

void playShangHui(Area &map);
