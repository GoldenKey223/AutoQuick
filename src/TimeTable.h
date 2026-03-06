#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct TimetableEntry
{
    string day;
    string className;
    vector<string> paths;
};

static vector<string> parseCSVLine(const string& line);
vector<TimetableEntry> loadTimetableCSV(const string& filename);

#endif