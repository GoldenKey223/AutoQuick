#ifndef QUICKACCESS_H
#define QUICKACCESS_H

#include <windows.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <string>

using namespace std;

static void invokeVerb(const wstring& path, const wchar_t* verb);
void addToQuickAccess(const wstring& path);
void removeFromQuickAccess(const wstring& path);
bool isPinnedToQuickAccess(const wstring& path);

#endif