#pragma once

#include "Area.h"
#include "fmt/color.h"
#include "fmt/core.h"

void movePlayerLocation(Area &map, int &x, int &y);

void handleQuit(Area &current_map, bool &quit, int &x, int &y);

void changeMap(Area &map, int &x, int &y);

void printMap(std::vector<std::vector<std::string> > grid);
