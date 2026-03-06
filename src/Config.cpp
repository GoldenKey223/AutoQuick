#include "Config.h"

int loadTimetable(const std::string& userCSV)
{
    char buffer[MAX_PATH];

    if (GetModuleFileNameA(nullptr, buffer, MAX_PATH) == 0)
    {
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

int addToTimetable(){
    
}

int removeFromTimetable(){

}