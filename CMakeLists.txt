cmake_minimum_required(VERSION 3.28)
project(mud)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        mud

        game/main.cpp

        headers/color.h headers/constant.h

        headers/Task.h other/Task.cpp

        headers/Equipment.h equipment/Equipment.cpp

        headers/Buff.h buff/Buff.cpp

        headers/Bag.h other/Bag.cpp

        headers/Skill.h skill/Skill.cpp

        headers/Player.h class/Player.cpp

        headers/NPC.h npc/NPC.cpp

        headers/Enemy.h enemy/Enemy.cpp

        map/map.cpp headers/Node.h map/Node.cpp
        )
