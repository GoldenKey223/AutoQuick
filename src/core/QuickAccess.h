#ifndef QUICKACCESS_H
#define QUICKACCESS_H

#include <windows.h>
#include <shlobj.h>
#include <filesystem>
#include <string>
#include <iostream>

int toggleQuickAccess(const std::wstring& path);
int resetQuickAccess();

#endif