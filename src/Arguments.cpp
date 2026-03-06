#include "Arguments.h"

const std::string APP_VERSION = "1.0.0";

void printVersion(){
    std::cout << "AutoQuick version - " << APP_VERSION << std::endl;
}

void printHelp(){
    std::cout
    <<"AutoQuick - Timetable-Based Quick Access Manager\n"
    <<"Usage: AutoQuick.exe [options]\n"
    <<"\n"
    <<"Options:\n"
    <<" -h, --help           Show help message\n"
    <<" -v, --version        Display application version\n"
    <<" -c, --config <path>  Path to timetable.csv\n"
    <<" --verbose            Enable detailed logging\n"
    <<std::endl;
}

AppConfig parseArguments(int argc, char* argv[]){
    AppConfig config;

    for (int i = 1; i < argc; ++i){
        std::string arg = argv[i];
        if(arg == "--version" || arg == "-v"){
            printVersion();
            exit(0);
        }else if( arg == "--help" || arg == "-h"){
            printHelp();
            exit(0);
        }else if(arg == "--config" || arg == "-c"){
            config.config_path = argv[++i];
            config.config = true;
        }else if(arg == "--verbose" || arg == "-v"){
            config.verbose = true;
        }
    }

    return config;
}