#pragma once

#include <string>

// ��ͼ���
constexpr int MAP_MAX_SIZE = 5;                       // ����ͼ�ߴ�
const std::string EMPTY_ROOM = "�շ���";                 // �շ��������
const std::string DEFAULT_DESCRIPTION = "���￴�����տ���Ҳ��"; // �շ���Ĭ������

enum class Map { MAIN_CITY, WU_WEI_CHENG };                           // ��ͼ
enum class Content { EMPTY, CHEST, GATE, NPC, MONSTER, ELITE, BOSS }; // ��������ݣ��ֱ��ǣ��գ����䣬�ţ�npc��С�֣���Ӣ�֣�boss

// ��ɫ���
const std::string RESET = "\033[0m";         // �����ı���ɫ
const std::string RED = "\033[31m";          // ��ɫ��boss
const std::string GREEN = "\033[32m";        // ��ɫ������
const std::string YELLOW = "\033[33m";       // ��ɫ��С��
const std::string BLUE = "\033[34m";         // ��ɫ���ص�
const std::string PURPLE = "\033[35m";       // ��ɫ��
const std::string ORANGE = "\033[38;5;208m"; // ��ɫ����Ӣ��

// �������
constexpr char UP = 'w';    // ��
constexpr char DOWN = 's';  // ��
constexpr char LEFT = 'a';  // ��
constexpr char RIGHT = 'd'; // ��
