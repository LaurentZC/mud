#include "Player.h"
#include "fmt/core.h"

int Player::getStrength() const { return strength; }

void Player::openBag() const
{
    bag->display();
    fmt::println("�����ʹ��[u]ʹ�õ���/װ����[c]�ķ�ʽ�鿴����/װ�����ԡ�");
}
