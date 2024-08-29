#pragma once

#include <string>
#include <vector>

// ��ͼ���ߴ�
inline constexpr int MAP_MAX_SIZE = 5;


enum class Map { MainCity, WuWeiCheng };

class Room;

class Area
{
public:
    // ���캯��
    explicit Area(std::string name);

    // getter
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::vector<std::vector<Room> > &getArea();

private:
    std::string name {};
    std::vector<std::vector<Room> > area;
};

class Room
{
public:
    // ��������ݣ��ֱ��ǣ��գ����䣬�ţ�npc��С�֣���Ӣ�֣�boss�����壬��
    enum class Content { EMPTY, CHEST, GATE, NPC, MONSTER, ELITE, BOSS, TRAP, POISON };

    // ���캯��
    Room();
    Room(std::string name, Content content);

    // getter & setter
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] Content getContent() const;
    void setContent(Content content);
    [[nodiscard]] bool canPass() const;
    [[nodiscard]] std::string getDescription() const;
    void setDescription(std::string description);
    void setup(const std::string &name, std::string description, Content content);

private:
    bool can_pass {};                 // �ܷ�ͨ��
    std::string name;                 // ���������
    std::string description;          // �����ڵ�����
    Content content {Content::EMPTY}; // �����������
};
