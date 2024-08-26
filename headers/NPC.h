#pragma once

#include "Buff.h"
#include "Equipment.h"
#include "Task.h"

class NPC
{
    Task task;         // 任务
    int experience {}; // 任务的经验
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
