#pragma once

#include <string>
#include <vector>
#include "Constant.h"

using namespace std;

class Room;

class Map
{
    string name {};
    vector<vector<Room> > map;

public:
    // 构造函数
    explicit Map(string name);

    // getter
    [[nodiscard]] string getName() const;
    [[nodiscard]] vector<vector<Room> > &getMap();
};

class Room
{
    bool can_pass {};
    string name {EMPTY_ROOM};                 // 房间的名字
    string content {EMPTY_CONTENT};           // 里面含有的东西
    string description {DEFAULT_DESCRIPTION}; // 房间描述

public:
    // 构造函数

    Room();

    Room(string name, string content);

    // getter & setter

    [[nodiscard]] string getName() const;

    void setName(string name);

    [[nodiscard]] string getContent() const;

    void setContent(string content);

    [[nodiscard]] bool canPass() const;

    void setPass(bool entry);

    [[nodiscard]] string getDescription() const;

    void setDescription(string description);

    void Setup(const string &name, string description = DEFAULT_DESCRIPTION, string content = EMPTY_CONTENT);
};
