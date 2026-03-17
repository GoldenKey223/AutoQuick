#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <codecvt>
#include <locale>

#include "Arguments.h"

struct TimetableEntry
{
    std::wstring day;
    std::wstring class_name;
    std::wstring path;

    bool should_be_active = false;
    bool isActive = false;
};

std::filesystem::path getTimetablePath();
std::vector<TimetableEntry> loadTimetableCSV();
int saveConfig(const std::wstring& userCSV);
int addToTimetable(const AppConfig& config);
int removeFromTimetable(const AppConfig& config);
void shouldBeActive(std::vector<TimetableEntry>& entries);

#endif