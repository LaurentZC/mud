#pragma once

#include "Equipment.h"
#include "Pill.h"
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

class PillGiving : public NPC
{
public:
    void talk();

private:
    Pill pill;
};
