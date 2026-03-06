#include "Config.h"

int loadTimetable(const string& userCSV)
{
    char buffer[MAX_PATH];

    if (GetModuleFileNameA(nullptr, buffer, MAX_PATH) == 0)
    {
        cout << "Unable to determine executable path.\n";
        return 1;
    }

    filesystem::path exeDir = filesystem::path(buffer).parent_path();
    filesystem::path timetablePath = exeDir / "timetable.csv";

    if(userCSV.empty()) return 1;
    if(!filesystem::exists(userCSV)) return 1;

    try{
        if(filesystem::exists(timetablePath)){
            char overwrite;

            cout
                << "A timetable already exists.\n"
                << "Overwrite it? [Y/n]: ";

            cin >> overwrite;

            if(overwrite != 'y' && overwrite != 'Y'){
                cout << "Timetable not modified.\n";
                return 1;
            }
        }

        filesystem::copy_file(userCSV, timetablePath, filesystem::copy_options::overwrite_existing);

        cout << "Timetable loaded from: " << userCSV << endl;
        return 0;
    }
    catch (const exception& e)
    {
        cout << "Failed to copy timetable: " << e.what() << endl;
        return 1;
    }
}

int addToTimetable(){
    
}

int removeFromTimetable(){

}