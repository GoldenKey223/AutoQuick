/*
AutoQuick
*/

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#include "Arguments.h"
#include "Config.h"
#include "QuickAccess.h"
#include "TimeTable.h"

using namespace std;

int main (int argc, char* argv[])
{
    // argument parsing
    AppConfig config = parseArguments(argc, argv);

    // check for config arguments
    if(config.config){
        loadTimetableCSV(config.config_path);
    }
    
    // loading saved timetable.csv
    vector<TimetableEntry> entries = loadTimetableCSV("timetable.csv");

    // get system day of week
    const vector<string> days = {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};
    const vector<string> wdays = {"Mon", "Tues", "Wed", "Thurs", "Fri"};
    const vector<string> wends = {"Sun", "Sat"};

    time_t now = time(nullptr);
    tm* timeinfo = localtime(&now);

    int dayOfWeek = timeinfo->tm_wday; 

    // Compare current quick access lists to add
    for(const TimetableEntry& entry: entries){
        bool souldBeActive = (entry.day == "All" || entry.day == days[dayOfWeek] || (entry.day == "wday" && dayOfWeek >= 1 && dayOfWeek <= 5) || (entry.day == "wend" && (dayOfWeek == 0 || dayOfWeek == 6)));

        for(const string& path : entry.paths){
            wstring wpath(path.begin(), path.end());

            if(souldBeActive){
                if(!isPinnedToQuickAccess(wpath)) addToQuickAccess(wpath);
            }else{
                if(isPinnedToQuickAccess(wpath)) removeFromQuickAccess(wpath);
            }
        }
    }
    return 0;
}