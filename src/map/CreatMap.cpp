#include "CreatMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "fmt/color.h"

using namespace std;

void changeColor(string &text, const vector<TextColor> &colors)
{
    size_t start = 0;
    while ((start = text.find('[', start)) != string::npos) {
        const size_t end = text.find(']', start);
        string key = text.substr(start + 1, end - start - 1);
        for (const auto &it : colors) {
            if (find(it.keys.begin(), it.keys.end(), key) != it.keys.end()) {
                string replacement = format(fg(it.color), "{}", key);
                text.replace(start, end - start + 1, replacement);
                start += replacement.length();
            }
        }
    }
}

// ���� ˳ʱ��90�ȣ�д����
//  X        X       ������      X         X
//  X       ������     ��       ������       X
//  X       ������     ��       ����ص�     X
//  X       ҽԺ     ������      �̵�        X
//  X        X       �� ��      X          X
Area creatMainCity()
{
    Area main_city("main_city");
    auto &rooms = main_city.getArea();
    ifstream input_file("MainCity.txt");
    if (!input_file.is_open()) {
        cerr << "Could not open file MainCity.txt" << endl;
        exit(1);
    }

    // @formatter:off
    static const vector COLORS = {
        // ����
        TextColor {{"����", "ҽ��", "�ӻ��̵�", "������", "������", "������"}, fmt::color::magenta},
        // npc
        TextColor {{"���", "ҽ��", "����ʦ��", "����", "����"}, fmt::color::green}
    };
    // @formatter:on

    int x, y;
    string name, description, content;
    while (input_file >> x >> y >> name >> description >> content) {
        Room::Content content_handled;
        changeColor(description, COLORS);
        if (content == "empty")
            content_handled = Room::Content::EMPTY;
        if (content == "npc")
            content_handled = Room::Content::NPC;
        rooms[x][y].setup(name, description, content_handled);
    }
    return main_city;
}

// �����ǣ�˳ʱ��90��д����
//   X      X     npc   X      X
// �����ֿ�  X     ½��   X    ��ҩ�ֿ�
// ������   С��    ��   С��   �׻���
//   X    ����ͤ  ����  ����ͤ    X

Area creatWuWeiCheng()
{
    Area wu_wei_cheng("wu_wei_cheng");
    auto &rooms = wu_wei_cheng.getArea();
    ifstream input_file("WuWeiCheng.txt");
    if (!input_file.is_open()) {
        cerr << "Could not open file WuWeiCheng.txt" << endl;
        exit(1);
    }

    // @formatter:off
    static const vector COLORS = {
        // ����
        TextColor {{"����", "����ͤ", "������", "�׻���"}, fmt::color::magenta},
        // npc
        TextColor {{"����"}, fmt::color::green},
        // С��
        TextColor {{"����", "½�������"}, fmt::color::yellow},
        // ��Ӣ��
        TextColor {{"������", "�׻���"}, fmt::color::orange},
        // boss
        TextColor {{"½��"}, fmt::color::gold},
        // ����
        TextColor {{"����"}, fmt::color::cyan}
    };
    // @formatter:on

    int x, y;
    string name, description, content;
    while (input_file >> x >> y >> name >> description >> content) {
        Room::Content content_handled;
        changeColor(description, COLORS);
        if (content == "empty")
            content_handled = Room::Content::EMPTY;
        else if (content == "gate")
            content_handled = Room::Content::GATE;
        else if (content == "chest")
            content_handled = Room::Content::CHEST;
        else if (content == "npc")
            content_handled = Room::Content::NPC;
        else if (content == "monster")
            content_handled = Room::Content::MONSTER;
        else if (content == "elite")
            content_handled = Room::Content::ELITE;
        else if (content == "boss")
            content_handled = Room::Content::BOSS;
        rooms[x][y].setup(name, description, content_handled);
    }
    return wu_wei_cheng;
}

Area creatShangHui()
{
    Area shang_hui("shang_hui");
    auto &rooms = shang_hui.getArea();
    ifstream input_file("ShangHui.txt");
    if (!input_file.is_open()) {
        cerr << "Could not open file ShangHui.txt" << endl;
        exit(1);
    }

    // @formatter:off
    static const vector COLORS = {
        // ����
        TextColor {{"�����̻�"}, fmt::color::magenta},
        // npc
        TextColor {{"����"}, fmt::color::green},
        // С��
        TextColor {{"����"}, fmt::color::yellow},
        // ��Ӣ��
        TextColor {{"�з�"}, fmt::color::orange},
        // boss
        TextColor {{"����"}, fmt::color::gold},
        // ����
        TextColor {{"����"}, fmt::color::cyan},
        // ����
        TextColor {{"����", "����", "��ը"}, fmt::color::red}
    };
    // @formatter:on

    int x, y;
    string name, description, content;
    while (input_file >> x >> y >> name >> description >> content) {
        Room::Content content_handled;
        changeColor(description, COLORS);
        if (content == "gate")
            content_handled = Room::Content::GATE;
        else if (content == "chest")
            content_handled = Room::Content::CHEST;
        else if (content == "npc")
            content_handled = Room::Content::NPC;
        else if (content == "monster")
            content_handled = Room::Content::MONSTER;
        else if (content == "elite")
            content_handled = Room::Content::ELITE;
        else if (content == "boss")
            content_handled = Room::Content::BOSS;
        else if (content == "trap")
            content_handled = Room::Content::TRAP;
        else if (content == "poison")
            content_handled = Room::Content::POISON;
        rooms[x][y].setup(name, description, content_handled);
    }
    return shang_hui;
}
