#pragma once

#include <string>

// ��ͼ���
constexpr int MAP_MAX_SIZE = 5;                       // ����ͼ�ߴ�
const std::string EMPTY_ROOM = "�շ���";                 // �շ��������
const std::string DEFAULT_DESCRIPTION = "���￴�����տ���Ҳ��"; // �շ���Ĭ������

enum class Map { MAIN_CITY, WU_WEI_CHENG };                           // ��ͼ
enum class Content { EMPTY, CHEST, GATE, NPC, MONSTER, ELITE, BOSS }; // ��������ݣ��ֱ��ǣ��գ����䣬�ţ�npc��С�֣���Ӣ�֣�boss

// �������
constexpr char UP = 'w';    // ��
constexpr char DOWN = 's';  // ��
constexpr char LEFT = 'a';  // ��
constexpr char RIGHT = 'd'; // ��
