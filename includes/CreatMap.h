#pragma once

#include <Helper.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "Area.h"
#include "fmt/color.h"

// ≥«√≈Œª÷√
inline std::unordered_map<std::string, std::pair<int, int> > Gates = {
    {area("main_city"), std::make_pair(3, 1)},
    {area("wu_wei_cheng"), std::make_pair(3, 1)},
    {area("shang_hui"), std::make_pair(3, 5)}
};

struct TextColor
{
    std::vector<std::string> keys;
    fmt::color color;

    TextColor(std::vector<std::string> keys, const fmt::color color) : keys(std::move(keys)), color(color) { };
};

void changeColor(std::string &text, const std::vector<TextColor> &colors);

void changeColor(std::string &text);

Area creatMainCity();

Area creatWuWeiCheng();

Area creatShangHui();
