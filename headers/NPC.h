#pragma once

#include "Buff.h"
#include "Equipment.h"
#include "Task.h"

class NPC
{
    Task task;         // ����
    int experience {}; // ����ľ���
};

class EquipmentGiving : public NPC
{
public:
    EquipmentGiving();
    void talk();

private:
    Equipment *equipment {};
};

class BuffGiving : public NPC
{
public:
    void talk();

private:
    Buff buff;
};
