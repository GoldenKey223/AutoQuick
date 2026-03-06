#ifndef QUICKACCESS_H
#define QUICKACCESS_H

#include <windows.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <string>

static void invokeVerb(const std::wstring& path, const wchar_t* verb);
void addToQuickAccess(const std::wstring& path);
void removeFromQuickAccess(const std::wstring& path);
bool isPinnedToQuickAccess(const std::wstring& path);

#endif