#pragma once

#include <Helper.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "Area.h"
#include "fmt/color.h"

// 城门位置
// @formatter:off
inline std::unordered_map<std::string, std::pair<int, int> > Gates = {
    {area("main_city"), {5, 3}},
    {area("wu_wei_cheng"), {4, 3}},
    {area("shang_hui"), {4, 3}}
};
// @formatter:on

struct TextColor
{
    std::vector<std::string> keys;
    fmt::color color;

    TextColor(std::vector<std::string> keys, const fmt::color color) : keys(std::move(keys)), color(color) { };
};

void changeColor(std::string &text, const std::vector<TextColor> &colors);

Area creatMainCity();

Area creatWuWeiCheng();

Area creatShangHui();
