#include "Arguments.h"

const string APP_VERSION = "1.0.0";

void printVersion(){
    cout << "AutoQuick version - " << APP_VERSION << endl;
}

void printHelp(){
    cout
    <<"AutoQuick - Timetable-Based Quick Access Manager\n"
    <<"Usage: AutoQuick.exe [options]\n"
    <<"\n"
    <<"Options:\n"
    <<" -h, --help           Show help message\n"
    <<" -v, --version        Display application version\n"
    <<" -c, --config <path>  Path to timetable.csv\n"
    <<" --verbose            Enable detailed logging\n"
    <<endl;
}

AppConfig parseArguments(int argc, char* argv[]){
    AppConfig config;

    for (int i = 1; i < argc; ++i){
        string arg = argv[i];
        if(arg == "--version" || arg == "-v"){
            printVersion();
            exit(0);
        }else if( arg == "--help" || arg == "-h"){
            printHelp();
            exit(0);
        }else if(arg == "--config" || arg == "-c"){
            config.config_Path = argv[++i];
        }else if(arg == "--verbose" || arg == "-v"){
            config.verbose = true;
        }
    }

    return config;
}