#include "Constant.h"
#include "CreatMap.h"
#include "Helper.h"
using namespace std;

// ����
//  X        X       ������      X         X
//  X       ������     ��       ������       X
//  X       ������     ��       ����ص�     X
//  X       ҽԺ     ������      �̵�        X
//  X        X       �� ��      X          X

void creatMainCity(Area &main_city)
{
    auto &rooms = main_city.getArea();
    auto setup_room = [&rooms](const int x, const int y, const string &name, const string &description, const RoomContent content) {
        rooms[x][y].setup(name, description, content);
    };
    setup_room(3, 2, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 3, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 4, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 1, "����", "������" + place("����") + "���ſ���һ����򣬿�������ȥ�����ط���", RoomContent::NPC);
    setup_room(2, 2, "ҽ��", "������" + place("ҽ��") + "����λҽ��ҽ��ʮ�־�տ������Դ��������ƻ���ҩƷ��", RoomContent::NPC);
    setup_room(4, 2, "�̵�", "������" + place("�ӻ��̵�") + "������Դ����ﹺ��һЩ��Ʒ��", RoomContent::NPC);
    setup_room(2, 3, "������", "������" + place("������") + "��������ʦ�����ڴ���һ�ѽ���", RoomContent::NPC);
    setup_room(4, 3, "������", "���������ߴߴ��������������ʲô��Ҫ��ǰȥ���ʰѡ�", RoomContent::NPC);
    setup_room(2, 4, "������", place("������") + "�����ס��һЩ�ˡ�", RoomContent::NPC);
    setup_room(4, 4, "������", place("������") + "�����ס��һЩ�ˡ�", RoomContent::NPC);
    setup_room(3, 5, "������", "�������" + place("������") + "�ˣ�������������ü�����ġ�", RoomContent::NPC);
}

