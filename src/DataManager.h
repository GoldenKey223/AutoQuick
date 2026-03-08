#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct TimetableEntry
{
    std::string day;
    std::string className;
    std::string path;
};

std::vector<TimetableEntry> loadTimetableCSV();
int saveConfig(const std::string& userCSV);


#endif