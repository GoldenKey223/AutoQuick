#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int loadTimetable(const string& userCSV = "");

#endif