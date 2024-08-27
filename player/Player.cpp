#include "Player.h"
#include "fmt/core.h"

int Player::getStrength() const { return strength; }

void Player::openBag() const
{
    bag->display();
    fmt::println("你可以使用[u]使用道具/装备，[c]的方式查看道具/装备属性。");
}
