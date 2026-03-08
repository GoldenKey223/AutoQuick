#ifndef QUICKACCESS_H
#define QUICKACCESS_H

#include <windows.h>
#include <shldisp.h>
#include <comdef.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <string>
#include <iostream>

static void invokeVerb(const std::wstring& path, const wchar_t* verb);
void addToQuickAccess(const std::wstring& path);
void removeFromQuickAccess(const std::wstring& path);
bool isPinnedToQuickAccess(const std::wstring& path);

#endif