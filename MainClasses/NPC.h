//
// Created by 32186 on 19/8/2024.
//

#pragma once
#include "../SmallClasses/Task.h"
#include "../SmallClasses/Equipment.h"
#include "../SmallClasses/Buff.h"

class NPC
{
    Task task;         // 任务
    int experience {}; // 任务的经验
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
