#include "DataManager.h"

static std::vector<std::string> parseCSVLine(const std::string& line){
    std::vector<std::string> result;
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++){
        char c = line[i];

        if (c == '"'){
            inQuotes != inQuotes;
        }else if (c == '|' && !inQuotes){
            result.push_back(field);
            field.clear();
        }else{
            field += c;
        }
    }

    result.push_back(field);
    return result;
}

std::vector<TimetableEntry> loadTimetableCSV() {
    std::vector<TimetableEntry> entries;

    char buffer[MAX_PATH];
    if (GetModuleFileNameA(nullptr, buffer, MAX_PATH) == 0){
        std::cout << "Unable to determine executable path.\n";
        return entries;
    }
    std::filesystem::path exeDir = std::filesystem::path(buffer).parent_path();
    std::filesystem::path timetable_path = exeDir / "timetable.csv";
    std::ifstream file(timetable_path);

    if (!file.is_open()) return entries;

    std::string line;
    getline(file, line);

    while (getline(file, line)){
        std::vector<std::string> fields = parseCSVLine(line);

        if (fields.size() < 2) continue;

        TimetableEntry entry;
        entry.day = fields[0];
        entry.className = fields[1];
        entry.path = fields[2];

        entries.push_back(entry);
    }

    return entries;
}

int saveConfig(const std::string& userCSV)
{
    char buffer[MAX_PATH];
    if (GetModuleFileNameA(nullptr, buffer, MAX_PATH) == 0){
        std::cout << "Unable to determine executable path.\n";
        return 1;
    }
    std::filesystem::path exeDir = std::filesystem::path(buffer).parent_path();
    std::filesystem::path timetablePath = exeDir / "timetable.csv";

    if(userCSV.empty()) return 1;
    if(!std::filesystem::exists(userCSV)) return 1;

    try{
        if(std::filesystem::exists(timetablePath)){
            char overwrite;

            std::cout
                << "A timetable already exists.\n"
                << "Overwrite it? [Y/n]: ";

            std::cin >> overwrite;

            if(overwrite != 'y' && overwrite != 'Y'){
                std::cout << "Timetable not modified.\n";
                return 1;
            }
        }

        std::filesystem::copy_file(userCSV, timetablePath, std::filesystem::copy_options::overwrite_existing);

        std::cout << "Timetable loaded from: " << userCSV << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << "Failed to copy timetable: " << e.what() << std::endl;
        return 1;
    }
}