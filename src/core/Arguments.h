#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <iostream>
#include <string>

struct AppConfig
{
    unsigned int flag_count = 0;

    std::wstring config_path = L"config.csv";
    bool config = false;

    bool set = false;

    bool reset = false;

    std::wstring add_config_day;
    std::wstring add_config_class_name;
    std::wstring add_config_path;
    bool add = false;
    
    std::wstring remove_config_day;
    std::wstring remove_config_class_name;
    std::wstring remove_config_path;
    bool remove = false;
};

void printVersion();
void printHelp();
AppConfig parseArguments(int argc, wchar_t* argv[]);

#endif