#include "../headers/Constant.h"
#include "../headers/Helper.h"
#include "../headers/Map.h"

using namespace std;

Map creatWuWeiCheng()
{
    Map wu_wei_cheng("wu_wei_cheng");

    auto &rooms = wu_wei_cheng.getMap();
    rooms[3][1].Setup("����", "����" + Place("����") + "�����������������ս��������������ͼ����", "����");

    rooms[2][1].Setup("����ͤ", "������" + Place("����ͤ") + "����������Щ" + Minion("����") + "�ƺ��������㡣", ENEMY);
    rooms[4][1].Setup("����ͤ", "������" + Place("����ͤ") + "����������Щ" + Minion("����") + "�ƺ��������㡣", ENEMY);

    rooms[1][2].Setup("������", "����վ�ŵ�����½�������ұۡ���" + Elite("������") + "����������ʮ��ǿ��", ELITE);
    rooms[5][2].Setup("�׻���", "����վ�ŵ�����½�������ұۡ���" + Elite("�׻���") + "����������ʮ��ǿ��", ELITE);

    rooms[2][2].Setup("������", "����ǰ��" + Place("������") + "��·��������" + Minion("½�������") + "���������ǣ�", ENEMY);
    rooms[4][2].Setup("�׻���", "����ǰ��" + Place("�׻���") + "��·��������" + Minion("½�������") + "���������ǣ�", ENEMY);

    rooms[3][2].Setup(EMPTY_ROOM, DEFAULT_DESCRIPTION, EMPTY_CONTENT);

    rooms[3][3].Setup("����¥", "ֻ��" + Boss("½��") + "վ�����", BOSS);

    rooms[1][3].Setup("�ֿ�", "������" + Boss("½��") + "��" + Place("�ֿ�") + "�����Ǹ����ӿ�����ʲô�ɣ�");
    rooms[5][3].Setup("�ֿ�", "������" + Boss("½��") + "��" + Place("�ֿ�") + "�����Ǹ����ӿ�����ʲô�ɣ�");

    return wu_wei_cheng;
}