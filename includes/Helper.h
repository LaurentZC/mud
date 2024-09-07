#pragma once

#include <string>

std::string area(const std::string &text);

std::string npc(const std::string &text);

void waitForLoad(int total_time_ms);

void waitForAnyKey();

void printTitle();

void printSlowly(const std::string &text, int delay_milliseconds = 10);

bool achievePercent(double probability);

void restart();
