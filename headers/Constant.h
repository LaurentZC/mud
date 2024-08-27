#pragma once

#include <string>

// 地图相关
constexpr int MAP_MAX_SIZE = 5;                       // 最大地图尺寸
const std::string EMPTY_ROOM = "空房间";                 // 空房间的名字
const std::string DEFAULT_DESCRIPTION = "这里看起来空空如也。"; // 空房间默认描述

enum class RoomContent { EMPTY, CHEST, GATE, NPC, MONSTER, ELITE, BOSS }; // 房间的内容，分别是：空，宝箱，门，npc，小怪，精英怪，boss
enum class PillType { BLOOD_PILL, MANA_PILL };                            // 回血丹，回蓝丹
enum class PillSize { BIG, MID, SMALL };                                  // 大、中、小号
// 方向相关
constexpr char UP = 'w';    // 上
constexpr char DOWN = 's';  // 下
constexpr char LEFT = 'a';  // 左
constexpr char RIGHT = 'd'; // 右
