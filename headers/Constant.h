#pragma once

#include <string>

// ��ͼ���
constexpr int MAP_MAX_SIZE = 5;                       // ����ͼ�ߴ�
const std::string EMPTY_ROOM = "�շ���";                 // �շ��������
const std::string DEFAULT_DESCRIPTION = "���￴�����տ���Ҳ��"; // �շ���Ĭ������

enum class RoomContent { EMPTY, CHEST, GATE, NPC, MONSTER, ELITE, BOSS, TRAP, POISON }; // ��������ݣ��ֱ��ǣ��գ����䣬�ţ�npc��С�֣���Ӣ�֣�boss�����壬��

// �������
constexpr char UP = 'w';    // ��
constexpr char DOWN = 's';  // ��
constexpr char LEFT = 'a';  // ��
constexpr char RIGHT = 'd'; // ��
