#pragma once

#include <string>

// ��ͼ���
constexpr int MAP_MAX_SIZE = 5;                       // ����ͼ�ߴ�
const std::string EMPTY_ROOM = "�շ���";                 // �շ��������
const std::string DEFAULT_DESCRIPTION = "���￴�����տ���Ҳ��"; // �շ���Ĭ������

enum class Content { EMPTY, MONSTER, ELITE, BOSS, CHEST, GATE }; // ��������ݣ��ֱ��ǣ��գ�С�֣���Ӣ�֣�boss������

// ��ɫ���
const std::string RESET = "\033[0m";         // �����ı���ɫ
const std::string RED = "\033[31m";          // ��ɫ��boss
const std::string GREEN = "\033[32m";        // ��ɫ������
const std::string YELLOW = "\033[33m";       // ��ɫ��С��
const std::string BLUE = "\033[34m";         // ��ɫ���ص�
const std::string PURPLE = "\033[35m";       // ��ɫ��
const std::string ORANGE = "\033[38;5;208m"; // ��ɫ����Ӣ��

// �������
const std::string UP = "up";       // ��
const std::string DOWN = "down";   // ��
const std::string LEFT = "left";   // ��
const std::string RIGHT = "right"; // ��
