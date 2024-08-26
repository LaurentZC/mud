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
    [[nodiscard]] std::string getName() const;
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

    [[nodiscard]] std::string getName() const;


    [[nodiscard]] Content getContent() const;

    void setContent(Content content);

    [[nodiscard]] bool canPass() const;

    [[nodiscard]] std::string getDescription() const;

    void setup(const std::string &name, std::string description, Content content);

private:
    bool can_pass {};                              // �ܷ�ͨ��
    std::string name {EMPTY_ROOM};                 // ���������
    std::string description {DEFAULT_DESCRIPTION}; // �����ڵ�����
    Content content {Content::EMPTY};              // �����������
};
