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
    std::string getName() const;
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

    Room(std::string name, Content content);

    // getter & setter

    std::string getName() const;

    void setName(std::string name);

    Content getContent() const;

    void setContent(Content content);

    bool canPass() const;

    void setPass(bool entry);

    std::string getDescription() const;

    void setDescription(std::string description);

    void Setup(const std::string &name, std::string description = DEFAULT_DESCRIPTION, Content content = Content::EMPTY);

private:
    bool can_pass {};                              // 能否通过
    std::string name {EMPTY_ROOM};                 // 房间的名字
    std::string description {DEFAULT_DESCRIPTION}; // 房间内的描述
    Content content {Content::EMPTY};              // 房间的内容物
};


