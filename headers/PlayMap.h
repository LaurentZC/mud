#pragma once

#include <utility>
#include "../headers/Area.h"

std::pair<int, int> enterNewMap(Area &map);

void movePlayerLocation(Area &map, int &x, int &y);

Area creatWuWeiCheng();
