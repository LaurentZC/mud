#pragma once

#include "Task.h"
#include "Equipment.h"
#include "Buff.h"

class NPC
{
    Task task;         // ����
    int experience {}; // ����ľ���
};

class EquipmentGiving : public NPC
{
    Equipment equipment;

    public:
    void talk();
};

class BuffGiving : public NPC
{
    Buff buff;

    public:
    void talk();
};
