#include "Constant.h"
#include "CreatMap.h"
#include "Helper.h"

using namespace std;

//   X      X      X    X      X
//   X      X     npc   X      X
// �����ֿ�  X     ½��   X    ��ҩ�ֿ�
// ������   С��    ��   С��   �׻���
//   X    ����ͤ  ����  ����ͤ    X

void creatWuWeiCheng(Area &wu_wei_cheng)
{
    auto &rooms = wu_wei_cheng.getArea();

    auto setup_room = [&rooms](const int x, const int y, const string &name, const string &description, const RoomContent content) {
        rooms[x][y].setup(name, description, content);
    };

    setup_room(3, 1, "����", "����" + place("����") + "�����������������ս��������������ͼ����", RoomContent::GATE);
    setup_room(2, 1, "����ͤ", "������" + place("����ͤ") + "����������Щ" + minion("����") + "�ƺ��������㡣", RoomContent::MONSTER);
    setup_room(4, 1, "����ͤ", "������" + place("����ͤ") + "����������Щ" + minion("����") + "�ƺ��������㡣", RoomContent::MONSTER);
    setup_room(1, 2, "������", "����վ�ŵ�����½�������ұۡ���" + elite("������") + "����������ʮ��ǿ��", RoomContent::ELITE);
    setup_room(5, 2, "�׻���", "����վ�ŵ�����½�������ұۡ���" + elite("�׻���") + "����������ʮ��ǿ��", RoomContent::ELITE);
    setup_room(2, 2, "������", "����ǰ��" + place("������") + "��·��������" + minion("½�������") + "���������ǣ�", RoomContent::MONSTER);
    setup_room(4, 2, "�׻���", "����ǰ��" + place("�׻���") + "��·��������" + minion("½�������") + "���������ǣ�", RoomContent::MONSTER);
    setup_room(3, 2, EMPTY_ROOM, DEFAULT_DESCRIPTION, RoomContent::EMPTY);
    setup_room(3, 3, "����¥", "ֻ��" + boss("½��") + "վ�����", RoomContent::BOSS);
    setup_room(1, 3, "�ֿ�", "������" + boss("½��") + "��" + place("�ֿ�") + "�����Ǹ����ӿ�����ʲô�ɣ�", RoomContent::CHEST);
    setup_room(5, 3, "�ֿ�", "������" + boss("½��") + "��" + place("�ֿ�") + "�����Ǹ����ӿ�����ʲô�ɣ�", RoomContent::CHEST);
    setup_room(3, 4, "������", "�����Ѻ��һ���ˣ���ǰ������ô���°ѡ�", RoomContent::NPC);
}
