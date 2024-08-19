cmake_minimum_required(VERSION 3.28)
project(mud)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        mud

        main.cpp

        constant/color.h constant/constant.h

        SmallClasses/Task.h SmallClasses/Task.cpp

        SmallClasses/Equipment.h SmallClasses/Equipment.cpp

        SmallClasses/Buff.h SmallClasses/Buff.cpp

        SmallClasses/Bag.h SmallClasses/Bag.cpp

        SmallClasses/Skill.h SmallClasses/Skill.cpp

        MainClasses/Player.h MainClasses/Player.cpp

        MainClasses/NPC.h MainClasses/NPC.cpp

        MainClasses/Enemy.h MainClasses/Enemy.cpp

        map/map.cpp
        map/Node.cpp
        map/Node.h
        )
