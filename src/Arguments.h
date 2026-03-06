#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <iostream>
#include <string>

struct AppConfig
{
    std::string config_path = "config.csv";
    bool config = false;
    bool verbose = false;
};

void printVersion();
void printHelp();
AppConfig parseArguments(int argc, char* argv[]);

#endif