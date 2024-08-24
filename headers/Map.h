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
        // ���캯��
    explicit Map(std::string name);

    // getter
    std::string getName() const;
    std::vector<std::vector<Room> > &getMap();
};

class Room
{
    bool can_pass {};
    std::string name {EMPTY_ROOM};                 // ���������
    std::string content {EMPTY_CONTENT};           // ���溬�еĶ���
    std::string description {DEFAULT_DESCRIPTION}; // ��������

    public:
        // ���캯��

    Room();

    Room(std::string name, std::string content);

    // getter & setter

    std::string getName() const;

    void setName(std::string name);

    std::string getContent() const;

    void setContent(std::string content);

    bool canPass() const;

    void setPass(bool entry);

    std::string getDescription() const;

    void setDescription(std::string description);

    void Setup(const std::string &name, std::string description = DEFAULT_DESCRIPTION, std::string content = EMPTY_CONTENT);
};
