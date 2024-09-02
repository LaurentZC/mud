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
    // ������ʽ�ַ�����ֱ�ӷ��ؿ�ʼλ��
    static constexpr auto parse(const format_parse_context &ctx) { return ctx.begin(); }

    // ��ʽ�� 2D �ַ�������
    template <typename FormatContext>
    auto format(const std::vector<std::vector<std::string> > &grid, FormatContext &ctx)
    {
        std::string result;
        size_t max_width = 0;

        // ����ÿ����Ԫ��������
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                max_width = std::max(max_width, cell.length());
            }
        }

        // ȷ����ȣ����������ź����
        const size_t width = fmt::format(fg(color::yellow), "[{}]", std::string(max_width, ' ')).length() + 1;

        // ��ʽ��ÿһ��
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
