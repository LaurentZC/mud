cmake_minimum_required(VERSION 3.28)
project(mud)

# 设置 C++ 标准为 C++ 17
set(CMAKE_CXX_STANDARD 17)

# 添加源文件和头文件
file(GLOB_RECURSE SOURCES
     "buff/*.cpp"
     "class/*.cpp"
     "enemy/*.cpp"
     "equipment/*.cpp"
     "game/*.cpp"
     "map/*.cpp"
     "npc/*.cpp"
     "other/*.cpp"
     "skill/*.cpp"
     )

file(GLOB_RECURSE HEADERS "headers/*.h")

# 添加可执行文件
add_executable(mud ${SOURCES} ${HEADERS})
