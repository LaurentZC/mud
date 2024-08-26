#pragma once

#include <string>

// 地图相关
constexpr int MAP_MAX_SIZE = 5;                       // 最大地图尺寸
const std::string EMPTY_ROOM = "空房间";                 // 空房间的名字
const std::string DEFAULT_DESCRIPTION = "这里看起来空空如也。"; // 空房间默认描述

enum class Map { MAIN_CITY, WU_WEI_CHENG };                           // 地图
enum class Content { EMPTY, CHEST, GATE, NPC, MONSTER, ELITE, BOSS }; // 房间的内容，分别是：空，宝箱，门，npc，小怪，精英怪，boss

// 颜色相关
const std::string RESET = "\033[0m";         // 重置文本颜色
const std::string RED = "\033[31m";          // 红色，boss
const std::string GREEN = "\033[32m";        // 绿色，任务
const std::string YELLOW = "\033[33m";       // 黄色，小怪
const std::string BLUE = "\033[34m";         // 蓝色，地点
const std::string PURPLE = "\033[35m";       // 紫色，
const std::string ORANGE = "\033[38;5;208m"; // 橙色，精英怪

// 方向相关
constexpr char UP = 'w';    // 上
constexpr char DOWN = 's';  // 下
constexpr char LEFT = 'a';  // 左
constexpr char RIGHT = 'd'; // 右
