#pragma once

#include <string>
#include <vector>
#include "Constant.h"

class Room;

class Map
{
    std::string name {};
    std::vector<std::vector<Room> > map;

    public:
        // 构造函数
    explicit Map(std::string name);

    // getter
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::vector<std::vector<Room> > &getMap();
};

class Room
{
    bool can_pass {};
    std::string name {EMPTY_ROOM};                 // 房间的名字
    std::string content {EMPTY_CONTENT};           // 里面含有的东西
    std::string description {DEFAULT_DESCRIPTION}; // 房间描述

    public:
        // 构造函数

    Room();

    Room(std::string name, std::string content);

    // getter & setter

    [[nodiscard]] std::string getName() const;

    void setName(std::string name);

    [[nodiscard]] std::string getContent() const;

    void setContent(std::string content);

    [[nodiscard]] bool canPass() const;

    void setPass(bool entry);

    [[nodiscard]] std::string getDescription() const;

    void setDescription(std::string description);

    void Setup(const std::string &name, std::string description = DEFAULT_DESCRIPTION, std::string content = EMPTY_CONTENT);
};
