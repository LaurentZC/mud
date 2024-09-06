#include "Area.h"
#include <string>
#include <vector>
#include "fmt/color.h"

using namespace std;

Room::Room() = default;

Room::Room(string name, const Content content) : name(std::move(format(fg(fmt::color::blue), "{}", std::move(name)))), content(content) { }

void Room::clear()
{
    name = "空房间";
    description = "这里已经什么也没有了";
    content = Content::EMPTY;
}

string Room::getName() const { return name; }

void Room::setName(const string &name) { this->name = name; }

Room::Content Room::getContent() const { return content; }

void Room::setContent(const Content content) { this->content = content; }

bool Room::canPass() const { return can_pass; }

string Room::getDescription() const { return description; }

void Room::setDescription(string description) { this->description = std::move(description); }

void Room::setup(string name, string description, const Content content)
{
    this->can_pass = true;
    this->name = std::move(name);
    this->description = std::move(description);
    this->content = content;
}

Area::Area(string name) : name(std::move(name)), area(MAP_MAX_SIZE + 1, vector<Room>(MAP_MAX_SIZE + 1)) { }

string Area::getName() const { return name; }

vector<vector<Room> > &Area::getArea() { return area; }
