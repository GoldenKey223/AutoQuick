#include "Arguments.h"

void printVersion(){
    std::cout << "AutoQuick version - " << APP_VERSION << std::endl;
}

void printHelp(){
    std::cout
    <<"AutoQuick - Timetable-Based Quick Access Manager\n"
    <<"Usage: AutoQuick.exe [options]\n"
    <<"\n"
    <<"Options:\n"
    <<"  -h, --help                Show help message\n"
    <<"  -v, --version             Display application version\n"
    <<"  -c, --config <path>       Path to timetable.csv\n"
    <<"  -s, --set                 Refreshes quick access\n"
    <<"  -r, --reset               Resets quick access to default\n"
    <<"  -a, --add <day> <path>      adds <day> and <path> to config\n"
    <<"  -rm, --remove <day> <path>  removes <day> and <path> from config\n"
    <<std::endl;
}

AppConfig parseArguments(int argc, wchar_t* argv[]){
    AppConfig config;

    for (int i = 1; i < argc; ++i){
        std::wstring arg = argv[i];
        if (arg == L"-h" || arg == L"--help"){
            printHelp();
            exit(0);
        }else if ( arg == L"-v" || arg == L"--version"){
            printVersion();
            exit(0);
        }else if (arg == L"-c" || arg == L"--config"){
            if (i + 1 < argc) {
                config.config_path = argv[++i];
                config.config = true;
                config.flag_count++;
            }else{
                std::cerr << "Error: -c, --config requires a path.\n";
                exit(1);
            }
        }else if (arg == L"-s" || arg == L"--set"){
            config.set = true;
            config.flag_count++;
        }else if (arg == L"-r" || arg == L"--reset"){
            config.reset = true;
            config.flag_count++;
        }else if (arg == L"-a" || arg == L"--add"){
            if (i + 2 < argc){
                config.add_config_day = argv[++i];
                config.add_config_path = argv[++i];
                config.add = true;
                config.flag_count++;
            }else{
                std::cerr << "Error: -a, --add requires <day> <path>.\n";
                exit(1);
            }
        }else if (arg == L"-rm" || arg == L"--remove"){
            if (i + 2 < argc){
                config.remove_config_day = argv[++i];
                config.remove_config_path = argv[++i];
                config.remove = true;
                config.flag_count++;
            }else{
                std::cerr << "Error: -rm, --remove requires <day> <path>.\n";
                exit(1);
            }
        }else{
            std::cerr
            <<"Error: Unknown options.\n"
            <<"For more informaion use -h or --help.\n";
        }
    }

    return config;
}