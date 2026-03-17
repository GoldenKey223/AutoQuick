#ifndef NETWORKDRIVE_H
#define NETWORKDRIVE_H  

#include <windows.h>
#include <winnetwk.h>
#include <iostream>
#include <string>

struct NetworkDrive{
    std::wstring local_name;
    std::wstring remote_name;
    std::wstring username;
    std::wstring password;
};

#endif