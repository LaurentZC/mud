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

    Room(std::string name, RoomContent content);

    // getter & setter

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] RoomContent getContent() const;

    void setContent(RoomContent content);

    [[nodiscard]] bool canPass() const;

    [[nodiscard]] std::string getDescription() const;

    void setDescription(std::string description);

    void setup(const std::string &name, std::string description, RoomContent content);

private:
    bool can_pass {};        // �ܷ�ͨ��
    std::string name;        // ���������
    std::string description; // �����ڵ�����
    RoomContent content;     // �����������
};
