#pragma once

#include <string>
#include <vector>
#include "Constant.h"

class Room;

class Area
{
public:
    // 构造函数
    explicit Area(std::string name);

    // getter
    [[nodiscard]] std::string getName() const;
    std::vector<std::vector<Room> > &getArea();

private:
    std::string name {};
    std::vector<std::vector<Room> > area;
};

class Room
{
public:
    // 构造函数

    Room();

    Room(std::string name, RoomContent content);

    // getter & setter

    [[nodiscard]] std::string getName() const;


    [[nodiscard]] RoomContent getContent() const;

    void setContent(RoomContent content);

    [[nodiscard]] bool canPass() const;

    [[nodiscard]] std::string getDescription() const;

    void setup(const std::string &name, std::string description, RoomContent content);

private:
    bool can_pass {};                              // 能否通过
    std::string name {EMPTY_ROOM};                 // 房间的名字
    std::string description {DEFAULT_DESCRIPTION}; // 房间内的描述
    RoomContent content {RoomContent::EMPTY};      // 房间的内容物
};
