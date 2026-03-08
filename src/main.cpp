/*
AutoQuick
*/

#include <windows.h>
#include <filesystem>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#include "Arguments.h"
#include "Config.h"
#include "QuickAccess.h"
#include "TimeTable.h"

int wmain(int argc, wchar_t* argv[]){
    // argument parsing
    AppConfig config = parseArguments(argc, argv);
    std::cout << "parsed arugments." << std::endl;

    if (config.flag_count == 0){
        return 0;
    }

    if (config.config){

    }

    if (config.set){
        
    }

    if (config.reset){

    }

    if (config.add){

    }

    if (config.remove){
        
    }

    // check for config arguments
    if(config.config){
        loadTimetable(config.config_path);
    }
    std::cout << "checked for config argument." << std::endl;
    
    // loading saved timetable.csv
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::filesystem::path exeDir = std::filesystem::path(buffer).parent_path();
    std::filesystem::path timetablePath = exeDir / "timetable.csv";

    std::vector<TimetableEntry> entries = loadTimetableCSV(timetablePath.string());
    std::cout << "checked for saved timetable.\n" << "Size of entries: " << entries.size() << std::endl;

    // get system day of week
    const std::vector<std::string> days = {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};
    const std::vector<std::string> wdays = {"Mon", "Tues", "Wed", "Thurs", "Fri"};
    const std::vector<std::string> wends = {"Sun", "Sat"};

    time_t now = time(nullptr);
    tm* timeinfo = localtime(&now);

    int dayOfWeek = timeinfo->tm_wday; 
    std::cout << "checked for system time." << std::endl;

    // Compare current quick access lists to add
    for(const TimetableEntry& entry: entries){
        std::cout << "checking for class: " << entry.className << std::endl;

        bool souldBeActive = (entry.day == "All" || entry.day == days[dayOfWeek] || (entry.day == "wday" && dayOfWeek >= 1 && dayOfWeek <= 5) || (entry.day == "wend" && (dayOfWeek == 0 || dayOfWeek == 6)));

        for(const std::string& path : entry.paths){
            std::cout << "checking for each path: " << path << std::endl;

            std::wstring wpath(path.begin(), path.end());

            if(souldBeActive){
                std::cout << entry.className << " should be active.\n";
                if(!isPinnedToQuickAccess(wpath)) addToQuickAccess(wpath);
            }else{
                std::cout << entry.className << " should not be active.\n";
                if(isPinnedToQuickAccess(wpath)) removeFromQuickAccess(wpath);
            }
        }
    }
    return 0;
}