#include "DataManager.h"

static std::vector<std::wstring> parseCSVLine(const std::wstring& line){
    std::vector<std::wstring> result;
    std::wstring field;
    bool inQuotes = false;

    for (wchar_t c : line){
        if (c == L'"'){
            inQuotes = !inQuotes;
        }else if (c == L'|' && !inQuotes){
            result.push_back(field);
            field.clear();
        }else{
            field += c;
        }
    }

    result.push_back(field);

    return result;
}

std::filesystem::path getTimetablePath(){
    wchar_t buffer[MAX_PATH];
    if (GetModuleFileNameW(nullptr, buffer, MAX_PATH) == 0){
        std::cout << "Unable to determine executable path.\n";
        return "";
    }
    std::filesystem::path exeDir = std::filesystem::path(buffer).parent_path();
    std::filesystem::path timetable_path = exeDir / "timetable.csv";

    return timetable_path;
}

static void backupTimetable(){
    std::filesystem::path path = getTimetablePath();
    if (!std::filesystem::exists(path)) return;

    std::filesystem::path backupPath = path;
    backupPath.replace_extension(L".csv.bak");

    std::error_code ec;
    std::filesystem::copy_file(path, backupPath, std::filesystem::copy_options::overwrite_existing, ec);
    
    if (ec){
        std::wcerr << L"Backup failed: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(ec.message()) << std::endl;
    }
}

std::vector<TimetableEntry> loadTimetableCSV() {
    std::cout << "loading timetable csv.\n";

    std::vector<TimetableEntry> entries;
    std::wifstream file(getTimetablePath());

    std::cout << getTimetablePath() << std::endl;

    if (!file.is_open()) return entries;

    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    std::wstring line;
    if (!std::getline(file, line)) return entries;

    while (std::getline(file, line)){
        if (line.empty()) continue;
        if (!line.empty() && line.back() == L'\r') line.pop_back();

        std::vector<std::wstring> fields = parseCSVLine(line);
        if (fields.size() < 3) continue;

        TimetableEntry entry;
        entry.day = fields[0];
        entry.class_name = fields[1];
        entry.path = fields[2];

        entries.push_back(entry);
    }
    std::cout << entries.size() << std::endl;

    shouldBeActive(entries);

    return entries;
}

int saveConfig(const std::wstring& userCSV)
{
    std::filesystem::path timetablePath = getTimetablePath();

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

        backupTimetable();
        std::filesystem::copy_file(userCSV, timetablePath, std::filesystem::copy_options::overwrite_existing);

        std::wcout << L"Timetable loaded from: " << userCSV << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << "Failed to copy timetable: " << e.what() << std::endl;
        return 1;
    }
}

int addToTimetable(const AppConfig& config){
    backupTimetable();
    
    std::filesystem::path path = getTimetablePath();

    std::wofstream file(path, std::ios::app);
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open()){
        std::cerr << "Failed to open timetable for writing." << std::endl;
        return 1;
    }

    file << config.add_config_day << L"|" << config.add_config_class_name << L"|" << config.add_config_path << std::endl;

    std::wcout << L"Successfully added entry for " << config.add_config_day << std::endl;

    return 0;
}

int removeFromTimetable(const AppConfig& config){
    // to be added, make wstring from arguments and just compare with getline
}

void shouldBeActive(std::vector<TimetableEntry>& entries){
    std::cout << "checking if it should be active.\n";

    const std::vector<std::wstring> days = {L"Sun", L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat"};
    const std::vector<std::wstring> wdays = {L"Mon", L"Tue", L"Wed", L"Thu", L"Fri"};
    const std::vector<std::wstring> wends = {L"Sun", L"Sat"};

    time_t now = time(nullptr);
    tm* timeinfo = localtime(&now);

    int dayOfWeek = timeinfo->tm_wday; 

    std::cout << "checking if it should be active.\n";
    std::cout << entries.size() << std::endl;

    for (TimetableEntry& entry: entries){
        entry.should_be_active = (entry.day == L"All" || entry.day == days[dayOfWeek] || (entry.day == L"wday" && dayOfWeek >= 1 && dayOfWeek <= 5) || (entry.day == L"wend" && (dayOfWeek == 0 || dayOfWeek == 6)));
        if (entry.should_be_active){
            std::wcout << entry.class_name << " should be active.\n";
        }else{
            std::wcout << entry.class_name << " should not be active.\n";
        }
    }
}