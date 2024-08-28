#include "Area.h"
#include <string>
#include <vector>
#include "Constant.h"
#include "Helper.h"

using namespace std;

Room::Room() = default;

Room::Room(string name, const RoomContent content) : name(std::move(name)), content(content) { }

string Room::getName() const { return name; }

RoomContent Room::getContent() const { return content; }

void Room::setContent(const RoomContent content) { this->content = content; }

bool Room::canPass() const { return can_pass; }

string Room::getDescription() const { return description; }

void Room::setDescription(string description) { this->description = std::move(description); }

void Room::setup(const string &name, string description, const RoomContent content)
{
    this->can_pass = true;
    this->name = place(name);
    this->description = std::move(description);
    this->content = content;
}

Area::Area(string name) : name(std::move(name)), area(MAP_MAX_SIZE + 1, vector<Room>(MAP_MAX_SIZE + 1)) { }

string Area::getName() const { return name; }

vector<vector<Room> > &Area::getArea() { return area; }
