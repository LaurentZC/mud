# 最低版本 cmake
cmake_minimum_required(VERSION 3.20)

# 设置项目
project(mud)

# 要求至少 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加 .cpp 源文件
file(GLOB SOURCES
     "src/*.cpp"
     "src/player/*.cpp"
     "src/enemy/*.cpp"
     "src/equipment/*.cpp"
     "src/map/*.cpp"
     "src/npc/*.cpp"
     "src/skill/*.cpp")

# 删除 byd windows 定义的 min 和 max
if (WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif ()

# 为 .cpp 文件添加可执行文件
add_executable(mud ${SOURCES})

# 添加头文件
target_include_directories(mud PUBLIC ${CMAKE_SOURCE_DIR}/includes)

# 添加 fmt 头文件目录
add_subdirectory(fmt)

# 链接 fmt 库
target_link_libraries(mud PUBLIC fmt::fmt)

# 设置 ccache 加速编译
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
endif ()

