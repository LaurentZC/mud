//
// Created by 32186 on 24-8-19.
//

#include "../headers/Map.h"

Room::Room() = default;

Room::Room(string name, string content) : name(std::move(name)), content(std::move(content)) { }

string Room::getName() const { return name; }

void Room::setName(string name) { this->name = std::move(name); }

string Room::getContent() const { return content; }

void Room::setContent(string content) { this->content = std::move(content); }

bool Room::canPass() const { return can_pass; }

void Room::setPass(const bool entry) { can_pass = entry; }

string Room::getDescription() const { return description; }

void Room::setDescription(string description) { this->description = std::move(description); }

void Room::Setup(const string &name, string description, string content)
{
    this->can_pass = true;
    this->name = Place(name);
    this->description = std::move(description);
    this->content = std::move(content);
}

Map::Map(string name) : name(std::move(name)), map(MAP_MAX_SIZE + 1, vector<Room>(MAP_MAX_SIZE + 1)) { }

string Map::getName() const { return name; }

vector<vector<Room> > &Map::getMap() { return map; }
