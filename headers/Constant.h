//
// Created by 32186 on 19/8/2024.
//

#pragma once
#include <string>
using namespace std;

constexpr int MAP_MAX_SIZE = 5;                  // 最大地图尺寸
const string EMPTY_ROOM = "空房间";                 // 空房间的名字
const string DEFAULT_DESCRIPTION = "这里看起来空空如也。"; // 空房间默认描述
const string EMPTY_CONTENT = "empty";            // 空地图节点
const string ENEMY = "enemy";                    // 房间内敌人
const string ELITE = "elite";                    // 房间内的精英怪

const string RESET = "\033[0m";         // 重置文本颜色
const string RED = "\033[31m";          // 红色，boss
const string GREEN = "\033[32m";        // 绿色
const string YELLOW = "\033[33m";       // 黄色，小怪
const string BLUE = "\033[34m";         // 蓝色
const string PURPLE = "\033[35m";       // 紫色
const string ORANGE = "\033[38;5;208m"; // 橙色，精英怪
