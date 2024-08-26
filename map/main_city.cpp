#include "../headers/CreatMap.h"

using namespace std;

//  X        X       ������      X         X
//  X       ������     ��       ������       X
//  X       ������     ��       ����ص�     X
//  X       ҽԺ     ������      �̵�        X
//  X        X       �� ��      X          X

void creatMainCity(Area &main_city)
{
    auto &rooms = main_city.getArea();

    auto setupRoom = [&rooms](const int x, const int y, const string &name, const string &description, const Content content) {
        rooms[x][y].Setup(name, description, content);
    };

    setupRoom(3, 2, EMPTY_ROOM, DEFAULT_DESCRIPTION, Content::EMPTY);
    setupRoom(3, 3, EMPTY_ROOM, DEFAULT_DESCRIPTION, Content::EMPTY);
    setupRoom(3, 4, EMPTY_ROOM, DEFAULT_DESCRIPTION, Content::EMPTY);

    setupRoom(3, 1, "����", "������" + place("����") + "���ſ���һ����򣬿�������ȥ�����ط���", Content::NPC);

    setupRoom(2, 2, "ҽ��", "������" + place("ҽ��") + "����λҽ��ҽ��ʮ�־�տ������Դ��������ƻ���ҩƷ��", Content::NPC);

    setupRoom(4, 2, "�̵�", "������" + place("�ӻ��̵�") + "������Դ����ﹺ��һЩ��Ʒ��", Content::NPC);

    setupRoom(2, 3, "������", "������" + place("������") + "��������ʦ�����ڴ���һ�ѽ���", Content::NPC);

    setupRoom(4, 3, "������", "���������ߴߴ��������������ʲô��Ҫ��ǰȥ���ʰѡ�", Content::NPC);

    setupRoom(2, 4, "������", place("������") + "�����ס��һЩ�ˡ�", Content::NPC);
    setupRoom(4, 4, "������", place("������") + "�����ס��һЩ�ˡ�", Content::NPC);

    setupRoom(3, 5, "������", "�������" + place("������") + "�ˣ�������������ü�����ġ�", Content::NPC);
}
