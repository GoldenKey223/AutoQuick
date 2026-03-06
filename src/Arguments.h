#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <iostream>
#include <string>

using namespace std;

// Struct to store the arguments

struct AppConfig
{
    string config_Path = "config.json";
    bool verbose = false;
};

// Functions
void printVersion();
void printHelp();
AppConfig parseArguments(int argc, char* argv[]);

#endif