/*
AutoQuick
*/

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "Arguments.h"
#include "QuickAccess.h"
#include "DataManager.h"

int wmain(int argc, wchar_t* argv[]){
    // argument parsing
    AppConfig config = parseArguments(argc, argv);

    if (config.flag_count == 0){
        resetQuickAccess();

        std::vector<TimetableEntry> entries = loadTimetableCSV();
        for (TimetableEntry entry : entries){
            if (entry.should_be_active){
                toggleQuickAccess(entry.path);
                entry.isActive = true;
            }
        }

        return 0;
    }

    if (config.config){
        saveConfig(config.config_path);
    }

    if (config.set){
        resetQuickAccess();

        std::vector<TimetableEntry> entries = loadTimetableCSV();
        for (TimetableEntry entry : entries){
            if (entry.should_be_active){
                toggleQuickAccess(entry.path);
                entry.isActive = true;
            }
        }
    }

    if (config.reset){
        resetQuickAccess();
    }

    if (config.add){
        addToTimetable(config);
    }

    if (config.remove){
        removeFromTimetable(config);
    }

    return 0;
}