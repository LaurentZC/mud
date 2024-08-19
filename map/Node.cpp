//
// Created by 32186 on 24-8-19.
//

#include "Node.h"

Node::Node(string newName, int x, int y)
{
    name = std::move(newName);
    position = make_pair(x, y);
}
