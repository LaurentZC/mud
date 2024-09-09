#pragma once

#include <string>
#include <vector>

// 地图最大尺寸
inline constexpr int MAP_MAX_SIZE = 5;

class Room;

class Area
{
public:
    // 构造函数
    explicit Area(std::string name);

    // getter
    [[nodiscard]] std::string getName() const;
    std::string getName(int) const;
    [[nodiscard]] std::vector<std::vector<Room> > &getArea();

private:
    std::string name {};
    std::vector<std::vector<Room> > areas;
};

class Room
{
public:
    // 房间的内容，分别是：空，宝箱，门，npc，小怪，精英怪，boss，陷阱，毒
    enum class Content { EMPTY, CHEST, GATE, NPC, MONSTER, ELITE, BOSS, TRAP, POISON };

    // 构造函数
    Room();
    Room(std::string name, Content content);

    void clear();

    // getter & setter
    [[nodiscard]] std::string getName() const;
    void setName(const std::string &name);
    [[nodiscard]] Content getContent() const;
    void setContent(Content content);
    [[nodiscard]] bool canPass() const;
    [[nodiscard]] std::string getDescription() const;
    void setDescription(std::string description);
    void setup(std::string name, std::string description, Content content);

private:
    bool can_pass {};                 // 能否通过
    std::string name;                 // 房间的名字
    std::string description;          // 房间内的描述
    Content content {Content::EMPTY}; // 房间的内容物
};
