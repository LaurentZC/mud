#pragma once

#include "Area.h"
#include "fmt/color.h"
#include "fmt/core.h"

void movePlayerLocation(Area &map, int &x, int &y);

void handleQuit(Area &current_map, bool &quit, int &x, int &y);

void changeMap(Area &map, int &x, int &y);

template <>
struct fmt::formatter<std::vector<std::vector<std::string> > >
{
    // 解析格式字符串，直接返回开始位置
    static constexpr auto parse(const format_parse_context &ctx) { return ctx.begin(); }

    // 格式化 2D 字符串向量
    template <typename FormatContext>
    auto format(const std::vector<std::vector<std::string> > &grid, FormatContext &ctx)
    {
        std::string result;
        size_t max_width = 0;

        // 计算每个单元格的最大宽度
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                max_width = std::max(max_width, cell.length());
            }
        }

        // 确定宽度，包括方括号和填充
        const size_t width = fmt::format(fg(color::yellow), "[{}]", std::string(max_width, ' ')).length() + 1;

        // 格式化每一行
        for (const auto &row : grid) {
            bool has_content = false;
            for (const auto &cell : row) {
                if (!cell.empty()) {
                    has_content = true;
                    std::string bracketed_cell = fmt::format("[{}]", cell);
                    std::string colored_cell = fmt::format(fg(color::yellow), bracketed_cell);
                    result += fmt::format("{:<{}}", colored_cell, width);
                }
            }
            if (has_content)
                result += "\n";
        }
        return fmt::format_to(ctx.out(), "{}\n", result);
    }
};
