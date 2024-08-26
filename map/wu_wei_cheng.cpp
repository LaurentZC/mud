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

    auto setupRoom = [&rooms](const int x, const int y, const string &name, const string &description, const Content content) {
        rooms[x][y].Setup(name, description, content);
    };

    setupRoom(3, 1, "����", "����" + place("����") + "�����������������ս��������������ͼ����", Content::GATE);

    setupRoom(2, 1, "����ͤ", "������" + place("����ͤ") + "����������Щ" + minion("����") + "�ƺ��������㡣", Content::MONSTER);
    setupRoom(4, 1, "����ͤ", "������" + place("����ͤ") + "����������Щ" + minion("����") + "�ƺ��������㡣", Content::MONSTER);

    setupRoom(1, 2, "������", "����վ�ŵ�����½�������ұۡ���" + elite("������") + "����������ʮ��ǿ��", Content::ELITE);
    setupRoom(5, 2, "�׻���", "����վ�ŵ�����½�������ұۡ���" + elite("�׻���") + "����������ʮ��ǿ��", Content::ELITE);

    setupRoom(2, 2, "������", "����ǰ��" + place("������") + "��·��������" + minion("½�������") + "���������ǣ�", Content::MONSTER);
    setupRoom(4, 2, "�׻���", "����ǰ��" + place("�׻���") + "��·��������" + minion("½�������") + "���������ǣ�", Content::MONSTER);

    setupRoom(3, 2, EMPTY_ROOM, DEFAULT_DESCRIPTION, Content::EMPTY);

    setupRoom(3, 3, "����¥", "ֻ��" + boss("½��") + "վ�����", Content::BOSS);

    setupRoom(1, 3, "�ֿ�", "������" + boss("½��") + "��" + place("�ֿ�") + "�����Ǹ����ӿ�����ʲô�ɣ�", Content::CHEST);
    setupRoom(5, 3, "�ֿ�", "������" + boss("½��") + "��" + place("�ֿ�") + "�����Ǹ����ӿ�����ʲô�ɣ�", Content::CHEST);

    setupRoom(3, 4, "������", "�����Ѻ��һ���ˣ���ǰ������ô���°ѡ�", Content::NPC);
}
