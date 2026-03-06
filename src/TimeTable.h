#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct TimetableEntry
{
    std::string day;
    std::string className;
    std::vector<std::string> paths;
};

static std::vector<std::string> parseCSVLine(const std::string& line);
std::vector<TimetableEntry> loadTimetableCSV(const std::string& filename);

#endif