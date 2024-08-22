cmake_minimum_required(VERSION 3.28)
project(mud)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件和头文件
set(SOURCES
    game/main.cpp
    buff/Buff.cpp
    class/Player.cpp
    enemy/Enemy.cpp
    equipment/Equipment.cpp
    map/Map.cpp
    map/xing_wu_cheng.cpp
    npc/NPC.cpp
    other/Bag.cpp
    other/Helper.cpp
    other/Task.cpp
    skill/Skill.cpp
    )

set(HEADERS
    headers/constant.h
    headers/Task.h
    headers/Equipment.h
    headers/Buff.h
    headers/Bag.h
    headers/Skill.h
    headers/Player.h
    headers/NPC.h
    headers/Enemy.h
    headers/Map.h
    headers/Helper.h
    )

# 添加可执行文件
add_executable(mud ${SOURCES} ${HEADERS})
