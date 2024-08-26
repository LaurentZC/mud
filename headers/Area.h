#pragma once

#include <string>
#include <vector>
#include "Constant.h"

class Room;

class Area
{
public:
    // ���캯��
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
    // ���캯��

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
    bool can_pass {};                              // �ܷ�ͨ��
    std::string name {EMPTY_ROOM};                 // ���������
    std::string description {DEFAULT_DESCRIPTION}; // �����ڵ�����
    Content content {Content::EMPTY};              // �����������
};


