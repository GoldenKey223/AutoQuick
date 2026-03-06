#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int loadTimetable(const std::string& userCSV = "");

#endif