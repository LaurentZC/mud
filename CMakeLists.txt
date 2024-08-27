cmake_minimum_required(VERSION 3.28)
project(mud)

# 设置 C++ 标准为 C++ 17
set(CMAKE_CXX_STANDARD 17)

# 添加 .cpp 源文件
file(GLOB_RECURSE SOURCES
     "buff/*.cpp"
     "player/*.cpp"
     "enemy/*.cpp"
     "equipment/*.cpp"
     "game/*.cpp"
     "map/*.cpp"
     "npc/*.cpp"
     "other/*.cpp"
     "skill/*.cpp"
     )
# 为 .cpp 文件添加可执行文件
add_executable(mud ${SOURCES})
# 添加头文件
target_include_directories(mud PUBLIC ${CMAKE_SOURCE_DIR}/headers)
# 添加 fmt 头文件目录
add_subdirectory(fmt)
# 链接 fmt 库
target_link_libraries(mud PUBLIC fmt::fmt)
# 设置编译器选项以使用 GBK 编码
add_compile_options(-finput-charset=GBK -fexec-charset=GBK)


