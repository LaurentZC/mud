#include "../headers/Area.h"
#include "../headers/Constant.h"
#include "../headers/Helper.h"

using namespace std;

Area creatWuWeiCheng()
{
    Area wu_wei_cheng("wu_wei_cheng");

    auto& rooms = wu_wei_cheng.getArea();

    auto setupRoom = [&rooms](const int x, const int y, const std::string& name, const std::string& description, const Content content)
    {
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

    return wu_wei_cheng;
}
