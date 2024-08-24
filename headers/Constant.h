#pragma once

#include <string>

// 地图相关
constexpr int MAP_MAX_SIZE = 5;                  // 最大地图尺寸
const std::string EMPTY_ROOM = "空房间";                 // 空房间的名字
const std::string DEFAULT_DESCRIPTION = "这里看起来空空如也。"; // 空房间默认描述
const std::string EMPTY_CONTENT = "empty";            // 空地图节点
const std::string ENEMY = "enemy";                    // 房间内敌人
const std::string ELITE = "elite";                    // 房间内的精英怪
const std::string BOSS = "boss";                      // boss

// 颜色相关
const std::string RESET = "\033[0m";         // 重置文本颜色
const std::string RED = "\033[31m";          // 红色，boss
const std::string GREEN = "\033[32m";        // 绿色，任务
const std::string YELLOW = "\033[33m";       // 黄色，小怪
const std::string BLUE = "\033[34m";         // 蓝色，地点
const std::string PURPLE = "\033[35m";       // 紫色，
const std::string ORANGE = "\033[38;5;208m"; // 橙色，精英怪

// 方向相关
const std::string UP = "up";        // 上
const std::string DOWN = "down";    // 下
const std::string LEFT = "left";    // 左
const std::string RIGHT = "right";  // 右