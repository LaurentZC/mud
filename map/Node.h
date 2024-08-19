//
// Created by 32186 on 24-8-19.
//

#pragma once
#include <memory>
#include <string>
using namespace std;

class Node
{
    string name;
    bool hasPlayer {};
    bool hasEnemy {};
    bool hasBoss {};
    bool hasNPC {};

    pair<int, int> position;
    unique_ptr<Node> prev;
    unique_ptr<Node> next;

public:
    Node(string newName, int x, int y);
};
