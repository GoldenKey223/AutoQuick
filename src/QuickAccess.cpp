#include "QuickAccess.h"

static void invokeVerb(const std::wstring& path, const wchar_t* verb){
    IShellItem* item = nullptr;
    IContextMenu* menu = nullptr;

    if (FAILED(SHCreateItemFromParsingName(path.c_str(), nullptr, IID_PPV_ARGS(&item))))
        return;

    if (FAILED(item->BindToHandler(nullptr, BHID_SFUIObject, IID_PPV_ARGS(&menu))))
    {
        item->Release();
        return;
    }

    CMINVOKECOMMANDINFOEX info{};
    info.cbSize = sizeof(info);
    info.fMask = CMIC_MASK_UNICODE;
    info.lpVerb = (LPCSTR)verb;
    info.lpVerbW = verb;
    info.nShow = SW_SHOWNORMAL;

    menu->InvokeCommand((LPCMINVOKECOMMANDINFO)&info);

    menu->Release();
    item->Release();
}

void addToQuickAccess(const std::wstring& path){
    invokeVerb(path, L"pintohome");
}

void removeFromQuickAccess(const std::wstring& path){
    invokeVerb(path, L"unpinfromhome");
}

bool isPinnedToQuickAccess(const std::wstring& path){
    IShellItem* quickAccess = nullptr;

    HRESULT hr = SHCreateItemFromParsingName(
        L"shell:::{679F85CB-0220-4080-B29B-5540CC05AAB6}",
        nullptr,
        IID_PPV_ARGS(&quickAccess)
    );

    if (FAILED(hr))
        return false;

    IEnumShellItems* enumerator = nullptr;
    hr = quickAccess->BindToHandler(nullptr, BHID_EnumItems, IID_PPV_ARGS(&enumerator));

    if (FAILED(hr))
    {
        quickAccess->Release();
        return false;
    }

    IShellItem* item = nullptr;

    while (enumerator->Next(1, &item, nullptr) == S_OK)
    {
        PWSTR itemPath = nullptr;

        if (SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &itemPath)))
        {
            if (_wcsicmp(itemPath, path.c_str()) == 0)
            {
                CoTaskMemFree(itemPath);
                item->Release();
                enumerator->Release();
                quickAccess->Release();
                return true;
            }

            CoTaskMemFree(itemPath);
        }

        item->Release();
    }

    enumerator->Release();
    quickAccess->Release();

    return false;
}